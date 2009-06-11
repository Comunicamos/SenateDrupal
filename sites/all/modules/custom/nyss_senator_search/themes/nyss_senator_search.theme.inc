<?php

function theme_nyss_senator_search() {
  $output .= drupal_get_form('nyss_senator_search_form');
  return $output;
}