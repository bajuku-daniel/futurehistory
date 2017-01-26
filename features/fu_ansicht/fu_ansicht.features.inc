<?php
/**
 * @file
 * fu_ansicht.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fu_ansicht_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function fu_ansicht_image_default_styles() {
  $styles = array();

  // Exported image style: ansicht_bild_portal-copy.
  $styles['ansicht_bild_portal-copy'] = array(
    'label' => 'mc Ansicht Bild Portal',
    'effects' => array(
      16 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 1000,
          'height' => 800,
          'upscale' => 1,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'ansicht_bild_portal-copy',
        ),
        'weight' => -11,
      ),
      15 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1000,
          'height' => 800,
          'upscale' => 1,
        ),
        'weight' => -10,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function fu_ansicht_node_info() {
  $items = array(
    'ansicht' => array(
      'name' => t('Eigene Bilder einstellen'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
