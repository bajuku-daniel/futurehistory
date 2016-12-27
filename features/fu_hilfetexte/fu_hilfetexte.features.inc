<?php
/**
 * @file
 * fu_hilfetexte.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fu_hilfetexte_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function fu_hilfetexte_node_info() {
  $items = array(
    'ansicht_hilfetexte' => array(
      'name' => t('Eigene Bilder Hilfetexte'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
