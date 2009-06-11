<?php

/**
 *  @file
 *  NYSS Signup administrative functions
 */

/**
 * Define module settings FormAPI array.
 *
 * @return
 *   FormAPI form array passed through system_settings_form.
 */
function nyss_signup_settings() {  
  $form['bronto'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bronto Settings'),
  );  
  $form['bronto']['bronto_login'] = array(
    '#type' => 'textfield',
    '#title' => t('Bronto login'),
    '#default_value' => variable_get('bronto_login', ''),
    '#description' => t('Enter the login ID for your Bronto account.')
  );  
  $form['bronto']['bronto_sitename'] = array(
    '#type' => 'textfield',
    '#title' => t('Bronto site name'),
    '#default_value' => variable_get('bronto_sitename', ''),
    '#description' => t('Enter the sitename associated with this site in this Bronto account')
  );  
  $form['bronto']['bronto_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Bronto password'),
    '#default_value' => variable_get('bronto_password', ''),
    '#description' => t('Enter the password associated with this Bronto account.')
  );
  $form['bronto_general_list'] = array(
    '#type' => 'textfield',
    '#title' => t('General Mailing List Name'),
    '#default_value' => variable_get('bronto_general_list', ''),
    '#description' => t('This is the Bronto name of the general, site-wide mailing list.'),
  );
  $form['bronto_subscription_confirm_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Confirmation email body'),
    '#default_value' => variable_get('bronto_subscription_confirm_body', nyss_signup_confirm_body_default()),
    '#description' => t('The body of the confirmation email a user gets when they subscribe to a list.  Tokens: !site, !lists, !unsubscribe_link.'),
  );
  $form['bronto_subscription_unsubscribe_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Unsubscribe email body'),
    '#default_value' => variable_get('bronto_subscription_unsubscribe_body', nyss_signup_unsubscribe_body_default()),
    '#description' => t('The body of the confirmation email a user gets when they unsubscribe from a list.  Tokens: !site, !lists, !site_link.'),
  );
  return system_settings_form($form);
}

/**
 * Define FormAPI array for sending/previewing emails to accessible lists.
 *
 * @return
 *   FormAPI form array.
 */
function nyss_signup_send_mail($form_state) {
  // This is a two step form (create, preview)
  $step = isset($form_state['values']) ? (int)$form_state['storage']['step'] : 0;
  
  // Store next step
  $form_state['storage']['step'] = $step + 1;
  
  switch($step) {
    case 1:
      $lists = array();
      if (user_access('send to any mailing list')) {
        // Pull all mailing lists
        $general_list = variable_get('bronto_general_list', '');
        if ($general_list) {
          $lists[$general_list] = $general_list;
        }
        $results = db_query("SELECT ml.field_mailing_list_value AS list FROM {content_field_mailing_list} ml JOIN {node} n ON ml.vid = n.vid ORDER BY n.type ASC, ml.field_mailing_list_value ASC");
        while ($obj = db_fetch_object($results)) {
          $lists[$obj->list] = $obj->list;
        }
      }
      else {
        // Find out what senators and committees this user can edit and pull only those mailing lists
        $offices = nyss_editors_senate_offices();
        foreach ($offices as $nid => $title) {
          $list = db_result(db_query("SELECT ml.field_mailing_list_value AS list FROM {content_field_mailing_list} ml JOIN {node} n ON ml.vid = n.vid WHERE n.nid = %d", $nid));
          if ($list) {
            $lists[$list] = $list;
          }
          $senator = new stdClass();
          $senator->nid = $nid;
          $chairs = nyss_editors_senate_chairs($senator);
          foreach ($chairs as $cnid => $ctitle) {
            $list = db_result(db_query("SELECT ml.field_mailing_list_value AS list FROM {content_field_mailing_list} ml JOIN {node} n ON ml.vid = n.vid WHERE n.nid = %d", $cnid));
            if ($list) {
              $lists[$list] = $list;
            }
          }
        }
      }
      $form['list'] = array(
        '#type' => 'select',
        '#title' => t('Send to'),
        '#options' => array('' => t('[Select list]')) + $lists,
        '#default_value' => $form_state['storage']['list'] ? $form_state['storage']['list'] : '',
      );
      $form['from'] = array(
        '#type' => 'textfield',
        '#title' => t('From email'),
        '#required' => TRUE,
        '#default_value' => $form_state['storage']['from'] ? $form_state['storage']['from'] : '',
      );
      $form['subject'] = array(
        '#type' => 'textfield',
        '#title' => t('Subject'),
        '#required' => TRUE,
        '#default_value' => $form_state['storage']['subject'] ? $form_state['storage']['subject'] : '',
      );
      $form['body']['body_text'] = array(
        '#type' => 'textarea',
        '#title' => t('Body'),
        '#required' => TRUE,
        '#rows' => 15,
        '#default_value' => $form_state['storage']['body'] ? $form_state['storage']['body'] : '',
      );
      $form['body']['format'] = filter_form(2);
      break;
    case 2:
      $form['preview'] = array(
        '#type' => 'markup',
        '#value' => theme('nyss_signup_send_mail_preview', $form_state['values']),
      );
    
      // Save email info from step 1
      $form_state['storage']['list'] = $form_state['values']['list'];
      $form_state['storage']['subject'] = $form_state['values']['subject'];
      $form_state['storage']['from'] = $form_state['values']['from'];
      $form_state['storage']['body'] = $form_state['values']['body_text'];
      break;
  }

  $button_name = t('Send');
  if ($step < 2) {
    $button_name = t('Preview');
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $button_name,
  );
  
  if ($step == 2) {
    $form['back'] = array(
      '#type' => 'submit',
      '#value' => t('Back'),
      '#submit' => array('nyss_signup_send_mail_back'),
    );
  }

  return $form;
}

/**
 *  Implementation of hook_validate().
 */
function nyss_signup_send_mail_validate(&$form, &$form_state) {
  $error = FALSE;
  if ($form_state['storage']['step'] == 2) {
    if (!$form_state['values']['from'] || !$form_state['values']['subject'] || !$form_state['values']['body_text']) {
      $error = TRUE;
    }
    if (empty($form_state['values']['list'])) {
      form_set_error('list', t('You must select a mailing list.'));
      $error = TRUE;
    }
  }
  if ($error) {
    $form_state['storage']['step']--;
  }
}

/**
 *  Implementation of hook_submit().
 */
function nyss_signup_send_mail_back(&$form, &$form_state) {
  $form_state['storage']['step'] -= 2;
}

/**
 *  Implementation of hook_submit().
 */
function nyss_signup_send_mail_submit(&$form, &$form_state) {
  if ($form_state['storage']['step'] < 3) {
    return;
  }
  
  global $user;
  require_once(drupal_get_path('module', 'nyss_signup') . '/includes/bronto_api.inc');

  $bronto = new bronto_api(variable_get('bronto_login', ''), variable_get('bronto_sitename', ''), variable_get('bronto_password', ''));

  $response = $bronto->send_message(
    $user->name,
    $form_state['storage']['from'],
    $form_state['storage']['list'],
    $form_state['storage']['subject'],
    preg_replace('/\n/', '<br />', $form_state['storage']['body']),
    l(t('View'), 'nyss_signup/unsubscribe', array('absolute' => TRUE)) . ' your subscriptions.',
    'html'
  );
  if (!$response) {
    $form_state['storage']['step'] -= 2;
    drupal_set_message('Error: ' . $bronto->get_error_code() . "<br/>" . $bronto->get_error_message(), 'error');
    return;
  }
  else {
    drupal_set_message(t('Mail sent. [%subject]', array('%subject' => $form_state['storage']['subject'])));
  }
  
  unset($form_state['storage']);
}

/*
 * One-time function to create initial Bronto lists
 */
function nyss_signup_create_initial_lists() {
  exit();

  require_once(drupal_get_path('module', 'nyss_signup') . '/includes/bronto_api.inc');
  $bronto = new bronto_api(variable_get('bronto_login', ''), variable_get('bronto_sitename', ''), variable_get('bronto_password', ''));

  $results = db_query("SELECT nid FROM {node} WHERE type IN ('senator', 'committee') AND status = 1");
  while ($obj = db_fetch_object($results)) {
    $n = node_load($obj->nid);
    if ($n->type == 'senator') {
      $district = node_load($n->field_senators_district[0]['nid']);
      $list = 'District '. $district->field_district_number[0]['value'] .' Updates';
    }
    elseif ($n->type == 'committee') {
      $list = $n->title .' Committee Updates';
    }
    $n->field_mailing_list[0]['value'] = $list;
    node_save($n);

    $bronto->create_list($list);
    print 'Created '. $list .'.<br/>';
  }
}