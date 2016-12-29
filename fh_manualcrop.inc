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
      $url = image_style_url( 'ansicht_bild_portal', $fu_image->uri);
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
  $output .= '<input type="button" value="' . t('Save') . '" class="manualcrop-button manualcrop-close form-submit" onmousedown="ManualCrop.closeCroptool();" />';
  $output .= '<input type="button" value="' . t('Revert selection') . '" class="manualcrop-button manualcrop-reset form-submit" onmousedown="ManualCrop.resetSelection();" />';
  $output .= '<input type="button" value="' . t('Remove selection') . '" class="manualcrop-button manualcrop-clear form-submit" onmousedown="ManualCrop.clearSelection();" />';
  $output .= '<input type="button" value="' . t('Maximize selection') . '" class="manualcrop-button manualcrop-maximize form-submit" onmousedown="ManualCrop.maximizeSelection();" />';
  $output .= '<input type="button" value="' . t('Cancel') . '" class="manualcrop-button manualcrop-cancel form-submit" onmousedown="ManualCrop.closeCroptool(true);" />';
  $output .= '</div>';

  $output .= '</div>';

  $output .= '</div>';

  return $output;
}





?>