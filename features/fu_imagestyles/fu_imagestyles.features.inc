<?php
/**
 * @file
 * fu_imagestyles.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function fu_imagestyles_image_default_styles() {
  $styles = array();

  // Exported image style: ansicht_bild_portal.
  $styles['ansicht_bild_portal'] = array(
    'label' => 'Ansicht Bild Portal',
    'effects' => array(
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1000,
          'height' => 800,
          'upscale' => 1,
        ),
        'weight' => -10,
      ),
    ),
  );

  // Exported image style: ansicht_bild_portal-copy.
  $styles['ansicht_bild_portal-copy'] = array(
    'label' => 'Manualcrop: Ansicht Bild Portal',
    'effects' => array(
      16 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 1000,
          'height' => 800,
          'upscale' => 1,
          'respectminimum' => 0,
          'onlyscaleifcrop' => 0,
          'style_name' => 'ansicht_bild_portal-copy',
        ),
        'weight' => -11,
      ),
      15 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1000,
          'height' => 800,
          'upscale' => 1,
        ),
        'weight' => -10,
      ),
    ),
  );

  // Exported image style: ansicht_bild_preview.
  $styles['ansicht_bild_preview'] = array(
    'label' => 'Ansicht Bild Vorschau',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 800,
          'height' => 600,
          'upscale' => 1,
        ),
        'weight' => -10,
      ),
    ),
  );

  // Exported image style: ansicht_bild_thumb.
  $styles['ansicht_bild_thumb'] = array(
    'label' => 'Ansicht Bild Thumb',
    'effects' => array(
      8 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 300,
          'height' => 300,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: fh-avatar-menu.
  $styles['fh-avatar-menu'] = array(
    'label' => 'fh-avatar-menu',
    'effects' => array(
      9 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 50,
          'height' => 50,
        ),
        'weight' => 1,
      ),
      10 => array(
        'name' => 'canvasactions_roundedcorners',
        'data' => array(
          'radius' => 25,
          'independent_corners_set' => array(
            'independent_corners' => 0,
            'radii' => array(
              'tl' => 0,
              'tr' => 0,
              'bl' => 0,
              'br' => 0,
            ),
          ),
        ),
        'weight' => 2,
      ),
      11 => array(
        'name' => 'coloractions_convert',
        'data' => array(
          'format' => 'image/png',
          'quality' => 75,
        ),
        'weight' => 3,
      ),
    ),
  );

  // Exported image style: fh_grid_view.
  $styles['fh_grid_view'] = array(
    'label' => 'FH Grid View',
    'effects' => array(
      12 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 320,
          'height' => 180,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: hintergrund_slideshow.
  $styles['hintergrund_slideshow'] = array(
    'label' => 'Hintergrund Slideshow (1366x768)',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1366,
          'height' => 768,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: mini_slider.
  $styles['mini_slider'] = array(
    'label' => 'Mini Slider',
    'effects' => array(
      14 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 400,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: profile_avatar.
  $styles['profile_avatar'] = array(
    'label' => 'Profile Avatar',
    'effects' => array(
      13 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 200,
          'height' => 200,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
