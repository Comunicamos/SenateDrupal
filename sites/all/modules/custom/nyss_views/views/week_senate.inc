<?php

$view = new view;
$view->name = 'week_senate';
$view->description = 'This week in the senate';
$view->tag = 'week senate flag ';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'flag_content_rel' => array(
    'label' => '',
    'required' => 1,
    'flag' => 'promote_to_front',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'field_date_value' => array(
    'label' => '',
    'link_to_node' => 0,
    'label_type' => 'none',
    'format' => 'default',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_date_value',
    'table' => 'node_data_field_date',
    'field' => 'field_date_value',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
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
));
$handler->override_option('sorts', array(
  'field_date_value' => array(
    'order' => 'ASC',
    'delta' => -1,
    'id' => 'field_date_value',
    'table' => 'node_data_field_date',
    'field' => 'field_date_value',
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
      'node_data_field_date.field_date_value' => 'node_data_field_date.field_date_value',
      'node_data_field_date.field_date_value2' => 'node_data_field_date.field_date_value2',
    ),
    'year_range' => '-3:+3',
    'date_method' => 'OR',
    'granularity' => 'week',
    'id' => 'date_argument',
    'table' => 'node',
    'field' => 'date_argument',
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '',
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
      '4' => 0,
      '1' => 0,
      '3' => 0,
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
    'validate_user_argument_type' => 'uid',
    'validate_user_roles' => array(
      '2' => 0,
      '3' => 0,
      '4' => 0,
      '7' => 0,
      '8' => 0,
      '5' => 0,
    ),
    'override' => array(
      'button' => 'Override',
    ),
    'validate_argument_transform' => 0,
    'validate_user_restrict_roles' => 0,
  ),
));
$handler->override_option('filters', array(
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
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('empty', 'No currently featured events.');
$handler->override_option('empty_format', '1');
$handler->override_option('items_per_page', 5);
$handler->override_option('distinct', 1);
$handler->override_option('style_plugin', 'list');
$handler->override_option('style_options', array(
  'type' => 'ul',
));
$handler->override_option('row_plugin', 'node');
$handler = $view->new_display('block', 'This week in the senate', 'block_1');
$handler->override_option('title', 'This week in the senate');
$handler->override_option('footer', '<?php print l(\'More events...\',\'calendar\'); ?>');
$handler->override_option('footer_format', '3');
$handler->override_option('footer_empty', 1);
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => '',
  'override' => 1,
  'sticky' => 0,
  'order' => 'asc',
  'columns' => array(
    'title' => 'title',
    'field_date_value' => 'field_date_value',
  ),
  'info' => array(
    'title' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'field_date_value' => array(
      'sortable' => 0,
      'separator' => '',
    ),
  ),
  'default' => '-1',
));
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);
$views[$view->name] = $view;
