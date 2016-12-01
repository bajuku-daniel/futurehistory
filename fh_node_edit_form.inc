<?php
/**
 * HOOK - form_node_form_alter
 */
function futurehistory_form_node_form_alter(&$form, &$form_state, $form_id) {
  if (futurehistory_admin_mode_enabled()) {
//    return;
  }

  $node_type = $form['type']['#value'];

  if ($node_type === 'ansicht') {
    // remove delete LÖSCHEN
    $form['actions']['delete']['#access'] = FALSE;
    $form['actions']['preview_changes']['#access'] = FALSE;
    // add ABBRECHEN
    $form['actions']['cancels'] = array(
      '#markup' =>
        l(t('Abbrechen'), 'user/meine_ansichten', array('attributes' => array('class' => array('btn btn-warning form-submit')), 'html' => TRUE)),
      '#weight' => 0,
    );
  }
  if ($node_type === 'ansicht_hilfetexte') {
    $form['additional_settings']['#access'] = FALSE;
  }
}

/**
 * Submit handler that sets config fu_hilfetexte variable.
 *
 * This content should be created only once per language.
 * This must be controled by permissions or any other mechanism.
 *
 */
function futurehistory_node_edit_form_handler_after_submit($form, &$form_state) {
  $node_nid = $form['#node']->nid;
  $node_lang = $form['#node']->language;
  variable_set('fu_hilfetexte_' . $node_lang, $node_nid);
  $form_state['redirect'] = 'admin/content';
}





/**
 * Helper - add DOM to lables
 * WIP - markup not ready yet.
 */
function futurehistory_custom_lable_informations(&$variables) {
  $result = '';

  $check = isset($variables['element']['#bundle']) && ($variables['element']['#bundle'] === 'ansicht');
  $field_name = isset($variables['element']['#field_name'])?$variables['element']['#field_name']:false;
  if ($check && $field_name) {
    $hilfetexte_nid = &drupal_static(__FUNCTION__);
    $info_node = &drupal_static(__FUNCTION__);
    if (!isset($hilfetexte_nid) || !isset($info_node)) {
      global $language;
      $hilfetexte_nid = variable_get('fu_hilfetexte_' . $language->language, '');
      if (!empty($hilfetexte_nid)) {
        $info_node = node_load($hilfetexte_nid);
        $variables['form']['ansicht_hilfetexte'] = $info_node;
      }
    }

    $field_name = fh_node_edit_form_field_mapping($field_name);
$R=0;
    if(isset($info_node->{$field_name}['und'][0]['safe_value'])){
      $field_value = $info_node->{$field_name}['und'][0]['safe_value'];
      $demo_html ="<div class='info $field_name'>".$field_value."</div>";
      $result = $demo_html;
    }

    $R = 0;
  }
  return $result;
}

function fh_node_edit_form_field_mapping($key){
  $mapping=array(
    'group_add_picture'=>'field_group_add_picture_hi',
    'field_bild'=>'field_bild_hi',
    'group_picture_info'=>'field_group_picture_info_hi',
    'title'=>'field_title_hi',
    'field_jahr'=>'field_jahr_hi',
    'field_genauigkeit'=>'field_genauigkeit_hi',
    'field_teaser_kurzetext'=>'field_teaser_kurzetext_hi',
    'field_kategorie'=>'field_kategorie_hi',
    'field_tags'=>'field_tags_hi',
    'field_lizenz'=>'field_lizenz_hi',
    'field_bildquelle'=>'field_bildquelle_hi',
    'field_bildquelle_url'=>'field_bildquelle_url_hi',
    'field_urheber'=>'field_urheber_hi',
    'group_position_der_ansicht'=>'field_group_position_der_ansicht',
    'field_position_der_aufnahme'=>'field_position_der_aufnahme_hi',
    'field_stadt'=>'field_stadt_hi',
    'group_overlay'=>'field_group_overlay_hi',
    'field_bild_overlay'=>'field_bild_overlay_hi',
    'field_lizenz_overlay'=>'field_overlay_lizenz_hi',
    'field_overlay_jahr'=>'field_overlay_jahr_hi',
    'field_autor_overlay'=>'field_overlay_autor_hi',
    'group_media'=>'field_group_media_hi',
    'field_text'=>'field_text_hi',
    'field_audio_datei'=>'field_audio_datei_hi',
  );

  if(isset($mapping[$key])){
    return $mapping[$key];
  }
  return false;
}


/**
 * Implements hook_theme_registry_alter().
 */
function futurehistory_theme_registry_alter(&$theme_registry) {
//  $theme_registry['form_element_label']['function'] = 'future_history_form_element_label';
//  $theme_registry['form_element_label']['theme path'] = drupal_get_path('module', 'futurehistory');
}


/**
 * Could be in template.php as HOOK_form_element_label
 * future_history_form_element_label added by theme_registry_alter namespace from theme
 * @param $variables
 * @return string
 *
 */
function future_history_form_element_label(&$variables) {
  $custom_informations = futurehistory_custom_lable_informations($variables);
  return bootstrap_form_element_label($variables) . $custom_informations;
}
