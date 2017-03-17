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
    if(isset($image->fid)){
      $image = get_object_vars($image);
    }
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



/*
 * DATE FORMATS
 * */
define("_DATE__12_10_2012", "d.m.Y");
define("_DATE__2012-10-12", "Y-m-d");
define("_DATE__12_", "d.");
define("_DATE__12", "d");
define("_DATE__12_10_", "d.m.");
define("_DATE__2012", "Y");
define("_DATE__MONTH", "F");
define("_DATE__15_JULY_2010", "d. F Y");
define("_DATE__j_n_Y", "j.n.Y");
define("_TIME__h_i_s", "H:i:s");
define("_DATE__MICROFORMAT", "c");


function ff_m_util_format_date($datevalue, $format) {
  if (!empty($datevalue)) {
    if (($timestamp = strtotime($datevalue)) !== false) {
      // Obtained a valid $timestamp; $format is valid
      $timestamp = strtotime($datevalue);
    } else {
      // $format is invalid
      $timestamp =  $datevalue;
    }

    $formateddate = format_date($timestamp, 'custom', $format);
    return $formateddate;
  }
  return '';
}

function ff_m_util_localise_date_format($format) {
  global $language;
  $local_formats = array(
    'd.m.Y' => array(
      'en-US' => 'd/m/Y',
    ),
    "d." => array(
      'en-US' => 'd',
    ),
    "d.m." => array(
      'en-US' => 'd/m',
    ),
    "Y" => array(
      'en-US' => 'Y',
    ),
    "F" => array(
      'en-US' => 'F',
    ),
    "j.n.Y" => array(
      'en-US' => 'j/n/Y',
    )
  );
  $local_format = isset($local_formats[$format][$language->language]) ? $local_formats[$format][$language->language] : $format;

  return $local_format;
}
