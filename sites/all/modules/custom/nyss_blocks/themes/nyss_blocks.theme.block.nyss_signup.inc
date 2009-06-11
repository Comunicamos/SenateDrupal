<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Signup' block
 */

/**
 *  Subject of the 'Signup' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_nyss_signup() {
  $subject = t('Sign up for Senate Updates: ');
  $senator = nyss_senator();
  if ($senator->vid) {
    $list = db_result(db_query("SELECT field_mailing_list_value FROM {content_field_mailing_list} WHERE vid = %d", $senator->vid));
    if ($list) {
      $subject = t('Sign Up For Updates<br />From !senator: ', array('!senator' => strip_tags($senator->title)));
    }
  }
  $committee = nyss_senator_committee();
  if ($committee->nid) {
    $list = db_result(db_query("SELECT field_mailing_list_value FROM {content_field_mailing_list} WHERE vid = %d", $committee->vid));
    if ($list) {
      $subject = t('Sign Up For Updates<br />From The @name Committee: ', array('@name' => $committee->title));
    }
  }
  return $subject;
}

/**
 *  Display the content of the 'Signup' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_nyss_signup() {
  return theme('nyss_signup_block');
}