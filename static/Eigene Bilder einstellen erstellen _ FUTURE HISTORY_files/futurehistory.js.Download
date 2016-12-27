(function ($) {

  // Style the gmap markers blue and violet
  var fh_marker_blue = new google.maps.MarkerImage(
    '/sites/default/files/gmap-files/fh-poi-blue.png',
    new google.maps.Size(25, 25),
    new google.maps.Point(0, 0), //origin
    new google.maps.Point(12, 12) //anchor point
  );
  var fh_marker_violet = new google.maps.MarkerImage(
    '/sites/default/files/gmap-files/fh-poi-violet.png',
    new google.maps.Size(25, 25),
    new google.maps.Point(0, 0), //origin
    new google.maps.Point(12, 12) //anchor point
  );

  //Start drupal behaviors
  Drupal.behaviors.futurehistoryDetails = {
    attach: function (context, settings) {

      // div once funciton for the click events in the action navigation 
      // open and close the toggles and start and stop the audio
      $('.ansicht-details-aktion').once(function(){
        $(".ansicht-audio-button").click(function(){
          $(".audio-container").slideToggle("slow");
          $('#ansicht-audio-player').trigger("play");
        });
        $(".ansicht-share-button").click(function(){
          $(".share-container").slideToggle("slow");
        });
        $(".ansicht-collection-button-message").click(function(){
          $(".collection-container").slideToggle("slow");
        });
        $(".audio-close").click(function(){
          $(".audio-container").slideUp("fast");
          $('#ansicht-audio-player').trigger("pause");
        });
        $(".share-close").click(function(){
          $(".share-container").slideUp("fast");
        });
      });
       
      // get the geo variables out of the hidden input fields in the node--ansicht.tpl.php files 
      var lat = $('#ansicht_lat').val();
      var lng = $('#ansicht_lng').val();
      var angle = parseInt($('#ansicht_angle').val());
      var heading = parseInt($('#ansicht_direction').val());
      // make new Latlng object
      var standpunkt = new google.maps.LatLng(lat,lng);
     
      
      // Overview MAP STUFF
      $('#ansicht-overview-map', context).each(function() {
        var $this = $(this);

        Drupal.futurehistoryDetails = {};
        mapCenter  = new google.maps.LatLng(lat,lng);
        mapZoom = 16;

        Drupal.futurehistoryDetails.map = new google.maps.Map(this, {
          center: mapCenter,
          zoom: mapZoom,
          mapTypeId: google.maps.MapTypeId.SATELLITE,
          mapTypeControl: false,
          zoomControl: true,
          streetViewControl:false,
          rotateControl:false,
          scrollwheel: false,
        });
        // set tilt to 0 and stop rotatign the map
        Drupal.futurehistoryDetails.map.setTilt(0); 

        // set the ansicht_marker
        Drupal.futurehistoryDetails.marker = new google.maps.Marker({
          position:standpunkt,
          map: Drupal.futurehistoryDetails.map,
          icon: fh_marker_violet,
        });
      
        // if angle is more than 0 print the "blickwinkel PIE"
        if (angle != 0) {
          var lineSymbol = {
            path: google.maps.SymbolPath.FORWARD_OPEN_ARROW
          };

          var distance = 300;
          var half_openangle = angle/2;
        
          var point_a = google.maps.geometry.spherical.computeOffset(standpunkt, distance, heading - half_openangle);
          var point_b = google.maps.geometry.spherical.computeOffset(standpunkt, distance, heading + half_openangle);
        
          line_a = new google.maps.Polyline({
            path: [standpunkt, point_a],
            icons: [{
              icon: lineSymbol,
              offset: '100%'
            }],
            map: Drupal.futurehistoryDetails.map,
          });
        
          line_b = new google.maps.Polyline({
            path: [standpunkt, point_b],
            icons: [{
              icon: lineSymbol,
              offset: '100%'
            }],
            map: Drupal.futurehistoryDetails.map,
          });
  
          pie = new google.maps.Polygon({
            paths: [standpunkt, point_a, point_b],
            strokeColor: '#9E1F81',
            strokeOpacity: 0.6,
            strokeWeight: 1,
            fillColor: '#9E1F81',
            fillOpacity: 0.45,
            map: Drupal.futurehistoryDetails.map,
          });
        }

      }); // end MAP each function         

    }  // end beaviors and atach function
  }
})(jQuery);

