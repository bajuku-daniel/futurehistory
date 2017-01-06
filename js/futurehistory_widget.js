(function ($) {

  Drupal.futurehistory = Drupal.futurehistory || {};
  Drupal.futurehistory.maps = Drupal.futurehistory.maps || {};
  Drupal.futurehistory.direction_sliders = Drupal.futurehistory.direction_sliders || {};
  Drupal.futurehistory.angle_sliders = Drupal.futurehistory.angle_sliders || {};
  Drupal.futurehistory.markers = Drupal.futurehistory.markers || {};
  Drupal.futurehistory.line_a = Drupal.futurehistory.line_a || {};
  Drupal.futurehistory.line_b = Drupal.futurehistory.line_b || {};
  Drupal.futurehistory.pie = Drupal.futurehistory.pie || {};

  geocoder = new google.maps.Geocoder();

  var dist = 250 ;
  var angle_slide_center = 80;
  var lat;
  var lng;
  var direction;
  var angle;
  var latLng;
  var noarview;
  var coordinate_known;
  var mapOptions;
  var mapZoom = 10;
  var initial;
  var initial_city;

  var fh_marker_location = new google.maps.MarkerImage(
    '/sites/default/files/gmap-files/location.png',
    new google.maps.Size(15, 32),
    new google.maps.Point(0, 0), //origin
    new google.maps.Point(7, 32) //anchor point
  );

  //google map style elements
  var map_styles = [ { "featureType": "poi.park", "stylers": [ { "visibility": "on" } ] },{ "featureType": "poi.attraction", "stylers": [ { "visibility": "on" } ] },{ "featureType": "poi.business", "stylers": [ { "visibility": "off" } ] },{ "featureType": "poi.government", "stylers": [ { "visibility": "on" } ] },{ "featureType": "poi.medical", "stylers": [ { "visibility": "off" } ] },{ "featureType": "poi.school", "stylers": [ { "visibility": "off" } ] },{ "featureType": "poi.place_of_worship", "stylers": [ { "visibility": "on" } ] },{ "featureType": "poi.school", "stylers": [ { "visibility": "off" } ] }];


/**
   * Google Autocomplete select first on Enter function
   */
 Drupal.futurehistory.selectFirstOnEnter = function(input){
    var _addEventListener = (input.addEventListener) ? input.addEventListener : input.attachEvent;
    function addEventListenerWrapper(type, listener) {
      if (type == "keydown") {
        var orig_listener = listener;
        listener = function (event) {
          var suggestion_selected = $(".pac-item-selected").length > 0;
          if ((event.which == 13 ) && !suggestion_selected) {
            var simulated_downarrow = $.Event("keydown", {
              keyCode:40,
              which:40
            });
            orig_listener.apply(input, [simulated_downarrow]);
          }
          orig_listener.apply(input, [event]);
        };
      }
      _addEventListener.apply(input, [type, listener]);
    }
    if (input.addEventListener) {
      input.addEventListener = addEventListenerWrapper;
    } else if (input.attachEvent) {
      input.attachEvent = addEventListenerWrapper;
    }
}

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
    console.log(latLng.lat());
    // Update the address field
    if ((op == 'marker' || op == 'geocoder' || op == 'initial') && geocoder) {
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
              console.log(itemCity);
            }
          });
          $('#futurehistory-address-' + i + ' input').val(results[0].formatted_address);
          if (op == 'geocoder' || op == 'initial') {
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

  /**
   * Get the location from the address field
   */
  Drupal.futurehistory.codeAddress = function(i, noarview, address, op) {
   // var address = $('#futurehistory-address-' + i + ' input').val();
    geocoder.geocode( { 'address': address }, function(results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        console.log(results[0].geometry.viewport);
        Drupal.futurehistory.maps[i].setCenter(results[0].geometry.location);
        if (op != 'initial'){
          Drupal.futurehistory.codeLatLng(results[0].geometry.location, i, 'textinput');
          Drupal.futurehistory.setMapMarker(results[0].geometry.location, i);
        } else {
          Drupal.futurehistory.codeLatLng(results[0].geometry.location, i, 'textinput');
        }
        // use the viewport if we have one
        if (results[0].geometry.viewport && op != 'initial') {
          Drupal.futurehistory.setViewport(i,results[0].geometry.viewport)
        }
        else {
          Drupal.futurehistory.setZoom(i, results[0].geometry.location_type);
        }

        if (!noarview && op != 'initial') {
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
    if (!noarview) {
      Drupal.futurehistory.setMapArrow(coordinates, i, dist, direction, angle);
    }
    latLng = coordinates;
  }

  /**
  *
  * Set Viewbox function
  *
  */
  Drupal.futurehistory.setViewport = function(i, viewport) {
    Drupal.futurehistory.maps[i].fitBounds(viewport);
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
      draggable: true,
      position: latLng,
      id: 'ansicht_marker',
      icon: fh_marker_location,
    });
    if (!noarview) {
      Drupal.futurehistory.setMapArrow(latLng, i, dist, direction, angle);
    }

    // we have to attach the fdragend function to every marker - not just the initial one
    google.maps.event.addListener(Drupal.futurehistory.markers[i], 'dragend', function(me) {
      Drupal.futurehistory.codeLatLng(me.latLng, i, 'marker');
      Drupal.futurehistory.setMapMarker(me.latLng, i);
      latLng = me.latLng
    });
  }

  /**
  * Set/Update the view direction on a map
  **/
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
    var arrow_half_openangle = angle/2;
    var point_a = google.maps.geometry.spherical.computeOffset(latLng, dist, direction - arrow_half_openangle);
    var point_b = google.maps.geometry.spherical.computeOffset(latLng, dist, direction + arrow_half_openangle);
    Drupal.futurehistory.line_a[i] = new google.maps.Polyline({
      path: [latLng, point_a],
      icons: [{
        icon: lineSymbol,
        offset: '100%'
       }],
       map: Drupal.futurehistory.maps[i]
    });

    Drupal.futurehistory.line_b[i] = new google.maps.Polyline({
      path: [latLng, point_b],
      icons: [{
        icon: lineSymbol,
        offset: '100%'
      }],
      map: Drupal.futurehistory.maps[i]
    });

    Drupal.futurehistory.pie[i] = new google.maps.Polygon({
      paths: [latLng, point_a, point_b],
      strokeColor: '#9E1F81',
      strokeOpacity: 0.6,
      strokeWeight: 1,
      fillColor: '#9E1F81',
      fillOpacity: 0.45,
      map: Drupal.futurehistory.maps[i]
    });
  }

  Drupal.behaviors.futurehistory = {
    attach: function(context, settings) {
      $.each(Drupal.settings.futurehistory.defaults, function(i, mapDefaults) {

        // Check if dialog confirmation should appear
        // trying to serialize form, not working if reediting node ?
        var beforeunload_enabled = true;
        var $form = jQuery("#ansicht-node-form");
        if($form.size() > 0) {
          var origForm = $form.find("input[type!='hidden']").serialize();
          if (jQuery(".custom-tooltip").size() > 0) {
            jQuery(".custom-tooltip").tooltipster({
              interactive: true
            });
          }
          jQuery("button:submit, .btn.btn-warning.form-submit").click(function (e) {
            beforeunload_enabled = false;
          });
          jQuery(window).bind("beforeunload", function () {
            var form_changed = ( $form.find("input[type!='hidden']").serialize() !== origForm && beforeunload_enabled);
            if (form_changed) {
              return "Do you realy want to leave this process?";
            }
          });
          jQuery(".form-type-dragndrop-upload label").removeAttr("for");
        }
        // END

        // disable form elements if no overlay image is set field_bild_overlay[und][0][fid]
        if (jQuery("input[name='field_bild_overlay[und][0][fid]']").attr('value') === "0") {
          $(".form-item-field-lizenz-overlay-und input:radio").attr('disabled', true);
          $("#edit-field-overlay-jahr-und-0-value").attr("disabled", "disabled");
          $("#edit-field-autor-overlay-und-0-value").attr("disabled", "disabled");
        }
        // after ajax call check if overlayimage has been uploaded - enable fields
       $( document ).ajaxStop(function() {
          if (jQuery("input[name='field_bild_overlay[und][0][fid]']").attr('value') !== "0") {
            $(".form-item-field-lizenz-overlay-und input:radio").removeAttr('disabled');
            $("#edit-field-overlay-jahr-und-0-value").removeAttr("disabled");
            $("#edit-field-autor-overlay-und-0-value").removeAttr("disabled");
          }else{
            $(".form-item-field-lizenz-overlay-und input:radio").attr('disabled', true);
            $("#edit-field-overlay-jahr-und-0-value").attr("disabled", "disabled");
            $("#edit-field-autor-overlay-und-0-value").attr("disabled", "disabled");
          }
        });


        // END

        // Only make this once - Drupal Performance.. ;)
        $("#futurehistory-map-" + i).once('futurehistory-googlemaps', function(){

          /**
          * Listeners and little magic für the whole "ansicht erstellen" node form
          **/
          // PREV NEXT Button function for the edit and add picture form
          $('.btnNext').click(function(){
            $("html, body").animate({ scrollTop: 0 }, "fast");
            $('.nav-tabs > .active').next('li').find('a').trigger('click');
          });
          $('.btnPrevious').click(function(){
            $("html, body").animate({ scrollTop: 0 }, "fast");
            $('.nav-tabs > .active').prev('li').find('a').trigger('click');
          });

          // FIX googlemap hidden DIV bug with resize call on active Bootstrap TAB
          $('.reloadMap').click(function() {   					                         // When tab is displayed...
            center = Drupal.futurehistory.maps[i].getCenter();
            google.maps.event.trigger(Drupal.futurehistory.maps[i], 'resize');           // fixes map display
            Drupal.futurehistory.maps[i].setCenter(center);                              // centers map correctly
          });
          $('a[href="#group_position_der_ansicht"]').on('shown.bs.tab', function(e) {   // When tab is displayed...
            center = Drupal.futurehistory.maps[i].getCenter();
            google.maps.event.trigger(Drupal.futurehistory.maps[i], 'resize');           // fixes map display
            Drupal.futurehistory.maps[i].setCenter(center);                              // centers map correctly
          });

          // Get default values from the input fields
          // todo: we need a initial marker at the user home city

          initial = $('#ansicht_initial').attr('value'); ;
          initial_city = $('#ansicht_initial_city').attr('value'); ;
          console.log(initial);
          console.log(initial_city);
          lat = $('#futurehistory-lat-' + i + ' input').attr('value');
          lng = $('#futurehistory-lng-' + i + ' input').attr('value');
          dist = parseFloat(mapDefaults.dist);
          direction = parseFloat($('#futurehistory-view_direction-slider-' + i + '-value input').attr('value'));
          angle = parseFloat($('#futurehistory-angle-slider-' + i + ' input').attr('value'));
          noarview = $("#futurehistory-arview-" + i + " input").prop( "checked" );
          coordinate_known = mapDefaults.coordinate_known;

          latLng = new google.maps.LatLng(lat, lng);


          // Add stupid google places Autocomplete to the Adress field
          var fh_inputfield = $('#futurehistory-address-' + i + ' input').attr('id');
          //select first on enter workaround
          var fh_input = Drupal.futurehistory.selectFirstOnEnter(document.getElementById(fh_inputfield));

          var fh_autocomplete = new google.maps.places.Autocomplete(document.getElementById(fh_inputfield));

          google.maps.event.addListener(fh_autocomplete, 'place_changed', function() {
            var address = $('#futurehistory-address-' + i + ' input').val();
            Drupal.futurehistory.codeAddress(i, noarview, address, 'geocoder');
          });


          // Attach listeners for the geocode function
          $('#futurehistory-address-' + i + ' input').keypress(function(ev){
            if(ev.which == 13){
              ev.preventDefault();
              var address = $('#futurehistory-address-' + i + ' input').val();
              Drupal.futurehistory.codeAddress(i, noarview, address, 'geocoder');
            }
          });
          $('#futurehistory-address-geocode-' + i).click(function(e) {
            var address = $('#futurehistory-address-' + i + ' input').val();
            Drupal.futurehistory.codeAddress(i, noarview, address, 'geocoder');
          });

          $('#futurehistory-coordinate-geocode-' + i).click(function(e) {
            Drupal.futurehistory.codeCoordinates(i, noarview);
          });


          // Attach listeners for "i know the coordinates" checkbox
          // Check coordinates known enabled and hide the address field
          //first check the defaults
          if (coordinate_known == 0){
            $("#futurehistory-coordinate-wrapper-" + i).hide();
          }
          else {
            $("#futurehistory-coordinate-wrapper-" + i).show();
            $("#futurehistory-address-" + i).hide();
          }
          // and than the click function
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
          // this only happens if we click the ar-view checkbox (clickFunction)
          $("#futurehistory-arview-" + i + " input").click(function(){
            if ($(this).is(':checked')){
              dist = 0;
              direction = 0;
              angle = 0;
              noarview = 1;
              Drupal.futurehistory.direction_sliders[i].roundSlider("setValue", direction);
              Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ angle_slide_center , angle_slide_center ]);
              $('#futurehistory-dist-slider-' + i + ' input' ).attr('value', dist);
              $('#futurehistory-view_direction-slider-' + i + '-value input' ).attr('value', direction);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', angle);
              $('#futurehistory-view_direction-slider-item-' + i + ' span').html(direction);
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
              Drupal.futurehistory.direction_sliders[i].roundSlider("disable");
              Drupal.futurehistory.angle_sliders[i].slider("option", "disabled", true);
              Drupal.futurehistory.line_a[i].setMap(null);
              Drupal.futurehistory.line_b[i].setMap(null);
              Drupal.futurehistory.pie[i].setMap(null);
            }
            else{
              noarview = 0;
              dist = 250;
              direction = 1;
              angle = 50;
              angle_slide_half = angle/2;
              angle_min = angle_slide_center - angle_slide_half ;
              angle_max = angle_slide_center + angle_slide_half ;
           	  last_range_min = angle_min;
         	  last_range_max = angle_max;
              Drupal.futurehistory.direction_sliders[i].roundSlider("setValue", direction);
              Drupal.futurehistory.direction_sliders[i].roundSlider("enable");
              Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [angle_min ,angle_max]);
              Drupal.futurehistory.angle_sliders[i].slider("option", "disabled", false);
              $('#futurehistory-dist-slider-' + i + ' input' ).attr('value', dist);
              $('#futurehistory-view_direction-slider-' + i + '-value input' ).attr('value', direction);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', angle);
              $('#futurehistory-view_direction-slider-item-' + i + ' span').html(direction);
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              latLng = new google.maps.LatLng(lat, lng);
              Drupal.futurehistory.setMapArrow(latLng, i, dist, direction, angle);
            }
          });

          //Direction Slider
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
			  $('#futurehistory-view_direction-slider-item-' + i + ' span.futurehistory-view_direction-slider-item-value').html(ui.value);
              $('#futurehistory-view_direction-slider-' + i + '-value input' ).attr('value', ui.value);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              latLng = new google.maps.LatLng(lat, lng);
              Drupal.futurehistory.setMapArrow(latLng, i, dist, ui.value, angle);
              direction = ui.value;
            },
            change: function (ui) {
			  $('#futurehistory-view_direction-slider-item-' + i + ' span.futurehistory-view_direction-slider-item-value').html(ui.value);
              $('#futurehistory-view_direction-slider-' + i + '-value input' ).attr('value', ui.value);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              Drupal.futurehistory.setMapArrow(latLng, i, dist, ui.value, angle);
              direction = ui.value;
            }
          });

          // angle slider
          // Calculate and generate the angle slider
          var angle_slide_half = angle / 2;
          var angle_slide_min = angle_slide_center - angle_slide_half;
          var angle_slide_max = angle_slide_center + angle_slide_half;

          if (angle_slide_min){
    	   var last_range_min = angle_slide_min;
    	   var last_range_max = angle_slide_max;
          }

          Drupal.futurehistory.angle_sliders[i] = $("#futurehistory-angle-slider-" + i + " ").slider({
            range: true,
            values: [angle_slide_min, angle_slide_max],
            min: 0,
            max: 161,
            step: 1,
            disabled: false,
            animate: false,

            slide : function( event, ui ) {
              var min = 0;
              var max = 161;
              var mid = 80;
              range_min = ui.values[0];
              range_max = ui.values[1];

              if (range_min > mid || range_min == mid) {
                range_min = mid - 1
              }
              if (range_max < mid || range_max == mid) {
                range_max = mid + 1
              }
              if (range_min > last_range_min || range_min < last_range_min){
                last_range_min = range_min;
                Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ range_min, max - range_min ] );
              }
              if (range_max > last_range_max || range_max < last_range_max){
                last_range_max = range_max;
                Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ max - range_max, range_max ] );
              }
              angle = range_max - range_min;
              $('#futurehistory-angle-slider-item-' + i + ' span.futurehistory-angle-slider-item-value').html(angle);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', angle);
              lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
              lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
              latLng = new google.maps.LatLng(lat, lng);
              Drupal.futurehistory.setMapArrow(latLng, i, dist, direction, angle);

            }
          });

          // Set map options
          mapOptions = {
            disableDefaultUI: true,
            zoom: mapZoom,
            center: latLng,
            styles: map_styles,
            mapTypeId: google.maps.MapTypeId.HYBRID,
            zoomControl: true,
            tilt:0
          }

          /**
           *
           * Print Map with i index and add the listner
           *
           **/
          Drupal.futurehistory.maps[i] = new google.maps.Map(document.getElementById("futurehistory-map-" + i), mapOptions);

          if (initial == 1) {
            Drupal.futurehistory.codeAddress(i, noarview, initial_city, 'initial');
            //$('#futurehistory-address-' + i + ' input').val(initial_city);

          } else if (lat && lng) {
            // Set saved marker
            Drupal.futurehistory.codeLatLng(latLng, i, 'initial');
            Drupal.futurehistory.setMapMarker(latLng, i);
            //initial run: check noarview value. if arview on and no values avail set fallback position (bookmark etc..)
            if (!noarview ) {
              if (!angle || !direction || !dist){
                console.log('ERROR: Keine Values bekannt - setze default');
                dist = 250;
                direction = 1;
                angle = 50;
              }
              angle_slide_half = angle/2;
              angle_min = angle_slide_center - angle_slide_half ;
              angle_max = angle_slide_center + angle_slide_half ;
              Drupal.futurehistory.direction_sliders[i].roundSlider("setValue", direction);
              Drupal.futurehistory.direction_sliders[i].roundSlider("enable");
              Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [angle_min ,angle_max]);
              Drupal.futurehistory.angle_sliders[i].slider("option", "disabled", false);
              $('#futurehistory-view_direction-slider-item-' + i + ' span').html(direction);
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
            }
            if (noarview) {
              //disable the slider
              Drupal.futurehistory.direction_sliders[i].roundSlider("setValue" , direction);
              Drupal.futurehistory.angle_sliders[i].slider( "option", "values", [ angle_slide_center , angle_slide_center ]);
              $('#futurehistory-view_direction-slider-' + i + '-value input' ).attr('value', direction);
              $('#futurehistory-angle-slider-' + i + ' input' ).attr('value', angle);
              $('#futurehistory-view_direction-slider-item-' + i + ' span').html(direction);
              $('#futurehistory-angle-slider-item-' + i + ' span').html(angle);
              Drupal.futurehistory.direction_sliders[i].roundSlider("disable");
              Drupal.futurehistory.angle_sliders[i].slider("option", "disabled", true);
            }
          }

          // add tha maps click listener and set the marker on this position
          Drupal.futurehistory.maps[i].addListener('click', function(e) {
            // Set a timeOut so that it doesn't execute if dbclick is detected
            singleClick = setTimeout(function() {
              latLng = e.latLng;
              // update the geocoder field
              Drupal.futurehistory.codeLatLng(latLng, i, 'marker');
              //set the marker
              Drupal.futurehistory.setMapMarker(latLng, i);
            }, 500);
          });
          // Detect double click to avoid setting marker
          Drupal.futurehistory.maps[i].addListener('dblclick', function(e) {
            clearTimeout(singleClick);
          });

        })
      });
    }
  };


  // http://stackoverflow.com/questions/38879742/is-it-possible-to-display-a-custom-message-in-the-beforeunload-popup
  // http://stackoverflow.com/questions/34172649/calling-a-javascript-function-when-google-chrome-is-closed
  // todo save form state
  // on unload check if data changed
  // $(window).bind('beforeunload', function(){
  //   return 'Do you realy want to leave this process?';
  // });


})(jQuery);
