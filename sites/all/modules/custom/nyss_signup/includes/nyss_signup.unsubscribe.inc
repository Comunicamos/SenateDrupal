<?php

/**
 *  @file
 *  NYSS Signup unsubscribe functions
 */

/**
 * Unsubscribe page.
 */
function nyss_signup_unsubscribe_page($email = NULL) {
  if (!$email) {
    $output .= drupal_get_form('nyss_signup_unsubscribe_email_form');
  }
  else {
    require_once(drupal_get_path('module', 'nyss_signup') . '/includes/bronto_api.inc');
    $bronto = new bronto_api(variable_get('bronto_login', ''), variable_get('bronto_sitename', ''), variable_get('bronto_password', ''));

    // Add the email to the mailing list
    $lists = $bronto->get_contact_lists($email);
    if (!count($lists)) {
      drupal_set_message('No lists found for that email address.');
      drupal_goto('nyss_signup/unsubscribe');
    }
    
    $output .= drupal_get_form('nyss_signup_unsubscribe_lists_form', $lists, $email);
  }
  
  return $output;
}

/**
 * Form to enter an email address to pull lists for unsubscribing.
 * @return
 *   FormAPI array.
 */
function nyss_signup_unsubscribe_email_form() {
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Implementation of hook_submit().
 */
function nyss_signup_unsubscribe_email_form_submit(&$form, &$form_state) {
  $form['#redirect'] = 'nyss_signup/unsubscribe/' . $form_state['values']['email'];
}

/**
 * Form that allows users to select from which lists to unsubscribe.
 * @param $lists
 *   Array of list names that the email is subscribed to.
 * @return
 *   FormAPI array.
 */
function nyss_signup_unsubscribe_lists_form($form_state, $lists, $email) {
  $form['email'] = array(
    '#type' => 'value',
    '#value' => $email,
  );

  $options = array();
  sort($lists);
  foreach ($lists as $list) {
    $options[$list] = $list;
  }
  
  $form['lists'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Your lists'),
    '#description' => t('Check the lists from which you wish to unsubscribe.'),
    '#options' => $options,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Unsubscribe'),
  );
  return $form;
}

/**
 * Implementation of hook_submit().
 */
function nyss_signup_unsubscribe_lists_form_submit(&$form, &$form_state) {
  require_once(drupal_get_path('module', 'nyss_signup') . '/includes/bronto_api.inc');
  $bronto = new bronto_api(variable_get('bronto_login', ''), variable_get('bronto_sitename', ''), variable_get('bronto_password', ''));

  $lists = array();
  foreach ($form_state['values']['lists'] as $list) {
    if ($list) {
      $lists[] = $list;
      $bronto->remove_email_from_list($form_state['values']['email'], $list);
    }
  }
  if (count($lists)) {
    // Send unsubscribe confirmation email
    $body = t(variable_get('bronto_subscription_unsubscribe_body', nyss_signup_unsubscribe_body_default()), array('!site' => variable_get('site_name', ''), '!lists' => implode("\n", $lists), '!site_link' => url('', array('absolute' => TRUE))));

    $response = $bronto->send_message(
      $user->name,
      variable_get('site_mail', ini_get('sendmail_from')),
      $form_state['values']['email'],
      t('Unsubscribed from !site mailing lists', array('!site' => variable_get('site_name', ''))),
      preg_replace('/\n/', '<br />', $body),
      l(t('View'), 'nyss_signup/unsubscribe/' . $form_state['values']['email'], array('absolute' => TRUE)) . ' your subscriptions.',
      'html',
      'contact'
    );
    drupal_set_message(t('You have successfully unsubscribed from the checked lists.'));
  }
  else {
    drupal_set_message(t('You have not unsubscribed from any lists.'));
  }
  $form['#redirect'] = 'nyss_signup/unsubscribe/' . $form_state['values']['email'];
}
