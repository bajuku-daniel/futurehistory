(function ($) {

  Drupal.futurehistory = Drupal.futurehistory || {};
  Drupal.futurehistory.maps = Drupal.futurehistory.maps || {};
  Drupal.futurehistory.markers = Drupal.futurehistory.markers || {};

  Drupal.futurehistory.codeLatLng = function(latLng, i) {
    // Update the lat and lng input fields
    $('#futurehistory-lat-item-' + i + ' .futurehistory-lat-item-value').html(latLng.lat());
    $('#futurehistory-lng-item-' + i + ' .futurehistory-lng-item-value').html(latLng.lng());

    $('#futurehistory-lat-' + i + 'input').attr('value', latLng.lat());
    $('#futurehistory-lng-' + i + 'input').attr('value', latLng.lng());
  }


  Drupal.behaviors.futurehistory = {
    attach: function(context, settings) {
      var lat;
      var lng;
      var latLng;
      var mapOptions;

      $.each(Drupal.settings.futurehistory.defaults, function(i, mapDefaults) {
        Drupal.behaviors.futurehistory.id = i;
        Drupal.behaviors.futurehistory.defaults = mapDefaults;

        // Get default values
        lat = $('#futurehistory-lat-' + i + ' input').attr('value') == false ? mapDefaults.lat : $('#futurehistory-lat-' + i + ' input').attr('value');
        lng = $('#futurehistory-lng-' + i + ' input').attr('value') == false ? mapDefaults.lng : $('#futurehistory-lng-' + i + ' input').attr('value');
        latLng = new google.maps.LatLng(lat, lng);

        // Set map options
        mapOptions = {
          zoom: 9,
          center: {lat: 48, lng: 7},
          mapTypeId: google.maps.MapTypeId.TERRAIN,
        }

        var lineSymbol = {
          path: google.maps.SymbolPath.FORWARD_OPEN_ARROW
        };

        Drupal.futurehistory.maps[i] == new google.maps.Map(document.getElementById("futurehistory-map-" + i), mapOptions);

                
        //add map click event and update the Values
        google.maps.event.addListener(Drupal.futurehistory.maps[i], 'click', function(me) {
              Drupal.futurehistory.placePointOfView(me.latLng, i);
              Drupal.futurehistory.codeLatLng(me.latLng, i);
          });

        Drupal.futurehistory.placePointOfView = function(latLng, i) {
          if (Drupal.futurehistory.markers[i]){
            Drupal.futurehistory.markers[i].setMap(null);
          }
          var standpunkt = latLng;
          var distance = 20000;
          var heading = 270;
          var half_openangle = 30;
        
          var point_a = google.maps.geometry.spherical.computeOffset(standpunkt, distance, heading - half_openangle);
          var point_b = google.maps.geometry.spherical.computeOffset(standpunkt, distance, heading + half_openangle);
        
          Drupal.futurehistory.markers[i].line_a = new google.maps.Polyline({
            path: [standpunkt, point_a],
            icons: [{
              icon: lineSymbol,
              offset: '100%'
            }],
            map: Drupal.futurehistory.maps[i]
          });
        
          Drupal.futurehistory.markers[i].line_b = new google.maps.Polyline({
            path: [standpunkt, point_b],
            icons: [{
              icon: lineSymbol,
              offset: '100%'
            }],
            map: Drupal.futurehistory.maps[i]
          });
        
          Drupal.futurehistory.markers[i].pie = new google.maps.Polygon({
            paths: [standpunkt, point_a, point_b],
            strokeColor: '#FF0000',
            strokeOpacity: 0.6,
            strokeWeight: 1,
            fillColor: '#FF0000',
            fillOpacity: 0.35,
            map: Drupal.futurehistory.maps[i]
          });
        }
      });
    }
  };
})(jQuery);
