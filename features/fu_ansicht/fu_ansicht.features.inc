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