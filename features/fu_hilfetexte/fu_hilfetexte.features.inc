<?php
/**
 * @file
 * fu_hilfetexte.features.inc
 */

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
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
