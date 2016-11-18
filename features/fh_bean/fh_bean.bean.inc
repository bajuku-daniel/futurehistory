<?php
/**
 * @file
 * fh_bean.bean.inc
 */

/**
 * Implements hook_bean_admin_ui_types().
 */
function fh_bean_bean_admin_ui_types() {
  $export = array();

  $bean_type = new stdClass();
  $bean_type->disabled = FALSE; /* Edit this to true to make a default bean_type disabled initially */
  $bean_type->api_version = 5;
  $bean_type->name = 'eigene_bilder';
  $bean_type->label = 'Eigene Bilder';
  $bean_type->options = '';
  $bean_type->description = 'Accordeons / Tooltips';
  $export['eigene_bilder'] = $bean_type;

  return $export;
}
