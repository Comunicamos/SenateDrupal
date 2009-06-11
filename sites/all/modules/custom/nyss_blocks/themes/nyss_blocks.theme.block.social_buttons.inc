<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Social buttons' block
 */

/**
 *  Subject of the 'Social buttons' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_social_buttons() {
  $senator = nyss_senator();
  // If we are on a senator page use senator title setting for block title.
  if (!empty($senator)) {
    // Replace the [senator] token with the senator's name.
    return str_replace('[senator]', strip_tags($senator->title), variable_get('nyss_blocks_social_buttons_senator', ''));
  }
  else {
    return variable_get('nyss_blocks_social_buttons_overall_title', '');
  }
}

/**
 *  Display the content of the 'Social buttons' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_social_buttons($senator = NULL) {
  if ($senator == NULL) {
    $senator = nyss_senator();
  }

  $output = '';
  // If not on a senator page then use the overall settings else use senator's.
  if (empty($senator)) {
    $overall_links = variable_get('nyss_blocks_social_buttons_overall_links', array());
    
    $text = t("RSS feed of @senator's content", array('@senator' => $senator->title));
    $rss = l('RSS', 'rss', array('attributes' => array('class' => 'rss', 'title' => $text)));
    
    if (!empty($overall_links['facebook'])) {
      $text = t("New York Senates' Facebook profile");
      $facebook = l('Facebook', $overall_links['facebook'], array('attributes' => array('class' => 'facebook', 'title' => $text)));
    }
    if (!empty($overall_links['twitter'])) {
      $text = t("Follow the New York Senate on Twitter");
      $twitter = l('Twitter', $overall_links['twitter'], array('attributes' => array('class' => 'twitter', 'title' => $text)));
    }
  }
  else {
    $text = t("RSS feed of @senator's content", array('@senator' => $senator->title));
    $rss = l('RSS', $senator->path . '/content/feed', array('attributes' => array('class' => 'rss', 'title' => $text)));
    
    if ($senator->field_facebook_link[0]['url']) {
      $text = t("@senator's Facebook profile", array('@senator' => $senator->title));
      $facebook = l('Facebook', $senator->field_facebook_link[0]['url'], array('attributes' => array('class' => 'facebook', 'title' => $text)));
    }
    if ($senator->field_twitter_link[0]['url']) {
      $text = t("Follow @senator on Twitter", array('@senator' => $senator->title));
      $twitter = l('Twitter', $senator->field_twitter_link[0]['url'], array('attributes' => array('class' => 'twitter', 'title' => $text)));
    }
  }

  if ($facebook || $twitter || $rss) {
    $output .= '<div id="social_buttons">'. $rss . $twitter . $facebook .'</div>';
  }
  return $output;
}

/**
 * Configurations for hook_block delta 'social_buttons'.
 *
 * @return array $form
 */
function nyss_blocks_configure_form_social_buttons() {
  $form['overall'] = array(
    '#type' => 'fieldset',
    '#title' => t('Overall block settings'),
    '#weight' => -9999,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('These are the settings that will be used when <strong>NOT</strong> on a senator page.'),
  );
  $form['overall']['overall_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => variable_get('nyss_blocks_social_buttons_overall_title', ''),
    '#size' => 60,
    '#maxlength' => 128,
  );
  $overall_links = variable_get('nyss_blocks_social_buttons_overall_links', array());
  $form['overall']['facebook'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook link'),
    '#default_value' => $overall_links['facebook'],
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t("Please enter the URL to the senate's Facebook page, if it exists."),
  );
  $form['overall']['twitter'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter link'),
    '#default_value' => $overall_links['twitter'],
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t("Please enter the URL to the senate's Twitter page, if it exists."),
  );
  $form['senator'] = array(
    '#type' => 'fieldset',
    '#title' => t('Senator settings'),
    '#weight' => -9999,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('These are the settings that will be used when on a senator page.'),
  );
  $form['senator']['senator_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => variable_get('nyss_blocks_social_buttons_senator', ''),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('You may use [senator] as a place holder for the senator name.')
  );
  return $form;
}

/**
 * Save for hook_block delta 'social_buttons'.
 *
 * @param array $edit
 */
function nyss_blocks_configure_form_save_social_buttons($edit) {
  variable_set('nyss_blocks_social_buttons_overall_title', $edit['overall_title']);
  variable_set('nyss_blocks_social_buttons_overall_links', array('facebook' => $edit['facebook'], 'twitter' => $edit['twitter']));
  variable_set('nyss_blocks_social_buttons_senator', $edit['senator_title']);
}
