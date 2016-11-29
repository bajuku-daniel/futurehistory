<?php
// Template file for the "Add Ansicht" form
// drupal _alter _theme _preprocess functions in futurehistory.module file
hide($form['group_add_picture']);
hide($form['group_picture_info']);
hide($form['group_position_der_ansicht']);
hide($form['field_position_der_aufnahme']);
hide($form['group_overlay']);
hide($form['group_media']);
$ansicht_button_static = $ansicht_initial['submit_button_static'];

?>
<div class="container">
  <h4 class="addAnsicht">Eigene Bilder einstellen</h4>
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
      if ($validation_error == 1 && $tab_content['validation_error'] == 1) {
        if ($first_error == 1) {
          print('<li class="active validation_error"><a href="#' . $tab . '" data-toggle="tab">' . $tab_content['tab_name'] . '</a></li>');
          $first_error = 0;
        }
        else {
          if ($first_error == 0) {
            print('<li class="validation_error"><a href="#' . $tab . '" data-toggle="tab">' . $tab_content['tab_name'] . '</a></li>');
          }
        }
      }
      else {
        if ($tab == 'group_add_picture' && $validation_error == 0) {
          print('<li class="active"><a href="#' . $tab . '" data-toggle="tab">' . $tab_content['tab_name'] . '</a></li>');
        }
        else {
          print('<li class=""><a href="#' . $tab . '" data-toggle="tab">' . $tab_content['tab_name'] . '</a></li>');
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
        print render($form[$tab]['field_position_der_aufnahme']);
        print render($form[$tab]['field_stadt']);
        print render($form['group_overlay']);
      }
      else {
        print render($form[$tab]);
      }

      print($form_buttons);
      print('</div>');
    }
    print('</div>');

    print drupal_render_children($form);
    ?>
  </div>
