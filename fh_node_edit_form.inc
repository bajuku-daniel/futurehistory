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
    if($field_name === "field_group_media_hi"){
      $table_markup = <<<LEGENDMARKUP
        <table width="100%">
        <tr>
        <td><p>So legst du einen internen Link an.</p></td>
        <td><p>So legst du einen externen Link an.</p></td>
        </tr><tr>
        <td><img src="data:image/jpeg;base64,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"></td>
        <td><img src="data:image/jpeg;base64,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"></td>
        </tr></table>
LEGENDMARKUP;

      $legend_info .= $table_markup;
    }
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