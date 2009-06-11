<?php
// $Id: template.php,v 1.17 2008/09/11 10:52:53 johnalbin Exp $

/**
 * @file
 * Contains theme override functions and preprocess functions for the theme.
 *
 * ABOUT THE TEMPLATE.PHP FILE
 *
 *   The template.php file is one of the most useful files when creating or
 *   modifying Drupal themes. You can add new regions for block content, modify
 *   or override Drupal's theme functions, intercept or make additional
 *   variables available to your theme, and create custom PHP logic. For more
 *   information, please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/theme-guide
 *
 * OVERRIDING THEME FUNCTIONS
 *
 *   The Drupal theme system uses special theme functions to generate HTML
 *   output automatically. Often we wish to customize this HTML output. To do
 *   this, we have to override the theme function. You have to first find the
 *   theme function that generates the output, and then "catch" it and modify it
 *   here. The easiest way to do it is to copy the original function in its
 *   entirety and paste it here, changing the prefix from theme_ to nys_.
 *   For example:
 *
 *     original: theme_breadcrumb()
 *     theme override: nys_breadcrumb()
 *
 *   where nys is the name of your sub-theme. For example, the
 *   zen_classic theme would define a zen_classic_breadcrumb() function.
 *
 *   If you would like to override any of the theme functions used in Zen core,
 *   you should first look at how Zen core implements those functions:
 *     theme_breadcrumbs()      in zen/template.php
 *     theme_menu_item_link()   in zen/template.php
 *     theme_menu_local_tasks() in zen/template.php
 *
 *   For more information, please visit the Theme Developer's Guide on
 *   Drupal.org: http://drupal.org/node/173880
 *
 * CREATE OR MODIFY VARIABLES FOR YOUR THEME
 *
 *   Each tpl.php template file has several variables which hold various pieces
 *   of content. You can modify those variables (or add new ones) before they
 *   are used in the template files by using preprocess functions.
 *
 *   This makes THEME_preprocess_HOOK() functions the most powerful functions
 *   available to themers.
 *
 *   It works by having one preprocess function for each template file or its
 *   derivatives (called template suggestions). For example:
 *     THEME_preprocess_page    alters the variables for page.tpl.php
 *     THEME_preprocess_node    alters the variables for node.tpl.php or
 *                              for node-forum.tpl.php
 *     THEME_preprocess_comment alters the variables for comment.tpl.php
 *     THEME_preprocess_block   alters the variables for block.tpl.php
 *
 *   For more information on preprocess functions, please visit the Theme
 *   Developer's Guide on Drupal.org: http://drupal.org/node/223430
 *   For more information on template suggestions, please visit the Theme
 *   Developer's Guide on Drupal.org: http://drupal.org/node/223440 and
 *   http://drupal.org/node/190815#template-suggestions
 */


// COMMENT OUT BEFORE LAUNCH!  THIS IS FOR THEME DEVELOPMENT USAGE ONLY.
// drupal_rebuild_theme_registry();


/*
 * Add any conditional stylesheets you will need for this sub-theme.
 *
 * To add stylesheets that ALWAYS need to be included, you should add them to
 * your .info file instead. Only use this section if you are including
 * stylesheets based on certain conditions.
 */
/* -- Delete this line if you want to use and modify this code
// Example: optionally add a fixed width CSS file.
if (theme_get_setting('nys_fixed')) {
  drupal_add_css(path_to_theme() . '/layout-fixed.css', 'theme', 'all');
}
// */


/**
 * Implementation of HOOK_theme().
 */
function nys_theme(&$existing, $type, $theme, $path) {
  $hooks = zen_theme($existing, $type, $theme, $path);
  // Add your theme hooks like this:
  /*
  $hooks['hook_name_here'] = array( // Details go here );
  */
  // @TODO: Needs detailed comments. Patches welcome!
  $hooks['search_theme_form'] = array(
	// Forms always take the form argument.
      'arguments' => array('form' => NULL),
  );
  return $hooks;
}

/**
 * Override or insert variables into all templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered (name of the .tpl.php file.)
 */
/* -- Delete this line if you want to use this function
function nys_preprocess(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the page templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function nys_preprocess_page(&$vars, $hook) {
  if ($node = menu_get_object()) {
    $variables['node'] = $node;
  }

// RANDOM BACKGROUND FOR HEADER - change second number in the rand() function to the amount of background images there are to rotate randomly through
  srand ((double) microtime( )*1000000);
  $random_number = rand(1,5);
  $vars['random_bg'] = 'bg-'.$random_number;
  $vars['senator'] = nyss_senator();
  $vars['senator_theme'] = $vars['senator']->field_theme[0]['value'];
  if ($vars['senator']->field_senators_district[0]['nid']) {
    $vars['district'] = node_load($vars['senator']->field_senators_district[0]['nid']);
  }

  // CUSTOM SEARCH PAGE TITLE
  if($vars['template_files'][1] == 'page-search-nyss_search') {
    $vars['title'] = 'Senator Search: ';
    if($vars['senator']->title != '') {
      $vars['title'] .= $vars['senator']->title;
      $vars['instructions'] = '<p>You are searching for content by Senator '.$vars['senator']->title.'. If you are looking for content by a different senator, search from within their page on '. l('this list', 'senators').'.</p>';
    } else {
      $vars['title'] .= 'No Senator Selected';
      $vars['instructions'] = '<p>You are searching for senator content, but have not selected a senator. Pick a senator from '. l('this list', 'senators').' and search from within their page.</p>';
    }
  }
  // Build out the Party Affiliation tag, $party_affiliation_list, as seen in the Senator Header
  if (is_array($vars['senator']->field_party_affiliation)) {
    $parties = array();
    foreach ($vars['senator']->field_party_affiliation as $party) {
      if ($party['value']) {
        $parties[] = $party['value'];
      }
    }
    $vars['party_affiliation_list'] = '('. implode(', ', $parties) .')';
  }

  // Create the main navigation menu.
  if (count($vars['senator']->field_navigation)) {
    // If we're on content related to a Senator, we'll replace the primary links with a custom sub-menu.
    $vars['primary_links'] = array();
    foreach ($vars['senator']->field_navigation as $count => $link) {
      // Make our custom URL replacements: [senator] with the senator's path, and [district] with the link to the district node.
      $link['url'] = str_replace('[senator]', $vars['senator']->field_path[0]['value'], /*str_replace(' ', '_', strtolower($vars['senator']->title))*/ $link['url']);
      if ($vars['senator']->field_senators_district[0]['nid']) {
        $link['url'] = str_replace('[district]', 'node/'. $vars['senator']->field_senators_district[0]['nid'], $link['url']);
      }

      // Add the link to the primary links array.
      $vars['primary_links']['menu-senator-'. $count] = array(
        'title' => $link['title'],
        'href' => $link['url'],
      );
    }

    // Finally, add a link to the main senate home page.
    //$vars['primary_links']['menu-senator-'. $count + 1] = array('title' => t('NY Senate Homepage'), 'href' => '<front>', 'attributes' => array('id' => 'menu-senator-front-link'));

    // Render the menu as a standard 'links' menu.
    $vars['nyss_menu'] = theme('links', $primary_links);
  }
  else {
    // Render the default primary links using nice menu.
    $vars['nyss_menu'] = theme('nice_menu_primary_links');
  }
  // Build the Section Header variable based on arg() or node type for the page being viewed
  if ($vars['senator'] == FALSE && ($vars['node']->type == 'blog' || arg(0) == 'blog')) {
    $vars['section_header'] = 'The New York Senate Blog';
  }
  if ($vars['senator'] == TRUE && (arg(2) == 'blog' || $vars['node']->type == 'blog')) {
    $vars['section_header'] = $vars['senator']->title.'\'s Blog';
  }
  // Classes for body element. Allows advanced theming based on context
  // (home page, node of certain type, etc.)
  $body_classes = array($vars['body_classes']);
  if (!$vars['is_front']) {
    // Add unique classes for each page and website section
    $path = drupal_get_path_alias($_GET['q']);
    list($section, ) = explode('/', $path, 2);
    $body_classes[] = zen_id_safe('page-' . $path);
    $body_classes[] = zen_id_safe('section-' . $section);
    if (arg(0) == 'node' && is_numeric(arg(1))) {
      $body_classes[] = 'full-node';
    }
    if (arg(0) != 'node') {
      $body_classes[] = 'not-node';
    }
    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-add'; // Add 'section-node-add'
      }
      elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-' . arg(2); // Add 'section-node-edit' or 'section-node-delete'
      }
    }
  }
  if (theme_get_setting('zen_wireframes')) {
    $body_classes[] = 'with-wireframes'; // Optionally add the wireframes style.
  }
  
  if ($vars['senator'] == TRUE) {
    $body_classes[] = 'senator'; // Class for a senator
  }
  if ($vars['senator'] == FALSE) {
    $body_classes[] = 'not-senator'; // Class for a non-senator
  }
  if ($vars['senator'] == TRUE && arg(2) == 'blog') {
    $body_classes[] = 'senator_blog'; // Class for a senator's blog
  }
  $vars['body_classes'] = implode(' ', $body_classes); // Concatenate with spaces
  if (!empty($vars['left_forms'])) {
    $vars['body_classes'] = str_replace('no-sidebars', 'one-sidebar sidebar-left', $vars['body_classes']);
  }
}
// */

/**
 * Override or insert variables into the node templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */

function nys_preprocess_node(&$vars, $hook) {
  $vars['senator'] = nyss_senator_node($vars['node']);
  if ($vars['senator']->field_senators_district[0]['nid']) {
    $vars['district'] = node_load($vars['senator']->field_senators_district[0]['nid']);
  }
  if (module_exists('service_links')) {
    $vars['service_links'] = theme('links', service_links_render($vars['node'], TRUE));
  }
  $vars['terms'] = nys_get_comma_tax_list($vars);
}

function nys_get_comma_tax_list($vars) {
  if (arg(0) == 'committee') {
    $schema = 'committee/'. check_plain(arg(1)) .'/issues/';
  }
  else {
    if (!empty($vars['senator'])) {
      $schema = 'senator/'. nyss_senator_title_to_url($vars['senator']) .'/issues/';
    }
    else {
      $schema = FALSE;
    }
  }

  if (empty($vars['node']->taxonomy))return;
  foreach ($vars['node']->taxonomy as $taxonomy) {
    if ($schema) {
      $terms[$taxonomy->vid][$taxonomy->tid] = l($taxonomy->name, $schema . strtolower(str_replace(' ', '_', check_plain($taxonomy->name))));
    }
    else {
      $terms[$taxonomy->vid][$taxonomy->tid] = l($taxonomy->name, 'taxonomy/term/' . $taxonomy->tid);
    }
  }
  $tax_terms_output = '<ul>';
  foreach ($terms as $vid => $terms) {
    $vocabulary = taxonomy_vocabulary_load($vid);
    $vocab_name = check_plain($vocabulary->name);
    $tax_terms_output .= '<li class="'. strtolower(str_replace(' ', '_', $vocab_name)) .'">';
    $tax_terms_output .= '<label>'. $vocab_name .'</label>';
    $tax_terms_output .= '<span class="term_list">'.implode(', ', $terms).'</span>';
    $tax_terms_output .= '</li>';
  }
  $tax_terms_output .= '</ul>';
  return $tax_terms_output;
}

/**
 * Override or insert variables into the comment templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
function nys_preprocess_comment(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the block templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
/* -- Delete this line if you want to use this function
function nys_preprocess_block(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

function nys_preprocess_search_result(&$variables) {
  $result = $variables['result'];
  $variables['url'] = check_url($result['link']);
  $variables['title'] = check_plain($result['title']);
  $variables['node'] = $result['node'];
  $info = array();
  if (!empty($result['type'])) {
    $info['type'] = check_plain($result['type']);
  }
  if (!empty($result['user'])) {
    $info['user'] = $result['user'];
  }
  if (!empty($result['date'])) {
    $info['date'] = format_date($result['date'], 'small');
  }
  if (isset($result['extra']) && is_array($result['extra'])) {
    $info = array_merge($info, $result['extra']);
  }
  // Check for existence. User search does not include snippets.
  $variables['snippet'] = isset($result['snippet']) ? $result['snippet'] : '';
  // Provide separated and grouped meta information..
  $variables['info_split'] = $info;
  $variables['info'] = implode(' - ', $info);
  // Provide alternate search result template.
  $variables['template_files'][] = 'search-result-'. $variables['type'];
}


function nys_node_submitted($node, $senator = FALSE) {
  if (!$senator) {
    $senator = nyss_senator($node);
  }
  else {
    $senator = nyss_senator($senator);
  }
  if ($senator->nid && $node->field_authored_by_senator[0]['value']) {
    $username = l($senator->title, 'node/'. $senator->nid);
  }
  else {
    $username = $node->name;
  }
  return t('Posted by !username on @datetime',
    array(
      '!username' => $username,
      '@datetime' => format_date($node->created, 'custom', 'l, F jS, Y'),
    ));
}

/**
 * Function for custom user login form.
 *
 **/

function nys_user_bar() {
  global $user;
  $output = '';

  if (!$user->uid) {
    $output .= "<div class='login'>" .(l(t('Log In'), 'user', array('title' => t('Log In'))) ."</div>" ."<div class='or'> or </div>" ."<div class='register'>" .l(t('Register'), 'user/register')) ."</div>";
  }
  else {
    $output .= "<div class='myaccount'>" .l(t('My account'), 'user/'.$user->uid, array('title' => t('Edit your account'))) ."</div>" ."<div class='logout'>" .(l(t('Log Out'), 'logout')) ."</div>";
  }

  $output = '<div id="user-bar">'.$output.'</div>';

  return $output;
}

/**
 * Function for Social Networking buttons, for Senators/Majority Leader
 *
 **/
function nys_social_buttons() {
  $output = '<div id="social_buttons"><a class="facebook" href=""></a><a class="twitter" href=""></a></div>';
  return $output;
}

/**
  * Theme override for search form.
  */
function nys_search_theme_form($form) {
  // Set a default value in the search box, you can change 'search' to whatever you want - you can change/delete this
  $form['search_theme_form']['#value'] = 'Search';
  // Additionally, hide the text when editing - you can change/delete this
  // Remember to change the value 'search' here too if you change it in the previous line
  $form['search_theme_form']['#attributes'] = array('onblur' => "if (this.value == '') {this.value = 'Search';}", 'onfocus' => "if (this.value == 'Search') {this.value = '';}" );
  // Don't change this
  $output .= drupal_render($form);
  return $output;
}

/**
 * Function for Share Links
 *
 **/
function nys_share_links() {
  global $base_path;
  $output = '';
  $output .= '<h3>Share This</h3>';
  $output .= '<ul>';
  $output .= '<li class="share_digg"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/digg.png"/></a></li>';
  $output .= '<li class="share_facebook"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/facebook.png"/></a></li>';
  $output .= '<li class="share_delicious"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/delicious.png"/></a></li>';
  $output .= '<li class="share_twitter"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/twitter.png"/></a></li>';
  $output .= '<li class="share_stumbleupon"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/stumbleupon.png"/></a></li>';
  $output .= '<li class="share_feedburner"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/feedburner.png"/></a></li>';
  $output .= '<li class="share_wordpress"><a href="#"><img src="'.$base_path.path_to_theme().'/images/share_icons/wordpress.png"/></a></li>';
  $output .= '</ul>';
  return $output;
}


function nys_service_links_build_link($text, $url, $title, $image, $nodelink) {
  global $base_path;

  if ($nodelink) {
    switch (variable_get('service_links_style', 1)) {
      case 1:
        $link = array(
          'title' => $text,
          'href' => $url,
          'attributes' => array('title' => $title, 'rel' => 'nofollow')
        );
        break;
      case 2:
        $link = array(
          'title' => '<img src="'. $base_path . path_to_theme() .'/'. $image .'" alt="'. $text .'" />',
          'href' => $url,
          'attributes' => array('title' => $title, 'rel' => 'nofollow'),
          'html' => TRUE
        );
        break;
      case 3:
        $link = array(
          'title' => '<img src="'. $base_path . path_to_theme() .'/'. $image .'" alt="'. $text .'" /> '. $text,
          'href' => $url,
          'attributes' => array('title' => $title, 'rel' => 'nofollow'),
          'html' => TRUE
        );
        break;
    }
  }
  else {
    switch (variable_get('service_links_style', 1)) {
      case 1:
        $link = '<a href="'. check_url($url) .'" title="'. $title .'" rel="nofollow">'. $text .'</a>';
        break;
      case 2:
        $link = '<a href="'. check_url($url) .'" title="'. $title .'" rel="nofollow"><img src="'. $base_path . path_to_theme() .'/'. $image .'" alt="'. $text .'" /></a>';
        break;
      case 3:
        $link = '<a href="'. check_url($url) .'" title="'. $title .'" rel="nofollow"><img src="'. $base_path . path_to_theme() .'/'. $image .'" alt="'. $text .'" /> '. $text .'</a>';
        break;
    }
  }

  return $link;
}

function nys_service_links_node_format($links) {
  return '<div class="service-links">'. theme('links', $links) .'</div>';
}

function nys_links($links, $attributes = array('class'=>'links')) {
  unset($links['node_read_more']);
  unset($links['blog_usernames_blog']);
  return theme_links($links, $attributes);  
}

function nys_comment_submitted($comment) {
  return t('by !username',
    array(
      '!username' => $comment->name,
    ));
}

function nys_date_all_day($which, $date1, $date2, $format, $node, $view = NULL) {
  if (empty($date1) || !is_object($date1)) {
    return '';
  }
  if (empty($date2)) {
    $date2 = $date1;
  }
  $granularity = array_pop(date_format_order($format));
  switch ($granularity) {
    case 'second':
      $max_comp = date_format($date2, 'H:i:s') == '23:59:59';
      break;
    case 'minute':
      $max_comp = date_format($date2, 'H:i') == '23:59';
      break;
    case 'hour':
      $max_comp = date_format($date2, 'H') == '23';
      break;
    default:
      $max_comp = FALSE;
  }
  // Time runs from midnight to the maximum time -- call it 'All day'.
  if (date_format($date1, 'H:i:s') == '00:00:00' && $max_comp) {
    $format = date_limit_format($format, array('year', 'month', 'day'));
    return trim(date_format_date($$which, 'custom', $format) .' '. theme('date_all_day_label'));
  }
  // There is no time, use neither 'All day' nor time.
  elseif (date_format($date1, 'H:i:s') == '00:00:00' && date_format($date2, 'H:i:s') == '00:00:00') {
    $format = date_limit_format($format, array('year', 'month', 'day'));
    return date_format_date($$which, 'custom', $format);
  }
  // Normal formatting - OVERRIDE TO ADD PERIOD.
  else {
    return date_format_date($$which, 'custom', 'M. d');
  }
}

/**
 * Returns the "Something to say" 'block'.
 */
function nys_get_something_to_say() {
  global $user;
  $output = '';
  $output .= '<div id="something_to_say">';
  $output .= '<ul>';
  $output .= '<li>';
  $output .= ($user->uid > 0) ? l('Blog about an issue you care about.', 'node/add/story') : l('Blog about an issue you care about.', 'user', array('query' => array('destination' => 'node/add/story')));
  $output .= '</li>';
  $output .= '<li>';
  $output .= ($user->uid > 0) ? l('Tell us a story about your life.', 'node/add/story') : l('Tell us a story about your life.', 'user', array('query' => array('destination' => 'node/add/story')));
  $output .= '</li>';
  $output .= '<li class="last">' . l('Have a suggestion? Let us know!', 'contact') . '</li>';
  $output .= '</ul>';
  $output .= '</div>';
  return $output;
}

function nys_emvideo_thickbox($field, $item, $formatter, $node, $options = array()) {
  $title = isset($options['title']) ? $options['title'] : (isset($node->title) ? $node->title : (isset($node->node_title) ? $node->node_title : (isset($field['widget']['thumbnail_link_title']) ? $field['widget']['thumbnail_link_title'] : variable_get('emvideo_default_thumbnail_link_title', t('See video')))));

  $thumbnail = theme('emvideo_video_thumbnail', $field, $item, 'video_thumbnail', $node, TRUE, $options);
  $destination = 'emvideo/thickbox/'. $node->nid .'/'. $field['widget']['video_width'] .'/'. $field['widget']['video_height'] .'/'. $field['field_name'] .'/'. $item['provider'] .'/'. $item['value'];
  $options = array(
    'attributes' => array(
      'title' => $title,
      'class' => 'thickbox',
      'rel' => module_exists('lightbox2') ? 'lightframe['. $field['type_name'] .'|width:'. ($field['widget']['video_width'] + 30) .'; height:'. ($field['widget']['video_height'] + 35) .';]' : $field['type_name'],
    ),
    'query' => NULL,
    'fragment' => NULL,
    'absolute' => FALSE,
    'html' => TRUE,
  );

  if (function_exists('lightbox2_add_files')) {
    lightbox2_add_files();
  }
  $output = l($thumbnail, $destination, $options);

  return $output;
}

// THEME THE ICAL CALENDAR ICON
function nys_calendar_ical_icon($url) {
  if ($url[0] == '/') { $url = substr($url, 1); }
  return '<div class="calendar-icon">' . l('Add to Your Calendar', $url, array('attributes'=>array('class'=>'ical-icon', 'title'=>t('Add to Your Calendar')))) . '</div>';
}

function nys_preprocess_node_rss(&$variables) {
  print_r($variables);
}

// MAKE CCK FILE FIELDS OPEN IN NEW WINDOW
function nys_filefield_file($file) {
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file['fid'])) {
    return '';
  }

  $path = $file['filepath'];
  $url = file_create_url($path);
  $icon = theme('filefield_icon', $file);

  // Set options as per anchor foaarmat described at
  // http://microformats.org/wiki/file-format-examples
  // TODO: Possibly move to until I move to the more complex format described 
  // at http://darrelopry.com/story/microformats-and-media-rfc-if-you-js-or-css
  $options = array(
    'attributes' => array(
      'type' => $file['filemime'],
      'length' => $file['filesize'],
      'target' => '_blank',
    ),
  );

  // Use the description as the link text if available.
  if (empty($file['data']['description'])) {
    $link_text = $file['filename'];
  }
  else {
    $link_text = $file['data']['description'];
    $options['attributes']['title'] = $file['filename'];
  }

  return '<div class="filefield-file clear-block">'. $icon . l($link_text, $url, $options) .'</div>';
}

// BOOK PREPROCESS VARIABLES
function nys_preprocess_book_navigation(&$variables) {
  $node = node_load($variables['book_link']['nid']);
  $variables['display'] = TRUE;
  if (strlen($node->body) >= 3000 || $variables['book_link']['nid'] == $variables['book_link']['bid']) {
    $book_link = $variables['book_link'];
    $tree = menu_tree_all_data(book_menu_name($book_link['bid']));
    $variables['tree'] = '<div class="book-navigation-tree">'. menu_tree_output($tree) . '</div>';
  }
  else {
    $variables['display'] = FALSE;
  }
}

function nys_menu_item_link($link) {
  if (empty($link['localized_options'])) {
    $link['localized_options'] = array();
  }
  
  $extra = '';
  $span = '<span class="';
  $div = '<div class="';

  if ($link['type'] & MENU_IS_LOCAL_TASK) {
    $link['title'] = '<span class="tab">' . check_plain($link['title']) . '</span>';
    $link['localized_options']['html'] = TRUE;
  }
  if ($link['module'] == 'book') {
    $explode = explode('/', $link['link_path']);
    $nid = $explode[1];
    $result = db_query('SELECT COUNT(c.cid) AS comment_count, n.comment FROM {comments} AS c LEFT JOIN {node} AS n on n.nid = c.nid WHERE c.nid = %d AND c.status = 0 GROUP BY c.nid', $nid);
    while($row = db_fetch_object($result)) {
      if ($row->comment == NULL || $row->comment = 0) {
        $extra = 'disabled';
        break;
      }
      else {
        $extra = $row->comment_count;
      }
    }
    //global $user;
    //if ($user->uid == 37) { print $extra .'<br />'; }
    if ($extra != 'disabled' && $extra != '') {
      if ($extra == 0) { $span .= 'no-comments '; } else { $span .= 'yes-comments '; }
      $extra = format_plural($extra, '(1&nbsp;comment)', '(@count&nbsp;comments)');
      
      $extra = l($extra, $link['href'], array('fragment' => 'comments', 'html' => 'true'));
    }
    else {
      unset($extra);
    }
	if ((arg(0) == 'node') && (is_numeric(arg(1))) && (arg(2) != 'edit')) {
      if (arg(1) == $explode[1]) {
        $div .= 'book-active-chapter ';
      }
    }
  }
  
  $span .= '">';
  $div .= '">';

  if (arg(1) == $explode[1] && $link['module'] == 'book') {
    return $div . t($link['title']) . ' ' . $span . $extra .'</span></div>';
  }
  else {
		return $div . l($link['title'], $link['href'], $link['localized_options']) . ' ' . $span . $extra .'</span></div>';
  }
}

/**
 * This will return a provided thumbnail image for a video.
 *
 * @param $field
 *   This is the field providing settings for the video thumbnail.
 * @param $item
 *   This is the data returned by the field. It requires at the least to be an array with 'value' and 'provider'.
 *   $item['value'] will be the video code, and $item['provider'] will be the provider, such as youtube.
 * @param $formatter
 *   This is the formatter for the view. This will nearly always be video_thumbnail.
 * @param $node
 *   This is the node object containing the field.
 * @param $no_link
 *   Optional. If FALSE, then we provide a link to the node.
 *   (In retrospect, this should have been $link, defaulting to TRUE.
 *   TODO: fix? problem though is that this goes deeper up the tree.)
 * @param $options
 *   Optional array. This is to pass optional overrides. currently:
 *     $options['width'] and $options['height'], if provided, will override any field settings for the thumbnail w/h.
 *     $options['link_url'], if provided, will cause the thumbnail link to go to another URL other than node/nid. $no_link must be FALSE.
 *     $options['title'], if provided, will set the title of the link and image.
 *     $options['link_title'], if provided, will set the title of the link when no image is provided. otherwise, it defaults to 'See video'.
 *     $options['image_title'], if provided, will set the title attribute of the href link, defaulting to $options['link_title'].
 *     $options['image_alt'], if provided, will set the alt attribute of the href link, defaulting to $options['link_title'].
 *     $options['thumbnail_url'], if provided, will completely override the thumbnail image entirely.
 *     $options['attributes'], if provided, sets the attributes for the displayed image.
 * @return
 *   The thumbnail output.
 */
function nys_emvideo_video_thumbnail($field, $item, $formatter, $node, $no_link = FALSE, $options = array()) {
  // Thickbox requires some output, so make sure we have at least a blank string.
  $output = '';
  
  if ((arg(0) == 'senator' && (arg(2) == 'video' || arg(2) == 'gallery')) || arg(0) == 'media' || arg(0) == 'video') { 
    $width = 120;
    $height = 90;
  } else {
    $width = isset($options['width']) ? $options['width'] : ($field['widget']['thumbnail_width'] ? $field['widget']['thumbnail_width'] : variable_get('emvideo_default_video_width', EMVIDEO_DEFAULT_THUMBNAIL_WIDTH));
    $height = isset($options['height']) ? $options['height'] : ($field['widget']['thumbnail_height'] ? $field['widget']['thumbnail_height'] : variable_get('emvideo_default_video_height', EMVIDEO_DEFAULT_THUMBNAIL_HEIGHT));
  }
  // Get a thumbnail URL. This can be an override through $options['thumbnail_url'],
  // defined by the provider (the usual case), or a default image.
  if (isset($options['thumbnail_url']) || ($item['value'] && $item['provider'])) {
    // If we've set $options['thumbnail_url'], then we'll just use that.
    $thumbnail_url = isset($options['thumbnail_url']) ? $options['thumbnail_url'] : '';

    // Otherwise, if we have emthumb installed, then give it a chance to override our thumbnail.
    if (empty($thumbnail_url) && function_exists('emthumb_thumbnail_url')) {
      $thumbnail_url = emthumb_thumbnail_url($item);
    }

    // If we don't have a custom thumbnail, then see if the provider gives us a thumbnail.
    if (empty($thumbnail_url)) {
      $thumbnail_url = emfield_include_invoke('emvideo', $item['provider'], 'thumbnail', $field, $item, $formatter, $node, $width, $height, $options);
    }
  }

  // If we still don't have a thumbnail, then apply a default thumbnail, if it exists.
  if (empty($thumbnail_url)) {
    $default_thumbnail_url = $field['widget']['thumbnail_default_path'] ? $field['widget']['thumbnail_default_path'] : variable_get('emvideo_default_thumbnail_path', NULL);
    if ($default_thumbnail_url) {
      $thumbnail_url = base_path() . $default_thumbnail_url;
    }
  }

  // Define the thumbnail link's path.
  $link_url = isset($options['link_url']) ? $options['link_url'] : 'node/'. $node->nid;

  // Define the title/alt to display for the link hover.
  $link_title = isset($options['link_title']) ? $options['link_title'] : (isset($options['title']) ? $options['title'] : (isset($field['widget']['thumbnail_link_title']) ? $field['widget']['thumbnail_link_title'] : variable_get('emvideo_default_thumbnail_link_title', t('See video'))));
  if (module_exists('token')) {
    // Allow the editor to use [title] tokens.
    $link_title = token_replace($link_title, 'global', $node);
  }
  $image_title = isset($options['image_title']) ? $options['image_title'] : $link_title;
  $image_alt = isset($options['image_alt']) ? $options['image_alt'] : $link_title;

  if ($thumbnail_url) {
    //$width = isset($options['width']) ? $options['width'] : NULL;
    $width = isset($width) ? $width : ($field['widget']['thumbnail_width'] ? $field['widget']['thumbnail_width'] : variable_get('emvideo_default_thumbnail_width', EMVIDEO_DEFAULT_THUMBNAIL_WIDTH));
    //$height = isset($options['height']) ? $options['height'] : NULL;
    $height = isset($height) ? $height : ($field['widget']['thumbnail_height'] ? $field['widget']['thumbnail_height'] : variable_get('emvideo_default_thumbnail_height', EMVIDEO_DEFAULT_THUMBNAIL_HEIGHT));
    $attributes = isset($options['attributes']) ? $options['attributes'] : array();
    $attributes['width'] = isset($attributes['width']) ? $attributes['width'] : $width;
    $attributes['height'] = isset($attributes['height']) ? $attributes['height'] : $height;
    $image = theme('image', $thumbnail_url, $image_alt, $image_title, $attributes, FALSE);
    if ($no_link) {
      // Thickbox requires the thumbnail returned without the link.
      $output = $image;
    }
    else {
      $output = l($image, $link_url, array('html'=> TRUE));
    }
  }
  else {
    // If all else fails, then just print a 'see video' type link.
    if (!$no_link) {
      $output = l($link_title, $link_url);
    }
  }

  return $output;
}
