<?php

function futurehistory_preprocess_user_profile(&$variables) {
  $account = $variables['elements']['#account'];

  // Helpful $user_profile variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['user_profile'][$key] = $variables['elements'][$key];
  }

  // Preprocess fields.
  field_attach_preprocess('user', $account, $variables['elements'], $variables);
  $variables['user_picture']=$variables['user_profile']['user_picture'];
  unset($variables['user_profile']['user_picture']);

  $variables['user_informations'] = "<b>user_informations</b>";
  $variables['user_activity'] ="<b>user_activity</b>";

  $view = views_get_view('meine_ansichten');
  $ansichten_list = $view->preview('default', array($account->uid));
//  if (count($view->$view) === 0) {
//    $ansichten_list = '';
//  }
  $variables['user_last_views'] = "<b>user_last_views</b>".$ansichten_list;


  $R=0;
}