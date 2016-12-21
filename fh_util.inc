<?php

/**
 * Whether or not the administration mode is enabled.
 *
 * @return bool <code>TRUE</code> if the administration mode is enabled.
 */
function fh_util_admin_mode_enabled() {
  return drupal_is_cli() || user_access('administer site configuration');
}

function futurehistory_admin_mode_enabled() {
  return drupal_is_cli() || user_access('administer site configuration');
}

/**
 * Whether or not the administration mode is enabled.
 *
 * @return bool <code>TRUE</code> if the administration mode is enabled.
 */
//function fh_util_admin_mode_enabled() {
//  return drupal_is_cli() || user_has_role(3);
//}


function cb_util_render_imagefield(&$node, $fieldname, $imagestyle = NULL, $imageclasses = NULL) {
  if (!isset($node->nid) && !isset($node->flid)) {
    return '';
  }
  $item = cb_util_field_item($node, $fieldname);
  $img = cb_util_render_image($item, $imagestyle, $imageclasses);
  return $img;
}

function cb_util_render_image($image, $imagestyle = NULL, $imageclasses = NULL, $default = NULL) {
  if (!empty($image)) {
    if (empty($image['alt'])) {
      $variables['alt'] = $image['filename'];
    }
    else {
      $variables['alt'] = $image['alt'];
    }
    $variables = array(
      'path' => $image['uri'],
      'title' => $variables['alt'],
      'alt' => $variables['alt'],
      'url' => $image['uri'],
      'style_name' => $imagestyle,
      'attributes' => array(),
    );
    if ($imageclasses) {
//    $variables['#attributes'] = array('class' => $imageclasses);
      $variables['attributes']['class'] = $imageclasses;
    }
    $img = $imagestyle ? theme('image_style', $variables) : theme('image', $variables);
    return $img;
  }
  else {
    return $default;
  }
}


/**
 * @param $node
 * @param $fieldname
 * @param null $attribute/propperty e.g. lat, lng
 * @param string $default if empty return default
 * @param int $index integer or 'all'
 * @return string
 */
function cb_util_field_item($entity, $fieldname, $attribute = NULL, $default = '', $index = 0) {
  // TODO: FIX
  if (!isset($entity->nid) && !isset($entity->flid)) {
    return $default;
  }
  if (!isset($entity->{$fieldname}['und'])) {
    return $default;
  }
  $item = $entity->{$fieldname}['und'];
  if ($index === 'all') {
    $item = $item;
  }
  else {
    if (isset($item[$index])) {
      $item = $item[$index];
    }
    else {
      return $default;
    }
  }
  $item = $attribute ? $item[$attribute] : $item;
  if ($attribute == 'value') {
    $item = check_plain($item);
  }
  return isset($item) ? $item : $default;
}
