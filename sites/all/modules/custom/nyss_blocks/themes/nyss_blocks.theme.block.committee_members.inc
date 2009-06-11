<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'Committee Members' block
 */

/**
 *  Subject of the 'Committee Members' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_committee_members() {
  return t('Committee Members');
}

/**
 *  Display the content of the 'Committee Members' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_committee_members() {
  $committee = nyss_senator_committee();

  $output = '';
  $params = array();
  foreach ($committee->field_multi_senator as $senator) {
    $params[] = $senator['nid'];
  }
  $output .= '<div class="committee_members">';
  $output .= views_embed_view('committee_members', 'default', implode('+', $params));
  $output .= '</div>';
  return $output;
}
