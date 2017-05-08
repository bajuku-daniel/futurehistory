<?php

function futurehistory_preprocess_user_profile(&$variables) {
  $account = $variables['elements']['#account'];


  // Preprocess fields.
  field_attach_preprocess('user', $account, $variables['elements'], $variables);
  $variables['user_picture'] = isset($variables['elements']['user_picture']['#markup']) ? $variables['elements']['user_picture']['#markup'] : '';
  $variables['user_name'] = $account->name;
//  unset($variables['user_profile']['user_picture']);

  $variables['user_informations'] = "";
  $variables['user_activity'] = "";


  $view = views_get_view('meine_ansichten');
//  $view->override_path = $_GET['q'];

  $view->override_url = $_GET['q'];
  $ansichten_list = $view->preview('profil', array($account->uid));
  if (count($view->result) === 0) {
    $view = views_get_view('meine_ansichten');
    $view->override_url = $_GET['q'];
//    $view->query->pager->current_page = 0;
    $view->current_page = 0;
//    $view->query->pager->set_current_page(0);
    $ansichten_list = $view->preview('profil', array($account->uid));
  }

//  $ansichten_list = $view->preview('block_1', array($account->uid));
  $ansichten_total = $view->total_rows;
//  $ansichten_total = $count_query->execute()->fetchColumn();meine_ansichten-block_1
  //        $block = module_invoke('views', 'block_view','-exp-meine_ansichten-profil');
//        print render($block['content']);
  $variables['user_last_views'] = $ansichten_list;
  $variables['user_last_views_total'] = $ansichten_total;

//  pager_default_initialize($ansichten_total, 6, "1");
//  $variables['user_last_views_pager'] = theme('pager', array('quantity' => $ansichten_total,'element' => "0"));

  $view_touren = views_get_view('meine_touren');
  $touren_list = $view_touren->preview('profil', array($account->uid));
  $touren_total = count($view_touren->result);
  $variables['user_tours_views'] = $touren_list;
  $variables['user_tours_views_total'] = $touren_total;


  // meine touren
  // meine Bilder
  // Aktionen - activity stream
  // statistiken - Bilder count - touren count - follower TBD- Sammlung count
  // infos interessenten - About me

  // image | name |

  $variables['total_bilder'] = '<b>' . $ansichten_total . '</b>' . ' Bilder';
  $variables['total_touren'] = '<b>' . $touren_total . '</b>' . ' Touren';
  $variables['total_sammlung'] = '<b>' . $touren_total . '</b>' . ' Bilder in Sammlung';

  $variables['user_interessts'] = isset($account->field_interessen['und'][0]['safe_value']) ? $account->field_interessen['und'][0]['safe_value'] : '';
  $variables['user_about'] = isset($account->field__ber_mich['und'][0]['safe_value']) ? $account->field__ber_mich['und'][0]['safe_value'] : '';

  $R = 0;


  // Helpful $user_profile variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['user_profile'][$key] = $variables['elements'][$key];
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function futurehistory_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  $R = 0;
  // Add facets as hidden inputs to preserve selection.
  if (isset($_GET['page']) /* && ADD ANY OTHER VIEW-IDENTIFYING CODE DESIRED */) {
    // Get the parameters from the current page request.
    $params = drupal_get_query_parameters();
    // Add the facet values as hidden elements to the form.
    // The browser will turn them back into query parameters.
    $form['page'] = array(
      '#type' => 'hidden',
      '#value' => check_plain($_GET['page']),
    );

  }
}