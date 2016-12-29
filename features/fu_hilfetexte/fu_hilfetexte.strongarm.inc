<?php
/**
 * @file
 * fu_hilfetexte.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function fu_hilfetexte_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_ansicht_hilfetexte';
  $strongarm->value = 0;
  $export['comment_anonymous_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_ansicht_hilfetexte';
  $strongarm->value = '0';
  $export['comment_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_ansicht_hilfetexte';
  $strongarm->value = 0;
  $export['comment_default_mode_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_ansicht_hilfetexte';
  $strongarm->value = '50';
  $export['comment_default_per_page_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_ansicht_hilfetexte';
  $strongarm->value = 0;
  $export['comment_form_location_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_ansicht_hilfetexte';
  $strongarm->value = '0';
  $export['comment_preview_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_ansicht_hilfetexte';
  $strongarm->value = 0;
  $export['comment_subject_field_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__ansicht_hilfetexte';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'language' => array(
          'weight' => '1',
        ),
        'title' => array(
          'weight' => '0',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_extended_ansicht_hilfetexte';
  $strongarm->value = '1';
  $export['i18n_node_extended_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_options_ansicht_hilfetexte';
  $strongarm->value = array(
    0 => 'current',
    1 => 'required',
  );
  $export['i18n_node_options_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_ansicht_hilfetexte';
  $strongarm->value = '2';
  $export['language_content_type_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_ansicht_hilfetexte';
  $strongarm->value = array();
  $export['menu_options_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_ansicht_hilfetexte';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_ansicht_hilfetexte';
  $strongarm->value = array(
    1 => 'status',
  );
  $export['node_options_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_ansicht_hilfetexte';
  $strongarm->value = '0';
  $export['node_preview_ansicht_hilfetexte'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_ansicht_hilfetexte';
  $strongarm->value = 0;
  $export['node_submitted_ansicht_hilfetexte'] = $strongarm;

  return $export;
}
