<?php

function futurehistory_preprocess_user_profile(&$variables) {
  $account = $variables['elements']['#account'];


  // Preprocess fields.
  field_attach_preprocess('user', $account, $variables['elements'], $variables);
  $variables['user_picture']=$variables['user_profile']['user_picture'];
  $variables['user_name']=$account->name;
  unset($variables['user_profile']['user_picture']);

  $variables['user_informations'] = "<b>user_informations</b>";
  $variables['user_activity'] ="<b>user_activity</b>";


  $view = views_get_view('meine_ansichten');
  $ansichten_list = $view->preview('profil', array($account->uid));
  $ansichten_total = $view->total_rows;
  $variables['user_last_views'] = $ansichten_list;


  $view_touren = views_get_view('meine_touren');
  $touren_list = $view_touren->preview('profil', array($account->uid));
  $touren_total = $view_touren->total_rows;
  $variables['user_tours_views'] = $touren_list;


  // meine touren
  // meine Bilder
  // Aktionen - activity stream
  // statistiken - Bilder count - touren count - follower TBD- Sammlung count
  // infos interessenten - About me

  // image | name |

  $variables['total_bilder'] = $ansichten_total.' Bilder';
  $variables['total_touren'] = $touren_total.' Touren';
  $variables['total_sammlung'] = $touren_total.' Bilder in Sammlung';

  $variables['user_interessts'] = isset($account->field_interessen['und'][0]['safe_value'])?$account->field_interessen['und'][0]['safe_value']:'';
  $variables['user_about'] = isset($account->field__ber_mich['und'][0]['safe_value'])?$account->field__ber_mich['und'][0]['safe_value']:'';

  $R=0;


  // Helpful $user_profile variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['user_profile'][$key] = $variables['elements'][$key];
  }
}