<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Committee Issues' block
 */

/**
 *  Subject of the 'Committee Issues' block.
 *
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_committee_issues() {
  return t('Committee Issues');
}

/**
 *  Display the content of the 'Committee Issues' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_committee_issues() {
  $committee = nyss_senator_committee();
  $terms = nyss_block_committee_issues_get_taxonomy($committee->nid);
  if (empty($terms)) return FALSE;

  $output = '';
  $output .= t('Read more about the @committee\'s subtopics', array('@committee' => $committee->title));
  $output .= '<ul>';
  foreach ($terms as $tid => $term) {
    $output .= '<li>'. l($term, 'committee/'. strtolower(str_replace(' ', '_', $committee->title)) .'/issues/'. strtolower(str_replace(' ', '_', $term))) .'</li>';
  }
  $output .= '</ul>';
  return $output;
}

/**
 *  Get the content of the terms that the committee has content assigned to.
 *
 *  @return
 *    The array of terms.
 */
function nyss_block_committee_issues_get_taxonomy($nid) {
  $results = db_query('SELECT tn.tid, td.name FROM {term_node} tn INNER JOIN {term_data} td ON tn.tid = td.tid 
    INNER JOIN {content_field_committee} cfc ON tn.nid = cfc.nid WHERE cfc.field_committee_nid = %d AND td.vid = 1 ORDER BY td.name ASC', $nid);
  $terms = array();
  while ($term = db_fetch_object($results)) {
    $clean_name = check_plain($term->name);
    $terms[$term->tid] = $clean_name;
  }
  return $terms;
}