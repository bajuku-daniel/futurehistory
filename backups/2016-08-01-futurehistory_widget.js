(function ($) {

  Drupal.futurehistory = Drupal.futurehistory || {};
  Drupal.futurehistory.maps = Drupal.futurehistory.maps || {};
  Drupal.futurehistory.dist_sliders = Drupal.futurehistory.dist_sliders || {};
  Drupal.futurehistory.direction_sliders = Drupal.futurehistory.direction_sliders || {};
  Drupal.futurehistory.angle_sliders = Drupal.futurehistory.angle_sliders || {};
  Drupal.futurehistory.markers = Drupal.futurehistory.markers || {};
  Drupal.futurehistory.line_a = Drupal.futurehistory.line_a || {};
  Drupal.futurehistory.line_b = Drupal.futurehistory.line_b || {};
  Drupal.futurehistory.pie = Drupal.futurehistory.pie || {};

  geocoder = new google.maps.Geocoder();      
  var lat;
  var lng;
  var dist = 250;
  var direction = 1;
  var angle = 40;
  var latLng;
  var noarview;
  var coordinate_known;
  var mapOptions;
  var angle_slide_center = 80;


  /**
   * Set the latitude and longitude values to the input fields
   * And optionaly update the address field
   */



  Drupal.futurehistory.codeLatLng = function(latLng, i, op) {
    // Update the lat and lng input fields
    $('#futurehistory-lat-' + i + ' input').attr('value', latLng.lat());
    $('#futurehistory-lng-' + i + ' input').attr('value', latLng.lng());
    $('#futurehistory-coordinate-lat-' + i + ' input').val(latLng.lat());
    $('#futurehistory-coordinate-lng-' + i + ' input').val(latLng.lng());
    Drupal.futurehistory.getCity(latLng,i); 
     
    // Update the address field
    if ((op == 'marker' || op == 'geocoder') && geocoder) {
      geocoder.geocode({'latLng': latLng}, function(results, status) {
        if (status == google.maps.GeocoderStatus.OK) {
          $('#futurehistory-address-' + i + ' input').val(results[0].formatted_address);
          if (op == 'geocoder') {
            Drupal.futurehistory.setZoom(i, results[0].geometry.location_type);
          }
        }
        else {
          $('#futurehistory-address-' + i + ' input').val('');
          if (status != google.maps.GeocoderStatus.ZERO_RESULTS) {
            alert(Drupal.t('Geocoder failed due to: ') + status);
          }
        }
      });
    }
  }

  Drupal.futurehistory.getCity = function(latLng, i) {
    geocoder.geocode({'latLng': latLng}, function(results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        // Get the Cityname "town" for the taxonomy
        var arrAddress = results[0].address_components;
        var itemCity='';
        // iterate through address_component array
        $.each(arrAddress, function (i, address_component) {
          if (address_component.types[0] == "locality"){
            itemCity = address_component.long_name;
            $('#edit-field-stadt-und').val(itemCity);
            $('#edit-field-stadt input').prop( "readonly", true );

          }
        });
      }
    });
  }


  /**
   * Get the location from the address field
   */
  Drupal.futurehistory.codeAddress = function(i, noarview) {
    var address = $('#futurehistory-address-' + i + ' input').val();

    geocoder.geocode( { 'address': address }, function(results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        Drupal.futurehistory.maps[i].setCenter(results[0].geometry.location);
        Drupal.futurehistory.setMapMarker(results[0].geometry.location, i);
        Drupal.futurehistory.codeLatLng(results[0].geometry.location, i, 'textinput');
        Drupal.futurehistory.setZoom(i, results[0].geometry.location_type);
        if (!noarview) {
          Drupal.futurehistory.setMapArrow(results[0].geometry.location, i, dist, direction, angle);
        }
        latLng = results[0].geometry.location;
      }
      else {
        alert(Drupal.t('Geocode was not successful for the following reason: ') + status);
      }
    });
  }

  /**
   * Get the location from the coordinates fields
   */
  Drupal.futurehistory.codeCoordinates = function(i, noarview) {
    var coordinates = new google.maps.LatLng($('#futurehistory-coordinate-lat-' + i + ' input').val(), $('#futurehistory-coordinate-lng-' + i + ' input').val());
    Drupal.futurehistory.maps[i].setCenter(coordinates);
    Drupal.futurehistory.setMapMarker(coordinates, i);
    Drupal.futurehistory.codeLatLng(coordinates, i, 'marker');
    Drupal.futurehistory.setZoom(i, coordinates);
    if (!noarview) {
      Drupal.futurehistory.setMapArrow(coordinates, i, dist, direction, angle);
    }
    latLng = coordinates;
  }
 

/**
   *
   * Set zoom level depending on accuracy (location_type)
   *
   */
  Drupal.futurehistory.setZoom = function(i, location_type) {
    if (location_type == 'APPROXIMATE') {
      Drupal.futurehistory.maps[i].setZoom(12);
    }
    else if (location_type == 'GEOMETRIC_CENTER') {
      Drupal.futurehistory.maps[i].setZoom(16);
    }
    else if (location_type == 'RANGE_INTERPOLATED' || location_type == 'ROOFTOP') {
      Drupal.futurehistory.maps[i].setZoom(19);
    }
  }

  /**
   * Set/Update a marker on a map
   */
  Drupal.futurehistory.setMapMarker = function(latLng, i) {
    // remove old marker
    if (Drupal.futurehistory.markers[i]) {
      Drupal.futurehistory.markers[i].setMap(null);
    }
    Drupal.futurehistory.markers[i] = new google.maps.Marker({
      map: Drupal.futurehistory.maps[i],
      draggable: Drupal.settings.futurehistory.settings.marker_draggable ? true : false,
      position: latLng
    });

   google.maps.event.addListener(Drupal.futurehistory.markers[i], 'dragend', function(me) {
      Drupal.futurehistory.codeLatLng(me.latLng, i, 'marker');
      Drupal.futurehistory.setMapMarker(me.latLng, i);
      if (!noarview) {
          Drupal.futurehistory.setMapArrow(me.latLng, i, dist, direction, angle);
      }
      latLng = me.latLng

    });

    return false; // if called from <a>-Tag
  }
 
  /**
   * Set/Update the view direction on a map
   */
  Drupal.futurehistory.setMapArrow = function(latLng, i, dist, direction, angle) {
    // remove old marker
    if (Drupal.futurehistory.line_a[i] || Drupal.futurehistory.line_b[i] || Drupal.futurehistory.pie[i]) {
      Drupal.futurehistory.line_a[i].setMap(null);
      Drupal.futurehistory.line_b[i].setMap(null);
      Drupal.futurehistory.pie[i].setMap(null);
    }
    var lineSymbol = {
      path: google.maps.SymbolPath.FORWARD_OPEN_ARROW
    };

    var standpunkt = latLng;
    var distance = dist;
    var heading = direction;
    var half_openangle = angle/2;
        
    var point_a = google.maps.geometry.spherical.computeOffset(standpunkt, distance, heading - half_openangle);
    var point_b = google.maps.geometry.spherical.computeOffset(standpunkt, distance, heading + half_openangle);
        
    Drupal.futurehistory.line_a[i] = new google.maps.Polyline({
      path: [standpunkt, point_a],
      icons: [{
        icon: lineSymbol,
        offset: '100%'
       }],
       map: Drupal.futurehistory.maps[i]
    });
        
    Drupal.futurehistory.line_b[i] = new google.maps.Polyline({
      path: [standpunkt, point_b],
      icons: [{
        icon: lineSymbol,
        offset: '100%'
      }],
      map: Drupal.futurehistory.maps[i]
    });
  
    Drupal.futurehistory.pie[i] = new google.maps.Polygon({
      paths: [standpunkt, point_a, point_b],
      strokeColor: '#9E1F81',
      strokeOpacity: 0.6,
      strokeWeight: 1,
      fillColor: '#9E1F81',
      fillOpacity: 0.45,
      map: Drupal.futurehistory.maps[i]
    });
    return false; // if called from <a>-Tag
  } 


  Drupal.behaviors.futurehistory = {
    attach: function(context, settings) {
   

      $.each(Drupal.settings.futurehistory.defaults, function(i, mapDefaults) {
        // Only make this once ;)
        $("#futurehistory-map-" + i).once('futurehistory-googlemaps', function(){

          // Attach listeners
          $('#futurehistory-address-' + i + ' input').keypress(function(ev){
            if(ev.which == 13){
              ev.preventDefault();
              Drupal.futurehistory.codeAddress(i, noarview);
            }
          });
          $('#futurehistory-address-geocode-' + i).click(function(e) {
            Drupal.futurehistory.codeAddress(i, noarview);
          });

          $('#futurehistory-coordinate-geocode-' + i).click(function(e) {
            Drupal.futurehistory.codeCoordinates(i, noarview);
          });


          // Get default values
          lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
          lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
          dist = parseFloat(mapDefaults.dist);
          direction = parseFloat(mapDefaults.direction);
          angle = parseFloat(mapDefaults.angle);
          noarview = mapDefaults.noarview;
          coordinate_known = mapDefaults.coordinate_known;
          latLng = new google.maps.LatLng(lat, lng);

          // FIX googlemap hidden DIV bug with resize call on active Bootstrap TAB
          $('a[href="#edit-group_picture_position"]').click(function() {   // When tab is displayed...
            center = Drupal.futurehistory.maps[i].getCenter();
            google.maps.event.trigger(Drupal.futurehistory.maps[i], 'resize');         // fixes map display
            Drupal.futurehistory.maps[i].setCenter(center);                            // centers map correctly
          });
    
          // Check coordinates known enabled and hide the adress field
          if (coordinate_known == 0){
            $("#futurehistory-coordinate-wrapper-" + i).hide();
          }
          else {
            $("#futurehistory-coordinate-wrapper-" + i).show();
            $("#futurehistory-address-" + i).hide();            
          }
          // klick function 
          $("#futurehistory-coordinate_known-checkbox_" + i + " input").click(function(){ 
            if ($(this).is(':checked')){
              coordinate_known = 1;
              $("#futurehistory-address-" + i).hide();
              $("#futurehistory-coordinate-wrapper-" + i).show();
            }
            else{
              coordinate_known = 0;
              $("#futurehistory-address-" + i).show();
              $("#futurehistory-coordinate-wrapper-" + i).hide();
            }
          });


          // Check AR view enabled and activate the sliders
          $("#futurehistory-arview-" + i + " input").click(function(){ 
            if ($(this).is(':checked')){
              dist = 0;
              direction = 0;
              angle = 0;
              noarview = 1;
              Drupal.futurehistory.dist_sliders[i].slider("option", "value", dist);
              Drupal.futurehistory.direction_sliders[i].roundSlider("setValue", direction);
//              Drupal.futurehistory.direction_sliders[i].slider("option", "value", direction);
              Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ angle_slide_center , angle_slide_center ]);
              $('#futurehistory-dist-slider-' + i + ' input' ).attr('value', dist);
              $('#futurehistory-view_direction-slider-' + i + ' input' ).attr('value', direction);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', angle);
              $('#futurehistory-dist-slider-item-' + i + ' span').html(dist);
              $('#futurehistory-view_direction-slider-item-' + i + ' span').html(direction);
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
              Drupal.futurehistory.dist_sliders[i].slider("option", "disabled", true);
              Drupal.futurehistory.direction_sliders[i].roundSlider("disable");
              Drupal.futurehistory.angle_sliders[i].slider("option", "disabled", true);
              Drupal.futurehistory.line_a[i].setMap(null);
              Drupal.futurehistory.line_b[i].setMap(null);
              Drupal.futurehistory.pie[i].setMap(null);
            }
            else{
              noarview = 0;
              if (!dist){
                dist = 250;
                direction = 1;
                angle = 40;
              }
              var angle_slide_half = angle/2;
              var angle_min = angle_slide_center - angle_slide_half ;
              var angle_max = angle_slide_center + angle_slide_half ;
              Drupal.futurehistory.dist_sliders[i].slider("option", "disabled", false);
              Drupal.futurehistory.direction_sliders[i].roundSlider("enable");
              Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ angle_min, angle_max ]);
              Drupal.futurehistory.angle_sliders[i].slider("option", "disabled", false);
              Drupal.futurehistory.dist_sliders[i].slider("option", "value", dist);
              $('#futurehistory-dist-slider-' + i + ' input' ).attr('value', dist);
              $('#futurehistory-view_direction-slider-' + i + ' input' ).attr('value', direction);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', angle);
              $('#futurehistory-dist-slider-item-' + i + ' span').html(dist);
              $('#futurehistory-view_direction-slider-item-' + i + ' span').html(direction);
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              latLng = new google.maps.LatLng(lat, lng);
              Drupal.futurehistory.setMapArrow(latLng, i, dist, direction, angle);
            }
          });
  
          // Build the Sliders
          Drupal.futurehistory.dist_sliders[i] = $("#futurehistory-dist-slider-" + i + " ").slider({
            value: dist,
            min: 10,
            max: 300,
            step: 1,
            disabled: false,
            animate: true,
            slide : function( event, ui ) {
              $('#futurehistory-dist-slider-item-' + i + ' span').html(ui.value);
              $('#futurehistory-dist-slider-' + i + ' input' ).attr('value', ui.value);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              latLng = new google.maps.LatLng(lat, lng);
              Drupal.futurehistory.setMapArrow(latLng, i, ui.value, direction, angle);
              dist = ui.value;
            }
          });

          Drupal.futurehistory.direction_sliders[i] = $("#futurehistory-view_direction-slider-" + i + " ").roundSlider({
            sliderType: "min-range",
            handleShape: "round",
            width: 22,
            radius: 100,
            editableTooltip: false,
            showTooltip: false,
            startAngle: 90,
            max: "360",
            handleSize: "+8",
            radius: 68,
            width: 9,
            drag: function (ui) {
			  $('#futurehistory-view_direction-slider-item-' + i + ' span').html(ui.value);
              $('#futurehistory-view_direction-slider-' + i + ' input' ).attr('value', ui.value);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              latLng = new google.maps.LatLng(lat, lng);
              Drupal.futurehistory.setMapArrow(latLng, i, dist, ui.value, angle);
              direction = ui.value;
            },
            change: function (ui) {
			  $('#futurehistory-view_direction-slider-item-' + i + ' span').html(ui.value);
              $('#futurehistory-view_direction-slider-' + i + ' input' ).attr('value', ui.value);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              latLng = new google.maps.LatLng(lat, lng);
              Drupal.futurehistory.setMapArrow(latLng, i, dist, ui.value, angle);
              direction = ui.value;
            }
          });

          // Calculate and generate the angle slider
          var angle_slide_half = angle / 2;
          var angle_slide_min = angle_slide_center - angle_slide_half;
          var angle_slide_max = angle_slide_center + angle_slide_half;
    	  var old_angle_min = '';
    	  var old_angle_max = '';

          Drupal.futurehistory.angle_sliders[i] = $("#futurehistory-angle-slider-" + i + " ").slider({
            range: true,
            values: [angle_slide_min, angle_slide_max],
            min: 1,
            max: 160,
            step: 1,
            disabled: false,
            animate: false,

            slide : function( event, ui ) {
              var angle_min = ui.values[0];
              var angle_max = ui.values[1];
              angle = angle_max - angle_min;
              angle_slide_half = angle / 2 ;
           
              //check which slider changed and add the value to the other one
              if (angle_min != old_angle_min ){
                old_angle_min = angle_min;
                var new_max = angle_slide_center + angle_slide_half ;
                Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ angle_min, new_max ] );
              } else if (angle_max != old_angle_max ) {
                old_angle_max = angle_max; 
                var new_min = angle_slide_center - angle_slide_half ;
                Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ new_min, angle_max ] );
              // error? 
              } else {
                console.log('Hoppla');
              }
              // add the map features and animations.
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', ui.value);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              latLng = new google.maps.LatLng(lat, lng);
              Drupal.futurehistory.setMapArrow(latLng, i, dist, direction, angle);
            }
          });

  
          // Set map options
          mapOptions = {
            disableDefaultUI: true,
            zoom: 15,
            center: latLng,
            mapTypeId: google.maps.MapTypeId.HYBRID,
            zoomControl: true,
            tilt:0
          }
  
          /**
           *
           * Print Map with i index
           *
           **/
          Drupal.futurehistory.maps[i] = new google.maps.Map(document.getElementById("futurehistory-map-" + i), mapOptions);

          if (lat && lng) {
            // Set initial marker
            Drupal.futurehistory.codeLatLng(latLng, i, 'geocoder');
            Drupal.futurehistory.setMapMarker(latLng, i);
            //initial run: check noarview value. if arview on and no values avail set default
            if (!noarview ) {
              if (!dist){
                dist = 50;
                direction = 1;
                angle = 30;
              }
              var angle_slide_half = angle/2;
              var angle_min = angle_slide_center - angle_slide_half ;
              var angle_max = angle_slide_center + angle_slide_half ;
              Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ angle_min, angle_max ]);
              Drupal.futurehistory.setMapArrow(latLng, i, dist, direction, angle);
              Drupal.futurehistory.dist_sliders[i].slider("option", "value", dist);
              Drupal.futurehistory.direction_sliders[i].roundSlider("setValue" , direction);
              $('#futurehistory-dist-slider-' + i + ' input' ).attr('value', dist);
              $('#futurehistory-view_direction-slider-' + i + ' input' ).attr('value', direction);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', angle);
              $('#futurehistory-dist-slider-item-' + i + ' span').html(dist);
              $('#futurehistory-view_direction-slider-item-' + i + ' span').html(direction);
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
            }
            if (noarview) {
              dist = 0;
              direction = 0;
              angle = 0;

              Drupal.futurehistory.dist_sliders[i].slider("option", "value", dist);
              Drupal.futurehistory.direction_sliders[i].roundSlider("setValue" , direction);
              Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ angle_slide_center , angle_slide_center ]);
              $('#futurehistory-dist-slider-' + i + ' input' ).attr('value', dist);
              $('#futurehistory-view_direction-slider-' + i + ' input' ).attr('value', direction);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', angle);
              $('#futurehistory-dist-slider-item-' + i + ' span').html(dist);
              $('#futurehistory-view_direction-slider-item-' + i + ' span').html(direction);
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
              Drupal.futurehistory.dist_sliders[i].slider("option", "disabled", true);
              Drupal.futurehistory.direction_sliders[i].roundSlider("disable");
              Drupal.futurehistory.angle_sliders[i].slider("option", "disabled", true);
            }
          }

          // Listener to set marker
          google.maps.event.addListener(Drupal.futurehistory.markers[i], 'dragend', function(me) {
            Drupal.futurehistory.codeLatLng(me.latLng, i, 'marker');
            if (!noarview ) {
                Drupal.futurehistory.setMapArrow(me.latLng, i, dist, direction, angle);
              }
              latLng = me.latLng;
          } );

          google.maps.event.addListener(Drupal.futurehistory.maps[i], 'click', function(me) {
            // Set a timeOut so that it doesn't execute if dbclick is detected
            singleClick = setTimeout(function() {
              Drupal.futurehistory.codeLatLng(me.latLng, i, 'marker');
              Drupal.futurehistory.setMapMarker(me.latLng, i);
              if (!noarview ) {
                Drupal.futurehistory.setMapArrow(me.latLng, i, dist, direction, angle);
              }
              latLng = me.latLng;
            }, 500);
          });

          // Detect double click to avoid setting marker
          google.maps.event.addListener(Drupal.futurehistory.maps[i], 'dblclick', function(me) {
            clearTimeout(singleClick);
          });
        })
      });
    }
  };
})(jQuery);
