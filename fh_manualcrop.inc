<?php


/**
 * Returns HTML for the inline crop area of an image.
 *
 * @param $variables
 *   An associative array containing:
 *   - "attributes": An array of attributes.
 *   - "image": An array of variables for the image theming function.
 *
 * @return
 *   HTML for the inline crop tool.
 *
 * @ingroup themeable
 */
function fh_theme_manualcrop_croptool_inline($variables) {
  $output = '<div ' . drupal_attributes($variables['attributes']) . '>';

  $output .= '<div class="manualcrop-image-holder">';
  $output .= theme('image', $variables['image']);
  $output .= '</div>';

  $output .= '<div class="clearfix">';

  if ($variables['crop_info']) {
    $output .= '<div class="manualcrop-selection-info hidden">';
    $output .= '<div class="manualcrop-selection-label manualcrop-selection-xy">';
    $output .= '<div class="manualcrop-selection-label-content">';
    $output .= '<span class="manualcrop-selection-x">-</span> x <span class="manualcrop-selection-y">-</span>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '<div class="manualcrop-selection-label manualcrop-selection-width">';
    $output .= '<div class="manualcrop-selection-label-content">-</div>';
    $output .= '</div>';
    $output .= '<div class="manualcrop-selection-label manualcrop-selection-height">';
    $output .= '<div class="manualcrop-selection-label-content">-</div>';
    $output .= '</div>';
    $output .= '</div>';
  }

  if ($variables['instant_preview']) {
    $style = '';
    $url = '';
    if(isset($_POST['field_bild']['und'][0]['fid'])){
      $fu_image = file_load($_POST['field_bild']['und'][0]['fid']);
      $url = image_style_url('ansicht_bild_portal', $fu_image->uri);
      $style = 'style="background-image:url('.$url.');background-size: cover;"';
    }else{
      $nid = explode('/',$_GET['q'])[1];
      if(is_numeric($nid)){
        $nid = (int) $nid;
        $node = node_load($nid);
        if(isset($node->field_bild['und'][0])){
          $fu_image = $node->field_bild['und'][0];
          $url = image_style_url( 'ansicht_bild_portal', $fu_image['uri']);
          $style = 'style="background-image:url('.$url.');background-size: cover;"';
        }
      }
    }

    $output .= "<div class='manualcrop-instantpreview' data-url='".$url."' ".$style."></div>";
  }

  if ($variables['crop_info']) {
    $output .= '<div class="manualcrop-style-info">';
    $output .= t('Image style') . ': <span class="manualcrop-style-name">&nbsp;</span><br />';
    $output .= '</div>';
  }
  $output .= '<div class="manualcrop-buttons">';
  $output .= '<input type="button" value="' . t('Abbrechen') . '" class="manualcrop-button manualcrop-cancel form-submit btn btn-danger" onmousedown="ManualCrop.closeCroptool(true);" />';
  $output .= '<input type="button" value="' . t('Speichern') . '" class="manualcrop-button manualcrop-close form-submit btn btn-success" onmousedown="ManualCrop.closeCroptool();" />';
  $output .= '</div>';
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}


/**
 * Return/Create Imagestyle for manualcrop by proportions of native primary image
 *
 * style for primary image: ansicht_bild_portal
 *
 * @param $width
 * @param $height
 * @return mixed
 */
function fh_mc_image_style_by_size($width, $height){
  $dimensions = array(
    'width' => $width,
    'height' => $height,
  );
  image_style_transform_dimensions("ansicht_bild_portal", $dimensions);
  return fh_mc_create_image_style((int) $dimensions['width'],(int) $dimensions['height']);
}

/**
 * Return/Create Imagestyle for manualcrop by proportions of transformed primary image
 *
 * style for primary image: ansicht_bild_portal
 *
 * @param $width
 * @param $height
 * @return mixed
 */
function fh_mc_create_image_style($width, $height){
$style_name = "mc-".$width."x".$height;
 $style_load =  image_style_load($style_name);
if(isset($style_load['name'])){
  return $style_load['name'];
}
  $style = image_style_save(array(
      'name' => $style_name,
      'label' => 'Ansicht Bild Portal ('.$width."x".$height.')')
  );
  $effect = array(
    'module' => 'manualcrop',
    'name' => 'manualcrop_crop_and_scale',
    'label' => 'Manual Crop: Crop and scale',
    'weight' => '-10',
    'help' => 'Crop and scale a user-selected area, respecting the ratio of the destination width and height.',
    'summary theme' => 'manualcrop_crop_and_scale_summary',
    'form callback' => 'manualcrop_crop_and_scale_form',
    'effect callback' => 'manualcrop_crop_and_scale_effect',

    'data' => array(
      'width' => $width,
      'height' => $height,
      'upscale' => TRUE,
      'respectminimum' => TRUE,
      'onlyscaleifcrop' => 0,
      'style_name' => $style_name,
    ),

    'isid' => $style['isid'],
  );
  $effect_result = image_effect_save($effect);
return  $style['name'];
}

/**
 * Add informations neded for manual crop initialisation
 *
 * TODO: check hidden fields
 *
 * @param $element
 * @param $form_state
 * @param $context
 *
 */
function futurehistory_field_widget_form_alter(&$element, &$form_state, $context) {
  // ['field_bild_overlay']
  // ['field_bild']
  $R=0;
  if ($context['field']['field_name'] == 'field_bild') {
    // Loop through the element children (there will always be at least one).
    foreach (element_children($element) as $key => $child) {
      // Add the new process function to the element
      //dpm($element);
      $element[$key]['#process'][] = 'futurehistory_image_field_widget_process';
    }
  }
}


function futurehistory_image_field_widget_process($element, &$form_state, $form) {
  // Change the title field label and description
  //dpm($element);
//  $element['title']['#title'] = 'NEW TITLE';
  $element['title']['#description'] = 'SOME NEW DESCRIPTION HERE.';

  // Return the altered element
  return $element;
}


?>