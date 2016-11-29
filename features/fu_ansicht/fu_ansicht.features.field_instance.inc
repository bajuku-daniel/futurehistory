<?php
/**
 * @file
 * fu_ansicht.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function fu_ansicht_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-ansicht-field_app_transfer_checksum'.
  $field_instances['node-ansicht-field_app_transfer_checksum'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_app_transfer_checksum',
    'label' => 'App Transfer checksum',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'field_hidden',
      'settings' => array(),
      'type' => 'field_hidden',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_audio_datei'.
  $field_instances['node-ansicht-field_audio_datei'] = array(
    'bundle' => 'ansicht',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_url_plain',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_audio_datei',
    'label' => 'Audio Datei',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'ansicht-audio',
      'file_extensions' => 'mp3',
      'filefield_paths' => array(
        'active_updating' => 0,
        'file_name' => array(
          'options' => array(
            'pathauto' => FALSE,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => 'aa-[file:owner:uid]-[file:fid]-[file:timestamp:raw].[file:extension]',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => FALSE,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => 'ansicht-audio',
        ),
        'redirect' => FALSE,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '25 MB',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'dragndrop_upload_file',
      'settings' => array(
        'allow_replace' => 0,
        'droppable_area_text' => 'Zieh Deine Audio Datei per Drag and Drop in diesen Bereich ',
        'media_browser' => 0,
        'multiupload' => 0,
        'progress_indicator' => 'throbber',
        'standard_upload' => 1,
        'upload_button_text' => 'Hochladen',
        'upload_event' => 'auto',
      ),
      'type' => 'dragndrop_upload_file',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_autor_overlay'.
  $field_instances['node-ansicht-field_autor_overlay'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 18,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_autor_overlay',
    'label' => 'Autor',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'filtered_html' => 'filtered_html',
          'full_html' => 'full_html',
          'php_code' => 'php_code',
          'plain_text' => 'plain_text',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'filtered_html' => array(
              'weight' => 0,
            ),
            'full_html' => array(
              'weight' => 1,
            ),
            'php_code' => array(
              'weight' => 11,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_bild'.
  $field_instances['node-ansicht-field_bild'] = array(
    'bundle' => 'ansicht',
    'default_value' => array(),
    'deleted' => 0,
    'description' => 'Lade hier das Bild für deine Ansicht hoch. Das Bild wird für unsere Ansicht automatisch auf eine Größe von maximal 800 Pixeln Breite oder maximal 600 Pixeln Höhe skaliert, so das für dich keine Arbeit mehr anfällt.

',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'ansicht_bild_portal',
        ),
        'type' => 'image',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bild',
    'label' => 'Bild',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'ansicht-pictures',
      'file_extensions' => 'png gif jpg jpeg',
      'filefield_paths' => array(
        'active_updating' => 0,
        'file_name' => array(
          'options' => array(
            'pathauto' => FALSE,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => 'ap-[file:owner:uid]-[file:fid]-[file:timestamp:raw].[file:extension]',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => FALSE,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => 'ansicht-pictures',
        ),
        'redirect' => FALSE,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '5 MB',
      'max_resolution' => '',
      'min_resolution' => '200x200',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'dragndrop_upload_image',
      'settings' => array(
        'allow_replace' => 0,
        'droppable_area_text' => 'Zieh Dein Bild per Drag and Drop in diesen Bereich ',
        'media_browser' => 0,
        'multiupload' => 0,
        'preview_image_style' => 'ansicht_bild_preview',
        'progress_indicator' => 'throbber',
        'standard_upload' => 1,
        'upload_button_text' => 'Hochladen',
        'upload_event' => 'auto',
      ),
      'type' => 'dragndrop_upload_image',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_bild_overlay'.
  $field_instances['node-ansicht-field_bild_overlay'] = array(
    'bundle' => 'ansicht',
    'deleted' => 0,
    'description' => 'Wenn du einen Bild-Slider erstellen möchtest, lade hier das Vergleichsbild für diese Funktion hoch. Das Vergleichsbild muß vor dem Hochladen ggf. mit einem entsprechendem Bildbearbeitungsprogramm angepasst werden.
',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'ansicht_bild_portal',
        ),
        'type' => 'image',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bild_overlay',
    'label' => 'Vergleichsbild Datei',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'ansicht-pictures-overlay',
      'file_extensions' => 'png gif jpg jpeg',
      'filefield_paths' => array(
        'active_updating' => 0,
        'file_name' => array(
          'options' => array(
            'pathauto' => FALSE,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => 'ao-[file:owner:uid]-[file:fid]-[file:timestamp:raw].[file:extension]',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => FALSE,
            'slashes' => 0,
            'transliterate' => 0,
          ),
          'value' => 'ansicht-pictures-overlay',
        ),
        'redirect' => FALSE,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'max_filesize' => '5 mb',
      'max_resolution' => '',
      'min_resolution' => '200x200',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'dragndrop_upload_image',
      'settings' => array(
        'allow_replace' => 0,
        'droppable_area_text' => 'Zieh Dein Vergleichsbild per Drag and Drop in diesen Bereich ',
        'media_browser' => 0,
        'multiupload' => 0,
        'preview_image_style' => 'ansicht_bild_preview',
        'progress_indicator' => 'throbber',
        'standard_upload' => 1,
        'upload_button_text' => 'Hochladen',
        'upload_event' => 'auto',
      ),
      'type' => 'dragndrop_upload_image',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_bildquelle'.
  $field_instances['node-ansicht-field_bildquelle'] = array(
    'bundle' => 'ansicht',
    'default_value' => array(
      0 => array(
        'value' => 'Gebe hier die Bildquelle an',
        'format' => 'plain_text',
      ),
    ),
    'deleted' => 0,
    'description' => 'Gebe hier die Bildquelle an',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bildquelle',
    'label' => 'Bildquelle',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'filtered_html' => 0,
          'full_html' => 0,
          'php_code' => 0,
          'plain_text' => 'plain_text',
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 1,
        'default_order_wrapper' => array(
          'formats' => array(
            'filtered_html' => array(
              'weight' => 2,
            ),
            'full_html' => array(
              'weight' => 1,
            ),
            'php_code' => array(
              'weight' => 11,
            ),
            'plain_text' => array(
              'weight' => 0,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_bildquelle_url'.
  $field_instances['node-ansicht-field_bildquelle_url'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bildquelle_url',
    'label' => 'Bildquelle URL',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'filtered_html' => 'filtered_html',
          'full_html' => 'full_html',
          'php_code' => 'php_code',
          'plain_text' => 'plain_text',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'filtered_html' => array(
              'weight' => 0,
            ),
            'full_html' => array(
              'weight' => 1,
            ),
            'php_code' => array(
              'weight' => 11,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_genauigkeit'.
  $field_instances['node-ansicht-field_genauigkeit'] = array(
    'bundle' => 'ansicht',
    'default_value' => array(
      0 => array(
        'value' => 'genau',
      ),
    ),
    'deleted' => 0,
    'description' => 'Genauigkeit XXXXXX',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 15,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_genauigkeit',
    'label' => 'Genauigkeit',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_jahr'.
  $field_instances['node-ansicht-field_jahr'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Jahr XXXXXX',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 12,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_jahr',
    'label' => 'Jahr',
    'required' => 1,
    'settings' => array(
      'max' => 2030,
      'min' => 800,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_kategorie'.
  $field_instances['node-ansicht-field_kategorie'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Zu welcher Kategorie gehört dein Bild?',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_kategorie',
    'label' => 'Kategorie',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_lizenz'.
  $field_instances['node-ansicht-field_lizenz'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Unter welcher Lizenz willst du dieses Bild veröffentlichen?',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lizenz',
    'label' => 'Lizenz',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_lizenz_overlay'.
  $field_instances['node-ansicht-field_lizenz_overlay'] = array(
    'bundle' => 'ansicht',
    'default_value' => array(
      0 => array(
        'tid' => 15,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'i18n_taxonomy',
        'settings' => array(),
        'type' => 'i18n_taxonomy_term_reference_link',
        'weight' => 17,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_lizenz_overlay',
    'label' => 'Lizenz Vergleichsbild',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_overlay_jahr'.
  $field_instances['node-ansicht-field_overlay_jahr'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_overlay_jahr',
    'label' => 'Jahr',
    'required' => 0,
    'settings' => array(
      'max' => 2020,
      'min' => 800,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_position_der_aufnahme'.
  $field_instances['node-ansicht-field_position_der_aufnahme'] = array(
    'bundle' => 'ansicht',
    'default_value' => array(
      0 => array(
        'lat' => 47.9990077,
        'lng' => '7.84210429999996',
        'dist' => 250,
        'view_direction' => 1,
        'angle' => 50,
        'coordinate_known' => 0,
        'address' => array(
          'field' => 'Wentzingerstraße 1, 79106 Freiburg im Breisgau, Deutschland',
        ),
        'coordinate_known_wrapper' => array(
          'coordinate_lat' => 47.9990077,
          'coordinate_lng' => '7.84210429999996',
        ),
        'view_direction_slider' => 1,
        'noarview' => 0,
        'field_type' => 'futurehistory_field',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'services_views',
        'settings' => array(
          'data_element_key' => '',
          'skip_empty_values' => 0,
          'skip_safe' => 0,
          'skip_text_format' => 1,
          'term_name' => 1,
        ),
        'type' => 'services',
        'weight' => 11,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_position_der_aufnahme',
    'label' => 'Bildposition',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'futurehistory',
      'settings' => array(
        'marker_draggable' => 1,
        'scrollwheel' => 0,
      ),
      'type' => 'futurehistory_map',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_stadt'.
  $field_instances['node-ansicht-field_stadt'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Dieses Feld wird Automatisch ausgefüllt sobald die Position des Bildes Festgelegt ist.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_stadt',
    'label' => 'Bildposition',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_tags'.
  $field_instances['node-ansicht-field_tags'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Hier hast du die Möglichkeit einige Suchbegriffe / Tags zu deinem Bild einzugeben. Die einzelnen Schlagworte werden mit  Komma "," getrennt.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_tags',
    'label' => 'Suchbegriffe / Tags',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_deluxe_path' => 'autocomplete_deluxe/taxonomy',
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_teaser_kurzetext'.
  $field_instances['node-ansicht-field_teaser_kurzetext'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Gebe hier einen Kurztext/Teaser ein. (Maximal 60 Zeichen)',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_teaser_kurzetext',
    'label' => 'Kurztext / Teaser',
    'required' => 1,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'filtered_html' => 'filtered_html',
          'full_html' => 'full_html',
          'php_code' => 'php_code',
          'plain_text' => 'plain_text',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'filtered_html' => array(
              'weight' => 0,
            ),
            'full_html' => array(
              'weight' => 1,
            ),
            'php_code' => array(
              'weight' => 11,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 1,
        'maxlength_js_label' => 'Maximal @limit Zeichen. Verbleibend: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_text'.
  $field_instances['node-ansicht-field_text'] = array(
    'bundle' => 'ansicht',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Beschreibe dein Bild hier',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_text',
    'label' => 'Beschreibung der Ansicht',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-ansicht-field_urheber'.
  $field_instances['node-ansicht-field_urheber'] = array(
    'bundle' => 'ansicht',
    'default_value' => array(
      0 => array(
        'value' => 'Unbekannt',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 14,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_urheber',
    'label' => 'Urheber',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 10,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('App Transfer checksum');
  t('Audio Datei');
  t('Autor');
  t('Beschreibe dein Bild hier');
  t('Beschreibung der Ansicht');
  t('Bild');
  t('Bildposition');
  t('Bildquelle');
  t('Bildquelle URL');
  t('Dieses Feld wird Automatisch ausgefüllt sobald die Position des Bildes Festgelegt ist.');
  t('Gebe hier die Bildquelle an');
  t('Gebe hier einen Kurztext/Teaser ein. (Maximal 60 Zeichen)');
  t('Genauigkeit');
  t('Genauigkeit XXXXXX');
  t('Hier hast du die Möglichkeit einige Suchbegriffe / Tags zu deinem Bild einzugeben. Die einzelnen Schlagworte werden mit  Komma "," getrennt.');
  t('Jahr');
  t('Jahr XXXXXX');
  t('Kategorie');
  t('Kurztext / Teaser');
  t('Lade hier das Bild für deine Ansicht hoch. Das Bild wird für unsere Ansicht automatisch auf eine Größe von maximal 800 Pixeln Breite oder maximal 600 Pixeln Höhe skaliert, so das für dich keine Arbeit mehr anfällt.

');
  t('Lizenz');
  t('Lizenz Vergleichsbild');
  t('Suchbegriffe / Tags');
  t('Unter welcher Lizenz willst du dieses Bild veröffentlichen?');
  t('Urheber');
  t('Vergleichsbild Datei');
  t('Wenn du einen Bild-Slider erstellen möchtest, lade hier das Vergleichsbild für diese Funktion hoch. Das Vergleichsbild muß vor dem Hochladen ggf. mit einem entsprechendem Bildbearbeitungsprogramm angepasst werden.
');
  t('Zu welcher Kategorie gehört dein Bild?');

  return $field_instances;
}
