<?php

/**
 *  @file
 *  NYSS Signup confirmation functions
 */

/**
 * Confirmation page after mailing list sign up (with options to sign up for more).
 */
function nyss_signup_confirm_page() {
  $output .= t('You are signing up for the !list mailing list. Fill out the form below to complete this process and opt in if you want to receive other updates from the New York Senate.', array('!list' => $_SESSION['bronto_list']));
  $output .= drupal_get_form('nyss_signup_confirm_form');
  return $output;
}

/*
 * Confirmation form allowing user to sign up for committee lists, and to fill in their personal info.
 */
function nyss_signup_confirm_form() {
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Your Information'),
  );
  $form['info']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => $_SESSION['bronto_email'],
  );
  $form['info']['firstname'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
  );
  $form['info']['lastname'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
  );
  $form['info']['address1'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 1'),
  );
  $form['info']['address2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 2'),
  );
  $form['info']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
  );
  $form['info']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#default_value' => 'New York',
  );
  $form['info']['zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#default_value' => $_SESSION['bronto_zip'],
  );
  $form['info']['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile'),
    '#default_value' => $_SESSION['bronto_mobile'],
  );

  $options = array();
  $options['New York Senate Updates'] = 'New York Senate Updates';
  $list = $_SESSION['bronto_list'];
  if(substr_count($list, 'District') > 0) {
	$options[$list] = $list;
  }
  $form['general_list'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Sign up for NY Senate Updates'),
    '#options' => $options,
    '#default_value' => array($list),
  );

  $options = array();
  $results = db_query("SELECT ml.field_mailing_list_value AS list FROM {content_field_mailing_list} ml JOIN {node} n ON ml.vid = n.vid WHERE n.type = 'committee' AND n.status = 1 ORDER BY list ASC");
  while ($obj = db_fetch_object($results)) {
    if ($obj->list) {
      $options[$obj->list] = $obj->list;
    }
  }

  $form['lists'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Sign Up for Committee Updates'),
    '#options' => $options,
    '#default_value' => array($_SESSION['bronto_list']),
  );
  
  $form['legal']['ver-age'] = array(
    '#type' => 'checkbox',
    '#title' => t('I confirm that I am over 13 years old'),
    '#default_Value' => 0,
    '#required' => TRUE,
    '#prefix' => '<div style="border-top: solid 1px #E2DED5;"></div>', 
  );
  $form['legal']['ver-priv'] = array(
    '#type' => 'checkbox',
    '#title' => t('I have read the ' . l('Privacy Policy', 'privacy-policy', array('attributes' => array('target' => '_blank'))) ),
    '#default_Value' => 0,
    '#required' => TRUE,
  );
  $form['legal']['ver-top'] = array(
    '#type' => 'checkbox',
    '#title' => t('I have read the ' . l('Terms of Participation', 'legal', array('attributes'=>array('target'=>'_blank')))),
    '#default_Value' => 0,
    '#required' => TRUE,
    '#suffix' => '<div style="border-top: solid 1px #E2DED5;">&nbsp;</div>', 
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
function nyss_signup_confirm_form_submit(&$form, &$form_state) {
  require_once(drupal_get_path('module', 'nyss_signup') . '/includes/bronto_api.inc');
  $bronto = new bronto_api(variable_get('bronto_login', ''), variable_get('bronto_sitename', ''), variable_get('bronto_password', ''));

  // Update the fields
  $fields = array();
  if ($form_state['values']['firstname']) {
    $fields['firstname'] = $form_state['values']['firstname'];
  }
  if ($form_state['values']['lastname']) {
    $fields['lastname'] = $form_state['values']['lastname'];
  }
  if ($form_state['values']['address1']) {
    $fields['address1'] = $form_state['values']['address1'];
  }
  if ($form_state['values']['address2']) {
    $fields['address2'] = $form_state['values']['address2'];
  }
  if ($form_state['values']['city']) {
    $fields['city'] = $form_state['values']['city'];
  }
  if ($form_state['values']['state']) {
    $fields['state'] = $form_state['values']['state'];
  }
  if ($form_state['values']['mobile']) {
    $fields['mobile'] = $form_state['values']['mobile'];
  }
  if ($form_state['values']['zip']) {
    $fields['zip'] = $form_state['values']['zip'];
  }
  if (count($fields)) {
    $response = $bronto->update_fields($form_state['values']['email'], $fields);
    if (!$response) {
      drupal_set_message('Error: ' . $bronto->get_error_code() . "<br/>" . $bronto->get_error_message(), 'error');
      return;
    }
  }

  // Add the email to the mailing lists
  // Start with the general list...
  $lists = array();
  foreach ($form_state['values']['general_list'] as $list) {
    if ($list) {
      $response = $bronto->add_email_to_list($form_state['values']['email'], $list);
      if (!$response) {
        drupal_set_message('Error: ' . $bronto->get_error_code() . "<br/>" . $bronto->get_error_message(), 'error');
        return;
      }
      $lists[] = $list;
    }
  }
  
  // ...Then do all the others.
  $lists = array();
  foreach ($form_state['values']['lists'] as $list) {
    if ($list) {
      $response = $bronto->add_email_to_list($form_state['values']['email'], $list);
      if (!$response) {
        drupal_set_message('Error: ' . $bronto->get_error_code() . "<br/>" . $bronto->get_error_message(), 'error');
        return;
      }
      $lists[] = $list;
    }
  }

  // Send confirmation email
  if (count($lists)) {
    $body = t(variable_get('bronto_subscription_confirm_body', nyss_signup_confirm_body_default()), array('!site' => variable_get('site_name', ''), '!lists' => implode("\n", $lists), '!unsubscribe_link' => url('nyss_signup/unsubscribe/' . $_SESSION['bronto_email'], array('absolute' => TRUE))));

    $response = $bronto->send_message(
      $user->name,
     variable_get('site_mail', ini_get('sendmail_from')),
      $form_state['values']['email'],
      t('Confirmation of subscription to !site mailing lists', array('!site' => variable_get('site_name', ''))),
      preg_replace('/\n/', '<br />', $body),
      l(t('View'), 'nyss_signup/unsubscribe/' . $form_state['values']['email'], array('absolute' => TRUE)) . ' your subscriptions.',
      'html',
      'contact'
    );
    drupal_set_message(t('Thank you.  You have successfully signed up for your selected committee updates.'));
  }
  else {
    drupal_set_message(t('Thank you.  Your information has been received.'));
  }
  $form_state['redirect'] = $_SESSION['bronto_redirect'];
}
