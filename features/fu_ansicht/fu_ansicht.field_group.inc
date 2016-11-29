<?php
/**
 * @file
 * fu_ansicht.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function fu_ansicht_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_add_picture|node|ansicht|form';
  $field_group->group_name = 'group_add_picture';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Bild hochladen',
    'weight' => '0',
    'children' => array(
      0 => 'field_bild',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Bild hochladen',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXX',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_add_picture|node|ansicht|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|ansicht|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Medien hinzufügen',
    'weight' => '4',
    'children' => array(
      0 => 'field_audio_datei',
      1 => 'field_text',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_media|node|ansicht|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_overlay|node|ansicht|form';
  $field_group->group_name = 'group_overlay';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Vergleichsbild / Bild-Slider',
    'weight' => '3',
    'children' => array(
      0 => 'field_bild_overlay',
      1 => 'field_overlay_jahr',
      2 => 'field_lizenz_overlay',
      3 => 'field_autor_overlay',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Vergleichsbild / Bild-Slider',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-overlay field-group-fieldset',
        'description' => 'Lade hier dein Vergleichsbild hoch, damit ein Bild-Slider für die Detailansicht erstellt wird. Ein Bild-Slider besteht aus zwei Bildern mit identischem Standort und identischer Perspektive aus unterschiedlichen Jahren oder Epochen, die übereinander gelegt werden. Über einen Regler können die Nutzer der App und des Webportals den Bildausschnitt frei wählen und interaktiv verändern.
',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_overlay|node|ansicht|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_picture_info|node|ansicht|form';
  $field_group->group_name = 'group_picture_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Bildinformationen',
    'weight' => '1',
    'children' => array(
      0 => 'field_teaser_kurzetext',
      1 => 'field_kategorie',
      2 => 'field_tags',
      3 => 'field_lizenz',
      4 => 'field_bildquelle',
      5 => 'field_jahr',
      6 => 'field_urheber',
      7 => 'field_genauigkeit',
      8 => 'field_bildquelle_url',
      9 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_picture_info|node|ansicht|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_position_der_ansicht|node|ansicht|form';
  $field_group->group_name = 'group_position_der_ansicht';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ansicht';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Bildposition',
    'weight' => '2',
    'children' => array(
      0 => 'field_stadt',
      1 => 'field_position_der_aufnahme',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Bildposition',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-position-der-ansicht field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_position_der_ansicht|node|ansicht|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Bild hochladen');
  t('Bildinformationen');
  t('Bildposition');
  t('Medien hinzufügen');
  t('Vergleichsbild / Bild-Slider');

  return $field_groups;
}
