<?php

function theme_nyss_signup_send_mail_preview($fields) {
  $output = '<h2>'. t('Preview') .'</h2>';

  $box .= t('<strong>To:</strong> !list', array('!list' => $fields['list'])) .'<br/>';   
  $box .= t('<strong>From:</strong> !email', array('!email' => $fields['from'])) .'<br/>';  
  $box .= t('<strong>Subject:</strong> !subject', array('!subject' => $fields['subject'])) .'<br/><br/>';
  $box .= _filter_url(preg_replace('/\n/', '<br />', $fields['body_text']), -1);
  
  $output .= theme('box', NULL, $box);
  
  return $output;
}

function theme_nyss_signup_block() {
  $output .= drupal_get_form('nyss_signup_block_form');
  return $output;
}