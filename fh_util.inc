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

