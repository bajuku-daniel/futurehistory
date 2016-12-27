<?php
/**
 * @file
 * Custom node access rules.
 * Implements HOOK_node_access
 *
 *
 */

function fh_node_access($node, $op, $account) {
  $R=0;
  if (!fh_util_admin_mode_enabled()) {
    $node_type = is_string($node) ? $node : $node->type;


    $condition = user_is_anonymous()
      && $op === 'view'
      && isset($node->field_visibility['und'][0]['tid'])
      && ($node->status === "1");

    if ($condition) {
      if (isset($_REQUEST['destination'])) {
        unset($_REQUEST['destination']);
      }
      $options = array('query' => drupal_get_destination());
      drupal_goto('user/login', $options);


      # disable viewing of node types with no own view
      $node_has_own_view = !in_array($node_type, array_keys(array('ansicht_hilfetexte')));
      # the additional test for '#^node/\d+$#' is required because we still want to allow translations of the node (see _translation_tab_access($node))
      $is_node_view_path = preg_match('#^node/\d+$#', current_path());
      $view_of_node_type_without_own_view = $op === 'view' && !$node_has_own_view && $is_node_view_path;
      if ($view_of_node_type_without_own_view) {
        return NODE_ACCESS_DENY;
      }

    }


    return NODE_ACCESS_IGNORE;
  }
}


