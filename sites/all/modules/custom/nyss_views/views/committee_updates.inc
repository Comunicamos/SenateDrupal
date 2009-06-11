<?php

$view = new view;
$view->name = 'committee_updates';
$view->description = 'Committee Updates';
$view->tag = 'committee';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'field_committee_nid' => array(
    'label' => 'Committee',
    'required' => 0,
    'delta' => -1,
    'id' => 'field_committee_nid',
    'table' => 'node_data_field_committee',
    'field' => 'field_committee_nid',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'created' => array(
    'label' => '',
    'date_format' => 'custom',
    'custom_date_format' => 'l, F jS, Y',
    'exclude' => 0,
    'id' => 'created',
    'table' => 'node',
    'field' => 'created',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'tid' => array(
    'label' => '',
    'type' => 'separator',
    'separator' => ', ',
    'empty' => '',
    'link_to_taxonomy' => 1,
    'limit' => 1,
    'vids' => array(
      '1' => 1,
      '2' => 0,
    ),
    'exclude' => 0,
    'id' => 'tid',
    'table' => 'term_node',
    'field' => 'tid',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'teaser' => array(
    'label' => '',
    'exclude' => 0,
    'id' => 'teaser',
    'table' => 'node_revisions',
    'field' => 'teaser',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'view_node' => array(
    'label' => '',
    'text' => 'Read more...',
    'exclude' => 0,
    'id' => 'view_node',
    'table' => 'node',
    'field' => 'view_node',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'nid' => array(
    'label' => '',
    'link_to_node' => 0,
    'exclude' => 1,
    'id' => 'nid',
    'table' => 'node',
    'field' => 'nid',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('sorts', array(
  'created' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'created',
    'table' => 'node',
    'field' => 'created',
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'title' => array(
    'default_action' => 'not found',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '%1 Updates',
    'default_argument_type' => 'fixed',
    'default_argument' => '',
    'validate_type' => 'php',
    'validate_fail' => 'not found',
    'glossary' => 0,
    'limit' => '0',
    'case' => 'ucwords',
    'path_case' => 'none',
    'transform_dash' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'field_committee_nid',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '',
    'validate_argument_node_type' => array(
      'blog' => 0,
      'committee' => 0,
      'district' => 0,
      'event' => 0,
      'in_the_news' => 0,
      'legislation' => 0,
      'page' => 0,
      'photo' => 0,
      'press_release' => 0,
      'report' => 0,
      'senator' => 0,
      'testimony' => 0,
      'video' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
      '1' => 0,
      '2' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_node_flag_name' => '*relationship*',
    'validate_argument_node_flag_test' => 'flaggable',
    'validate_argument_node_flag_id_type' => 'id',
    'validate_argument_user_flag_name' => '*relationship*',
    'validate_argument_user_flag_test' => 'flaggable',
    'validate_argument_user_flag_id_type' => 'id',
    'validate_argument_php' => '$committee = nyss_senator_committee();
                if ($committee) {
                  $handler->argument = check_plain($committee->title);
                  return $handler->argument;
                }
                ',
    'override' => array(
      'button' => 'Override',
    ),
  ),
));
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => '1',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'status',
    'table' => 'node',
    'field' => 'status',
    'relationship' => 'none',
  ),
  'type' => array(
    'operator' => 'in',
    'value' => array(
      'blog' => 'blog',
      'event' => 'event',
      'in_the_news' => 'in_the_news',
      'legislation' => 'legislation',
      'press_release' => 'press_release',
      'report' => 'report',
      'testimony' => 'testimony',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('title', 'Committee Updates');
$handler->override_option('items_per_page', 7);
$handler->override_option('use_pager', '1');
$handler->override_option('row_plugin', 'node');
$handler->override_option('row_options', array(
  'teaser' => 1,
  'links' => 1,
  'comments' => 0,
));
$handler = $view->new_display('page', 'Per Committee Page', 'page_1');
$handler->override_option('path', 'committee/%/updates');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
));
$handler = $view->new_display('block', 'Per Committe Block', 'block_1');
$handler->override_option('arguments', array(
  'title' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => 'Committee Updates',
    'default_argument_type' => 'php',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'glossary' => 0,
    'limit' => '0',
    'case' => 'ucwords',
    'path_case' => 'none',
    'transform_dash' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'field_committee_nid',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '$committee = nyss_senator_committee();
            if ($committee) {
              $handler->argument = check_plain($committee->title);
              return $handler->argument;
            }',
    'validate_argument_node_type' => array(
      'blog' => 0,
      'poll' => 0,
      'committee' => 0,
      'district' => 0,
      'event' => 0,
      'in_the_news' => 0,
      'legislation' => 0,
      'page' => 0,
      'photo' => 0,
      'press_release' => 0,
      'report' => 0,
      'senator' => 0,
      'story' => 0,
      'testimony' => 0,
      'video' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
      '1' => 0,
      '2' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_node_flag_name' => '*relationship*',
    'validate_argument_node_flag_test' => 'flaggable',
    'validate_argument_node_flag_id_type' => 'id',
    'validate_argument_user_flag_name' => '*relationship*',
    'validate_argument_user_flag_test' => 'flaggable',
    'validate_argument_user_flag_id_type' => 'id',
    'validate_argument_php' => '',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
));
$handler->override_option('items_per_page', 3);
$handler->override_option('use_pager', '0');
$handler->override_option('use_more', 1);
$handler->override_option('row_plugin', 'fields');
$handler->override_option('row_options', array(
  'inline' => array(),
  'separator' => '',
));
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);
$handler = $view->new_display('page', 'All Committees Page', 'page_2');
$handler->override_option('arguments', array());
$handler->override_option('title', 'Committees Updates');
$handler->override_option('path', 'committees/updates');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
));
$handler = $view->new_display('block', 'From my committee', 'block_2');
$handler->override_option('fields', array(
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
  ),
  'teaser' => array(
    'label' => '',
    'exclude' => 0,
    'id' => 'teaser',
    'table' => 'node_revisions',
    'field' => 'teaser',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'field_committee_nid' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '',
    'default_argument_type' => 'php',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'break_phrase' => 1,
    'not' => 0,
    'id' => 'field_committee_nid',
    'table' => 'node_data_field_committee',
    'field' => 'field_committee_nid',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '$committees = nyss_senator_get_committees();
    if ($committees) {
      $handler->argument = implode(\'+\', array_keys($committees));
      return $handler->argument;
    }',
    'validate_argument_node_type' => array(
      'blog' => 0,
      'poll' => 0,
      'committee' => 0,
      'district' => 0,
      'event' => 0,
      'in_the_news' => 0,
      'legislation' => 0,
      'page' => 0,
      'photo' => 0,
      'press_release' => 0,
      'report' => 0,
      'senator' => 0,
      'story' => 0,
      'testimony' => 0,
      'video' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
      '1' => 0,
      '2' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_node_flag_name' => '*relationship*',
    'validate_argument_node_flag_test' => 'flaggable',
    'validate_argument_node_flag_id_type' => 'id',
    'validate_argument_user_flag_name' => '*relationship*',
    'validate_argument_user_flag_test' => 'flaggable',
    'validate_argument_user_flag_id_type' => 'id',
    'validate_argument_php' => '',
  ),
));
$handler->override_option('title', 'From My Committee');
$handler->override_option('items_per_page', 1);
$handler->override_option('use_pager', '0');
$handler->override_option('row_plugin', 'fields');
$handler->override_option('row_options', array());
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);
$handler = $view->new_display('feed', 'Feed', 'feed_1');
$handler->override_option('style_plugin', 'rss');
$handler->override_option('style_options', array(
  'mission_description' => FALSE,
  'description' => '',
));
$handler->override_option('row_plugin', 'node_rss');
$handler->override_option('row_options', array(
  'item_length' => 'default',
));
$handler->override_option('path', 'committee/%/updates/feed');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
));
$handler->override_option('displays', array());
$handler->override_option('sitename_title', FALSE);

$views[$view->name] = $view;