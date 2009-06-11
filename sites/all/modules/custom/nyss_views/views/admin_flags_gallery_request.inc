<?php

$view = new view;
$view->name = 'admin_flags_gallery_request';
$view->description = 'An administrator\'s list of content requested to be promoted to the main Senate Gallery page.';
$view->tag = 'admin';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'flag_content_rel' => array(
    'label' => 'Request to promote to main gallery',
    'required' => 1,
    'flag' => 'request_to_gallery',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'flag_content_rel_1' => array(
    'label' => 'Promoted to Main Senate Gallery',
    'required' => 0,
    'flag' => 'promote_to_main_gallery',
    'user_scope' => 'any',
    'id' => 'flag_content_rel_1',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'title' => array(
    'label' => 'Post',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
  ),
  'field_feature_image_fid' => array(
    'label' => 'Photo',
    'link_to_node' => 0,
    'label_type' => 'custom',
    'format' => 'senator_teaser_imagelink',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_feature_image_fid',
    'table' => 'node_data_field_feature_image',
    'field' => 'field_feature_image_fid',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'ops' => array(
    'label' => 'Promote',
    'exclude' => 0,
    'id' => 'ops',
    'table' => 'flag_content',
    'field' => 'ops',
    'relationship' => 'flag_content_rel_1',
  ),
  'ops_1' => array(
    'label' => 'Deny request',
    'exclude' => 0,
    'id' => 'ops_1',
    'table' => 'flag_content',
    'field' => 'ops',
    'relationship' => 'flag_content_rel',
  ),
  'edit_node' => array(
    'label' => 'Edit',
    'text' => 'edit content',
    'exclude' => 0,
    'id' => 'edit_node',
    'table' => 'node',
    'field' => 'edit_node',
    'relationship' => 'none',
  ),
));
$handler->override_option('sorts', array(
  'timestamp' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'timestamp',
    'table' => 'flag_content',
    'field' => 'timestamp',
    'relationship' => 'flag_content_rel',
    'override' => array(
      'button' => 'Override',
    ),
  ),
));
$handler->override_option('filters', array(
  'flagged' => array(
    'operator' => '=',
    'value' => '1',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'flagged',
    'table' => 'flag_content',
    'field' => 'flagged',
    'relationship' => 'flag_content_rel',
    'override' => array(
      'button' => 'Override',
    ),
  ),
  'flagged_1' => array(
    'operator' => '=',
    'value' => '0',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'flagged_1',
    'table' => 'flag_content',
    'field' => 'flagged',
    'relationship' => 'flag_content_rel_1',
  ),
));
$handler->override_option('access', array(
  'type' => 'role',
  'role' => array(
    '3' => 3,
    '5' => 5,
  ),
));
$handler->override_option('header', 'Content that has been marked with the \'request to promote photo to main gallery\' by an office editor will appear on this page.');
$handler->override_option('header_format', '1');
$handler->override_option('header_empty', 1);
$handler->override_option('empty', 'There are currently no items for review for promotion to the gallery.');
$handler->override_option('empty_format', '1');
$handler->override_option('items_per_page', 50);
$handler->override_option('use_pager', '1');
$handler->override_option('style_plugin', 'table');
$handler = $view->new_display('page', 'Page: Gallery Administration', 'page_1');
$handler->override_option('title', 'Senate gallery administration');
$handler->override_option('path', 'nyss-admin/flags/gallery-promote');
$handler->override_option('menu', array(
  'type' => 'normal',
  'title' => 'Senate gallery administration',
  'weight' => '0',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
));
$handler = $view->new_display('page', 'Page: Video Gallery Administration', 'page_2');
$handler->override_option('relationships', array(
  'flag_content_rel' => array(
    'label' => 'Request to promote video to main gallery',
    'required' => 1,
    'flag' => 'request_video_to_gallery',
    'user_scope' => 'any',
    'id' => 'flag_content_rel',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
  ),
  'flag_content_rel_1' => array(
    'label' => 'Promoted to Main Senate Video Gallery',
    'required' => 0,
    'flag' => 'promote_video_to_main_gallery',
    'user_scope' => 'any',
    'id' => 'flag_content_rel_1',
    'table' => 'node',
    'field' => 'flag_content_rel',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
));
$handler->override_option('fields', array(
  'title' => array(
    'label' => 'Post',
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
  ),
  'field_video_embed' => array(
    'label' => 'Video',
    'link_to_node' => 0,
    'label_type' => 'custom',
    'format' => 'thickbox',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_video_embed',
    'table' => 'node_data_field_video',
    'field' => 'field_video_embed',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'none',
  ),
  'ops' => array(
    'label' => 'Promote',
    'exclude' => 0,
    'id' => 'ops',
    'table' => 'flag_content',
    'field' => 'ops',
    'relationship' => 'flag_content_rel_1',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'ops_1' => array(
    'label' => 'Deny request',
    'exclude' => 0,
    'id' => 'ops_1',
    'table' => 'flag_content',
    'field' => 'ops',
    'relationship' => 'flag_content_rel',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'edit_node' => array(
    'label' => 'Edit',
    'text' => 'edit content',
    'exclude' => 0,
    'id' => 'edit_node',
    'table' => 'node',
    'field' => 'edit_node',
    'relationship' => 'none',
  ),
));
$handler->override_option('sorts', array(
  'timestamp' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'timestamp',
    'table' => 'flag_content',
    'field' => 'timestamp',
    'relationship' => 'flag_content_rel',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
));
$handler->override_option('filters', array(
  'flagged' => array(
    'operator' => '=',
    'value' => '1',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'flagged',
    'table' => 'flag_content',
    'field' => 'flagged',
    'relationship' => 'flag_content_rel',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
  'flagged_1' => array(
    'operator' => '=',
    'value' => '0',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'flagged_1',
    'table' => 'flag_content',
    'field' => 'flagged',
    'relationship' => 'flag_content_rel_1',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
));
$handler->override_option('title', 'Senate video gallery administration');
$handler->override_option('header', 'Content that has been marked with the \'request to promote video to main gallery\' by an office editor will appear on this page.');
$handler->override_option('empty', 'There are currently no items for review for promotion to the video gallery.');
$handler->override_option('path', 'nyss-admin/flags/video-gallery-promote');
$handler->override_option('menu', array(
  'type' => 'normal',
  'title' => 'Senate video gallery administration',
  'weight' => '0',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
));
$views[$view->name] = $view;
