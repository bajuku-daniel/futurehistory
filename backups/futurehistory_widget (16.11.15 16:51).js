(function ($) {

  Drupal.futurehistory = Drupal.futurehistory || {};
  Drupal.futurehistory.maps = Drupal.futurehistory.maps || {};
  Drupal.futurehistory.sliders = Drupal.futurehistory.maps || {};
  Drupal.futurehistory.markers = Drupal.futurehistory.markers || {};

 // Drupal.futurehistory.codeLatLng = function(latLng, i) {
    // Update the lat and lng input fields
   // $('#futurehistory-lat-item-' + i + ' .futurehistory-lat-item-value').html(latLng.lat());
    //$('#futurehistory-lng-item-' + i + ' .futurehistory-lng-item-value').html(latLng.lng());

    //$('#futurehistory-lat-' + i + 'input').attr('value', latLng.lat());
   // $('#futurehistory-lng-' + i + 'input').attr('value', latLng.lng());
  //}


  Drupal.futurehistory.setMapArrow = function(latLng, i, dist) {
    // remove old marker
    if (Drupal.futurehistory.markers[i]) {
      Drupal.futurehistory.markers[i].setMap(null);
    }
  }
 


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
  }
 


  Drupal.behaviors.futurehistory = {
    attach: function(context, settings) {
      var lat;
      var lng;
      var dist;
      var latLng;
      var mapOptions;

      $.each(Drupal.settings.futurehistory.defaults, function(i, mapDefaults) {
        Drupal.behaviors.futurehistory.id = i;
        Drupal.behaviors.futurehistory.defaults = mapDefaults;

        // Get default values
        lat = Drupal.behaviors.futurehistory.defaults.lat;
        lng = Drupal.behaviors.futurehistory.defaults.lng;
        dist = Drupal.behaviors.futurehistory.defaults.dist;
        latLng = new google.maps.LatLng(lat, lng);
        
         Drupal.futurehistory.sliders[i] = $("#futurehistory-dist-slider-" + i + " ").slider({
          value: dist,
          min: 0,
          max: 500,
          step: 1,
          animate: true,
          slide : function( event, ui ) {
            $('#futurehistory-dist-slider-item-' + i + ' span').html(ui.value);
            $('#futurehistory-dist-slider-' + i + ' input' ).attr('value', ui.value);
            Drupal.futurehistory.setMapArrow(latLng, i, ui.value);
          }
        });

        // Set map options
        mapOptions = {
          zoom: 9,
          center: latLng,
          mapTypeId: google.maps.MapTypeId.TERRAIN
        }

        Drupal.futurehistory.maps[i] = new google.maps.Map(document.getElementById("futurehistory-map-" + i), mapOptions);

        //add map click event for marker and update the Values
        //google.maps.event.addListener(Drupal.futurehistory.maps[i], 'click', function(me) {
         Drupal.futurehistory.setMapMarker(latLng, i);
        //  Drupal.futurehistory.codeLatLng(me.latLng, i);
       // });
  
      });
    }
  };
})(jQuery);
