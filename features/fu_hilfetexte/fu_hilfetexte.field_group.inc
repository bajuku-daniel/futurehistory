<?php
/**
 * @file
 * fu_hilfetexte.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function fu_hilfetexte_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_add_picture_hi|node|ansicht_hilfetexte|form';
  $field_group->group_name = 'group_add_picture_hi';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht_hilfetexte';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Bild hochladen',
    'weight' => '2',
    'children' => array(
      0 => 'field_bild_hi',
      1 => 'field_group_add_picture_hi',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Bild hochladen',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-add-picture-hi field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_add_picture_hi|node|ansicht_hilfetexte|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_lizenz_blid_hi|node|ansicht_hilfetexte|form';
  $field_group->group_name = 'group_lizenz_blid_hi';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht_hilfetexte';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Lizenz ',
    'weight' => '4',
    'children' => array(
      0 => 'field_bildquelle_hi',
      1 => 'field_bildquelle_url_hi',
      2 => 'field_lizenz_hi',
      3 => 'field_urheber_hi',
      4 => 'field_accordion_lizenz_hi',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-lizenz-blid-hi field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_lizenz_blid_hi|node|ansicht_hilfetexte|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media_hi|node|ansicht_hilfetexte|form';
  $field_group->group_name = 'group_media_hi';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht_hilfetexte';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Medien hinzufügen',
    'weight' => '7',
    'children' => array(
      0 => 'field_audio_datei_hi',
      1 => 'field_group_media_hi',
      2 => 'field_text_hi',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Medien hinzufügen',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-media-hi field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_media_hi|node|ansicht_hilfetexte|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_overlay_hi|node|ansicht_hilfetexte|form';
  $field_group->group_name = 'group_overlay_hi';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht_hilfetexte';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Vergleichsbild / Bild-Slider',
    'weight' => '6',
    'children' => array(
      0 => 'field_bild_overlay_hi',
      1 => 'field_group_overlay_hi',
      2 => 'field_overlay_autor_hi',
      3 => 'field_overlay_jahr_hi',
      4 => 'field_overlay_lizenz_hi',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Vergleichsbild / Bild-Slider',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-overlay-hi field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_overlay_hi|node|ansicht_hilfetexte|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_picture_info_hi|node|ansicht_hilfetexte|form';
  $field_group->group_name = 'group_picture_info_hi';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht_hilfetexte';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Bildinformationen',
    'weight' => '3',
    'children' => array(
      0 => 'field_genauigkeit_hi',
      1 => 'field_group_picture_info_hi',
      2 => 'field_jahr_hi',
      3 => 'field_kategorie_hi',
      4 => 'field_tags_hi',
      5 => 'field_teaser_kurzetext_hi',
      6 => 'field_title_hi',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Bildinformationen',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-picture-info-hi field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_picture_info_hi|node|ansicht_hilfetexte|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_position_der_ansicht_hi|node|ansicht_hilfetexte|form';
  $field_group->group_name = 'group_position_der_ansicht_hi';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht_hilfetexte';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Bildposition',
    'weight' => '5',
    'children' => array(
      0 => 'field_group_position_der_ansicht',
      1 => 'field_position_der_aufnahme_hi',
      2 => 'field_stadt_hi',
      3 => 'field_info_blickwinkelbereich_hi',
      4 => 'field_info_blickwinkel_hi',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Bildposition',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-position-der-ansicht-hi field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_position_der_ansicht_hi|node|ansicht_hilfetexte|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Bild hochladen');
  t('Bildinformationen');
  t('Bildposition');
  t('Lizenz ');
  t('Medien hinzufügen');
  t('Vergleichsbild / Bild-Slider');

  return $field_groups;
}
