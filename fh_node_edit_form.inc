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

    if(isset($form['nid']['#value']) && $form['nid']['#value'] !== null) {
      // add ABBRECHEN
      $form['actions']['cancels'] = array(
        '#markup' =>
          l(t('Abbrechen'), 'user/meine_ansichten', array(
            'attributes' => array('class' => array('btn btn-warning form-submit')),
            'html' => TRUE
          )),
        '#weight' => 0,
      );
    }
  }
  if ($node_type === 'ansicht_hilfetexte') {
    $form['additional_settings']['#access'] = FALSE;
    $form['actions']['submit']['#submit'][] = 'futurehistory_node_edit_form_handler_after_submit';
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
    if(isset($variables['element']['#attributes']['data-toggle'])){
      unset($variables['element']['#attributes']['data-toggle']);
      $variables['element']['#children']=str_replace('data-toggle','data-toggle_',$variables['element']['#children']);
    }

  $check = isset($variables['element']['#bundle']) && ($variables['element']['#bundle'] === 'ansicht');
  $field_name = isset($variables['element']['#field_name'])?$variables['element']['#field_name']:false;
  if ($check && $field_name || (in_array($variables['element']['#id'],array("edit-field-position-der-aufnahme-und-0-coordinate-known","edit-field-position-der-aufnahme-und-0-address-field")))) {
    $result = fh_node_edit_lable_helper($field_name);
  }
  return $result;
}

function fh_node_edit_lable_helper($field_name,$result=""){
// TODO: add informations for "Ich kenne die Koordinaten" if nedded

  $info_node = fh_get_hilfetexte_node();
//    $variables['form']['ansicht_hilfetexte'] = $info_node;

  $field_name = fh_node_edit_form_field_mapping($field_name);
  if (isset($info_node->{$field_name}['und'][0]['safe_value'])) {
    $field_value = $info_node->{$field_name}['und'][0]['safe_value'];

    $img_src = drupal_get_path('module', 'futurehistory') . '/images/tooltip.png';
    $markup = <<<HTMLTEMPALTE
<span class="custom-tooltip" data-tooltip-content="#tooltip_content-$field_name">
	<img src="/$img_src"></span>
<div class="tooltip_templates">
    <span id="tooltip_content-$field_name">
	  $field_value
</div>
HTMLTEMPALTE;
    $result = $markup;
  }
  return $result;
}


/**
 * get Hilfetexte Node cached
 *
 * @return array|bool|mixed
 */
function fh_get_hilfetexte_node(){
  $hilfetexte_nid = &drupal_static(__FUNCTION__);
  $info_node = &drupal_static(__FUNCTION__);
  if (!isset($hilfetexte_nid) || !isset($info_node)) {
    global $language;
    $hilfetexte_nid = variable_get('fu_hilfetexte_' . $language->language, '');
    if (!empty($hilfetexte_nid)) {
      $info_node = node_load($hilfetexte_nid);
    }
  }

 return $info_node;
}

/**
 * Mapping for ansicht => ansicht_hilfetexte fields
 *
 * @param $key
 * @return bool|mixed
 */
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
    'group_lizenz_blid'=>'field_accordion_lizenz_hi',
    'field_lizenz'=>'field_lizenz_hi',
    'field_bildquelle'=>'field_bildquelle_hi',
    'field_bildquelle_url'=>'field_bildquelle_url_hi',
    'field_urheber'=>'field_urheber_hi',
    'group_position_der_ansicht'=>'field_group_position_der_ansicht',
    'field_position_der_aufnahme'=>'field_position_der_aufnahme_hi',
    'js_attach_field_stadt_hi'=>'field_stadt_hi',
    'js_attach_blickwinkel_hi'=>'field_info_blickwinkel_hi',
    'js_attach_blickwinkelbereich_hi'=>'field_info_blickwinkelbereich_hi',
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
 * Could be in template.php as HOOK_form_element_label
 * future_history_form_element_label added by theme_registry_alter namespace from theme
 * @param $variables
 * @return string
 *
 */
function future_history_form_element_label(&$variables) {
  $custom_informations = futurehistory_custom_lable_informations($variables);
  $bootstrap_label = bootstrap_form_element_label($variables);
  $bootstrap_label_custom = str_replace( "</label>" , $custom_informations."</label>" , $bootstrap_label);
  return $bootstrap_label_custom;
}

/**
 * Helper
 * parse rendered markup replace legende DOM node with accoriion markup
 *
 */
function future_history_replace_tab_legend($tab_content, $tab_id, $tab_title) {
  $elements = $tab_id;
  $c = new simple_html_dom();
  $c->load($tab_content);
//  $tab_content = $tab_content;
// filter for legend elements and replace content structure
  if($c->find('legend', 0)){
    $getLegent = fh_get_legend($tab_id, $tab_title);
    $c->find('legend', 0)->innertext = $getLegent;
// return the modified HTML
    $tab_content = $c;
  }


  return $tab_content;
}

/**
 * Helper
 * build accordion markup
 * map field ID to hilfetexte content fields
 *
 * @param $tab_id
 * @param $tab_title
 * @return string
 */
function fh_get_legend($tab_id,$tab_title){
  $info_node = fh_get_hilfetexte_node();
  $field_name = fh_node_edit_form_field_mapping($tab_id);
  $legend_info="";
  $legent_markup="";
  $legent_icon="";
  $legent_icon_style="icon-hidden";
  if(isset($info_node->{$field_name}['und'][0]['safe_value'])){
    $legend_info = $info_node->{$field_name}['und'][0]['safe_value'];
  }

  $img_src = drupal_get_path('module', 'futurehistory') . '/images/arrow-blank.png';
  $field_name = $tab_id;
  if(!empty($legend_info)){
    $legent_markup = <<<LEGENDMARKUP
        <div id="collapse$field_name" class="accordion-panel-collapse collapse">
            <div class="accordion-panel-body accordion1_">
                <p>$legend_info</p>
            </div>
        </div>
LEGENDMARKUP;

    $legent_icon = <<<LEGENDICON
        <span class="image-wrapper"><img src="/$img_src"></span>
LEGENDICON;
    $legent_icon_style='';


  }
  $legend = <<<HTMLTEMPALTE
<div class="accordion-toggle accordion1_">
    <div class="panel-group" id="accordion-$field_name">
        <div class="accordion-panel panel-default">
            <div class="accordion-panel-heading"> 
                <span class="accordion-panel-title $legent_icon_style" >
                    <a title="" data-toggle="collapse" data-parent="#accordion-$field_name"
                       href="#collapse$field_name" class="collapsed">
                    $tab_title $legent_icon
                    </a>
                </span>
            </div>
        </div>
        $legent_markup
    </div>
</div>
HTMLTEMPALTE;


return $legend;

}