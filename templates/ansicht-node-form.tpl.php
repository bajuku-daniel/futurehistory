<?php
// Template file for the "Add Ansicht" form
// drupal _alter _theme _preprocess functions in futurehistory.module file
hide($form['group_add_picture']);
hide($form['group_picture_info']);
hide($form['group_position_der_ansicht']);
hide($form['group_picture_info']);
hide($form['group_lizenz_blid']);
hide($form['field_position_der_aufnahme']);
hide($form['group_overlay']);
hide($form['group_media']);
hide($form['ansicht_tabs']);
$ansicht_button_static = $ansicht_initial['submit_button_static'];

?>

<?php
if(strpos($_GET['q'], 'edit') !== FALSE){
  print '<h4 class="addAnsicht">Eigene Bilder bearbeiten</h4>';
}else{
  print '<h4 class="addAnsicht">Eigene Bilder einstellen</h4>';
}
if(isset($messages)){
  print $messages;
}
?>
<div class="container">
  <ul class="nav nav-tabs">
    <?php
    //first print the TABS and check if validation error or not
    $validation_error = 0;
    foreach ($form['ansicht_tabs'] as $tab => $tab_content) {
      if ($tab_content['validation_error'] == 1) {
        $validation_error = 1;
      }
    }
    $first_error = 1;
    foreach ($form['ansicht_tabs'] as $tab => $tab_content) {
      $R=0;
      if ($validation_error == 1 && $tab_content['validation_error'] == 1) {
        if ($first_error == 1 && isset($tab_content['tab_name'])) {
          print('<li class="active validation_error"><a href="#' . $tab . '" data-toggle="tab">' . $tab_content['tab_name'] . '</a></li>');
          $first_error = 0;
        }
        else {
          if ($first_error == 0 && isset($tab_content['tab_name'])) {
            print('<li class="validation_error"><a href="#' . $tab . '" data-toggle="tab">' . $tab_content['tab_name'] . '</a></li>');
        }
      }
      }
      else {
        if ($tab == 'group_add_picture' && $validation_error == 0 && isset($tab_content['tab_name'])) {
          print('<li class="active"><a href="#' . $tab . '" data-toggle="tab">' . $tab_content['tab_name'] . '</a></li>');
        }
        else {
          if (isset($tab_content['tab_name'])) {
            print('<li class=""><a href="#' . $tab . '" data-toggle="tab">' . str_replace('(optional)','',$tab_content['tab_name']) . ' </a></li>');
          }
        }
      }
    }
    ?>
  </ul>
  <input type="hidden" id="ansicht_initial"
         value="<?php print($ansicht_initial['initial']); ?>">
  <input type="hidden" id="ansicht_initial_city"
         value="<?php print($ansicht_initial['place']); ?>">
  <div class="tab-content">
    <?php
    // next print the tab content and the buttons - check validation and "button_static"
    // button static shows buttons in "entwurf" or "bearbeiten" modus (see the futurehistory.modul button function)
    // foreach: run through all tabs and tab contents to set the specific "buttons"
    $first_error = 1;
    foreach ($form['ansicht_tabs'] as $tab => $tab_content) {
      if ($ansicht_button_static == 0 && $validation_error == 1 && $tab_content['validation_error'] == 1 || $ansicht_button_static == 1 && $validation_error == 1 && $tab_content['validation_error'] == 1) {
        if ($first_error == 1) {
          $tab_pane = '<div class="tab-pane active validation_error" id="' . $tab . '">';
          $first_error = 0;
        }
        else {
          if ($first_error == 0) {
            $tab_pane = '<div class="tab-pane validation_error" id="' . $tab . '">';
          }
        }
        if ($tab == 'group_add_picture') {
          $form_buttons = '
          <div class="addAnsichtButtons">
            <a class="btn btn-primary btnNext">weiter</a>' .
            render($buttons) . '
          </div>
        ';
        }
        else {
          if ($tab == 'group_media') {
            $form_buttons = '
          <div class="addAnsichtButtons">
            <a class="btn btn-primary btnPrevious reloadMap">zurück</a>' .
              render($buttons) . '
          </div>
        ';
          }
          else {
            $form_buttons = '
          <div class="addAnsichtButtons">
            <a class="btn btn-primary btnPrevious reloadMap">zurück</a>
            <a class="btn btn-primary btnNext reloadMap">weiter</a>' .
              render($buttons) . '
          </div>
        ';
          }
        }
        // TODO: Clean the messy condition if & else query.. fast forward coding without structure :-O
      }
      else {
        if ($ansicht_button_static == 1 && $tab == 'group_add_picture' && $validation_error == 0) {
          $tab_pane = '<div class="tab-pane active" id="' . $tab . '">';
          $form_buttons = '
        <div class="addAnsichtButtons">
          <a class="btn btn-primary btnNext reloadMap">weiter</a>' .
            render($buttons) . '
        </div>
      ';
        }
        else {
          if ($ansicht_button_static == 1 && $tab == 'group_add_picture' && $validation_error == 1 && $tab_content['validation_error'] == 0) {
            $tab_pane = '<div class="tab-pane" id="' . $tab . '">';
            $form_buttons = '
        <div class="addAnsichtButtons">
          <a class="btn btn-primary btnNext reloadMap">weiter</a>' .
              render($buttons) . '
        </div>
      ';
          }
          else {
            if ($ansicht_button_static == 1) {
              $tab_pane = '<div class="tab-pane" id="' . $tab . '">';
              if ($tab == 'group_media') {
                $form_buttons = '
          <div class="addAnsichtButtons">
            <a class=" reloadMap btn btn-primary btnPrevious">zurück</a>' .
                  render($buttons) . '
          </div>
        ';
              }
              else {
                $form_buttons = '
          <div class="addAnsichtButtons">
            <a class="btn btn-primary btnPrevious reloadMap ">zurück</a>
            <a class="btn btn-primary btnNext">weiter</a>' .
                  render($buttons) . '
          </div>
        ';
              }
            }
            else {
              if ($ansicht_button_static == 0 && $tab == 'group_add_picture' && $validation_error == 0) {
                $tab_pane = '<div class="tab-pane active" id="' . $tab . '">';
                $form_buttons = '
        <div class="addAnsichtButtons">
          <a class="btn btn-primary btnNext">weiter</a>
        </div>
      ';
              }
              else {
                if ($ansicht_button_static == 0) {
                  $tab_pane = '<div class="tab-pane" id="' . $tab . '">';
                  if ($tab == 'group_media') {
                    $form_buttons = '
          <div class="addAnsichtButtons">
            <a class=" reloadMap btn btn-primary btnPrevious">zurück</a>' .
                      render($buttons) . '
          </div>
        ';
                  }
                  else {
                    $form_buttons = '
          <div class="addAnsichtButtons">
            <a class="btn btn-primary btnPrevious reloadMap ">zurück</a>
            <a class="btn btn-primary btnNext">weiter</a>
          </div>
        ';
                  }
                }
              }
            }
          }
        }
      }
      print($tab_pane);
      if ($tab == 'group_position_der_ansicht') {
        print future_history_replace_tab_legend(render($form[$tab]['field_position_der_aufnahme']),$tab,$tab_content['tab_name']);
//        print future_history_replace_tab_legend(render($form[$tab]['field_stadt']),$tab,$tab_content['tab_name']);
        print render($form[$tab]['field_stadt']);
        print future_history_replace_tab_legend(render($form['group_overlay']),"group_overlay",$form['group_overlay']['#title']);
      }elseif ($tab == 'group_picture_info'){
        print future_history_replace_tab_legend(render($form['group_picture_info']),"group_picture_info",$form['group_picture_info']['#title']);
        print future_history_replace_tab_legend(render($form['group_lizenz_blid']),"group_lizenz_blid",$form['group_lizenz_blid']['#title']);
      }
      else {
        if (isset($tab_content['tab_name'])) {
          print future_history_replace_tab_legend(render($form[$tab]), $tab, $tab_content['tab_name']);
        }
      }
      print($form_buttons);
      print('</div>');
    }
    print('</div>');

    print drupal_render_children($form);
    ?>
  </div>
