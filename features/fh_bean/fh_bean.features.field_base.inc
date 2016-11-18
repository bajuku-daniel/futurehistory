<?php
/**
 * @file
 * fh_bean.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function fh_bean_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_fueb_test'.
  $field_bases['field_fueb_test'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_fueb_test',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  return $field_bases;
}
