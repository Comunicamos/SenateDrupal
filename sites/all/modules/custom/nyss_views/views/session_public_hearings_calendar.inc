<?php

$view = new view;
$view->name = 'session_public_hearings_calendar';
$view->description = 'A multi-dimensional calendar view with back/next navigation.';
$view->tag = 'Calendar';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('fields', array(
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'field' => 'title',
    'table' => 'node',
    'relationship' => 'none',
  ),
  'changed' => array(
    'label' => '',
    'link_to_node' => 0,
    'exclude' => 0,
    'id' => 'changed',
    'field' => 'changed',
    'table' => 'node',
    'relationship' => 'none',
    'date_format' => 'small',
  ),
));
$handler->override_option('sorts', array(
  'changed' => array(
    'order' => 'ASC',
    'delta' => '-1',
    'id' => 'changed',
    'table' => 'node',
    'field' => 'changed',
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'date_argument' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '',
    'default_argument_type' => 'date',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'date_fields' => array(
      'node.changed' => 'node.changed',
    ),
    'year_range' => '-3:+3',
    'date_method' => 'OR',
    'granularity' => 'month',
    'id' => 'date_argument',
    'table' => 'node',
    'field' => 'date_argument',
    'relationship' => 'none',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '',
    'validate_argument_node_type' => array(),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(),
    'validate_argument_type' => 'tid',
    'validate_argument_php' => '',
    'override' => array(
      'button' => 'Override',
    ),
    'default_options_div_prefix' => '',
  ),
));
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => 1,
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
      'event' => 'event',
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
  'field_public_hearing_value_many_to_one' => array(
    'operator' => 'or',
    'value' => array(
      '1' => '1',
      '2' => '2',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'field_public_hearing_value_many_to_one',
    'table' => 'node_data_field_public_hearing',
    'field' => 'field_public_hearing_value_many_to_one',
    'relationship' => 'none',
    'reduce_duplicates' => 0,
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
  'role' => array(),
  'perm' => '',
));
$handler->override_option('title', 'Sessions and Public Hearings');
$handler->override_option('items_per_page', 0);
$handler->override_option('use_more', 0);
$handler->override_option('style_plugin', 'calendar_nav');
$handler = $view->new_display('calendar', 'Calendar page', 'calendar_1');
$handler->override_option('path', 'session_public_hearings');
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
$handler->override_option('calendar_colors', array(
  '0' => array(),
));
$handler = $view->new_display('calendar_block', 'Calendar block', 'calendar_block_1');
$handler->override_option('block_description', 'Session and Public Hearing Calendar');
$handler->override_option('block_caching', -1);
$handler = $view->new_display('calendar_period', 'Year view', 'calendar_period_1');
$handler->override_option('style_plugin', 'calendar_style');
$handler->override_option('style_options', array(
  'display_type' => 'year',
  'name_size' => 1,
  'max_items' => 0,
  'truncated_fields' => array(),
  'truncate_length' => '',
));
$handler->override_option('attachment_position', 'after');
$handler->override_option('inherit_arguments', TRUE);
$handler->override_option('inherit_exposed_filters', TRUE);
$handler->override_option('displays', array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 0,
));
$handler->override_option('calendar_type', 'year');
$handler = $view->new_display('calendar_period', 'Month view', 'calendar_period_2');
$handler->override_option('style_plugin', 'calendar_style');
$handler->override_option('style_options', array(
  'display_type' => 'month',
  'name_size' => '99',
  'with_weekno' => '1',
  'date_fields' => NULL,
  'max_items' => 0,
  'truncated_fields' => array(),
  'truncate_length' => '',
));
$handler->override_option('attachment_position', 'after');
$handler->override_option('inherit_arguments', TRUE);
$handler->override_option('inherit_exposed_filters', TRUE);
$handler->override_option('displays', array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 0,
));
$handler->override_option('calendar_type', 'month');
$handler = $view->new_display('calendar_period', 'Day view', 'calendar_period_3');
$handler->override_option('style_plugin', 'calendar_style');
$handler->override_option('style_options', array(
  'name_size' => '99',
  'with_weekno' => 0,
  'max_items' => 0,
  'max_items_behavior' => 'more',
  'groupby_times' => 'hour',
  'groupby_times_custom' => '',
  'groupby_field' => '',
  'truncated_fields' => array(),
  'truncate_length' => '',
));
$handler->override_option('attachment_position', 'after');
$handler->override_option('inherit_arguments', TRUE);
$handler->override_option('inherit_exposed_filters', TRUE);
$handler->override_option('displays', array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 0,
));
$handler->override_option('calendar_type', 'day');
$handler = $view->new_display('calendar_period', 'Week view', 'calendar_period_4');
$handler->override_option('style_plugin', 'calendar_style');
$handler->override_option('style_options', array(
  'name_size' => '99',
  'with_weekno' => 0,
  'max_items' => 0,
  'max_items_behavior' => 'more',
  'groupby_times' => 'hour',
  'groupby_times_custom' => '',
  'groupby_field' => '',
  'truncated_fields' => array(),
  'truncate_length' => '',
));
$handler->override_option('attachment_position', 'after');
$handler->override_option('inherit_arguments', TRUE);
$handler->override_option('inherit_exposed_filters', TRUE);
$handler->override_option('displays', array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 0,
));
$handler->override_option('calendar_type', 'week');
$handler = $view->new_display('calendar_period', 'Block view', 'calendar_period_5');
$handler->override_option('style_plugin', 'calendar_style');
$handler->override_option('style_options', array(
  'display_type' => 'month',
  'name_size' => '1',
));
$handler->override_option('attachment_position', 'after');
$handler->override_option('inherit_arguments', TRUE);
$handler->override_option('inherit_exposed_filters', TRUE);
$handler->override_option('displays', array(
  'calendar_1' => 0,
  'default' => 0,
  'calendar_block_1' => 'calendar_block_1',
));
$handler->override_option('calendar_type', 'month');
$handler = $view->new_display('calendar_ical', 'iCal feed', 'calendar_ical_1');
$handler->override_option('arguments', array());
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => 1,
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
  'date_filter' => array(
    'operator' => '>=',
    'value' => array(
      'value' => NULL,
      'min' => NULL,
      'max' => NULL,
      'default_date' => 'now',
      'default_to_date' => '',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'date_fields' => array(
      'node.changed' => 'node.changed',
    ),
    'granularity' => 'day',
    'form_type' => 'date_select',
    'default_date' => 'now',
    'default_to_date' => '',
    'id' => 'date_filter',
    'table' => 'node',
    'field' => 'date_filter',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('style_plugin', 'ical');
$handler->override_option('style_options', array(
  'mission_description' => FALSE,
  'description' => '',
  'summary_field' => 'node_title',
  'description_field' => '',
  'location_field' => '',
));
$handler->override_option('row_plugin', '');
$handler->override_option('path', 'calendar/ical');
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
$handler->override_option('displays', array(
  'calendar_1' => 'calendar_1',
  'default' => 0,
  'calendar_block_1' => 'calendar_block_1',
));
$handler->override_option('sitename_title', FALSE);
$handler = $view->new_display('block', 'Upcoming', 'block_1');
$handler->override_option('fields', array(
  'title' => array(
    'label' => '',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'field' => 'title',
    'table' => 'node',
    'relationship' => 'none',
    'format' => 'default',
  ),
  'changed' => array(
    'label' => '',
    'link_to_node' => 0,
    'exclude' => 0,
    'id' => 'changed',
    'field' => 'changed',
    'table' => 'node',
    'relationship' => 'none',
    'date_format' => 'small',
    'format' => 'default',
  ),
));
$handler->override_option('arguments', array());
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => 1,
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
  'date_filter' => array(
    'operator' => '>=',
    'value' => array(
      'value' => NULL,
      'min' => NULL,
      'max' => NULL,
      'default_date' => 'now',
      'default_to_date' => '',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'date_fields' => array(
      'node.changed' => 'node.changed',
    ),
    'granularity' => 'day',
    'form_type' => 'date_select',
    'default_date' => 'now',
    'default_to_date' => '',
    'id' => 'date_filter',
    'table' => 'node',
    'field' => 'date_filter',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('items_per_page', 5);
$handler->override_option('use_more', 1);
$handler->override_option('style_plugin', 'list');
$handler->override_option('style_options', array(
  'grouping' => '',
  'type' => 'ul',
));
$handler->override_option('block_description', 'Upcoming');
$handler->override_option('block_caching', -1);

$views[$view->name] = $view;