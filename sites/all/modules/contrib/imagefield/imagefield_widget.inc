<?php
// $Id: imagefield_widget.inc,v 1.34 2009/03/28 03:10:11 quicksketch Exp $

/**
 * @file
 * ImageField widget hooks and callbacks.
 *
 * This file is loaded by fileifeld.module and the callbacks it contains are
 * invoked by filefield.module. This happens because imagefield delegates it's
 * CCK hooks and callbacks to filefield in imagefield.module.
 */

/**
 * @defgroup "FileField widget settings callbacks"
 * @{
 *
 * These callbacks are invoked by filefield_widget_settings. Their
 * return values are merged with and will override filefields' widget
 * settings callback's return values.
 */
function imagefield_widget_settings_form($widget) {
  $form = module_invoke('filefield', 'widget_settings', 'form', $widget);

  $form['max_resolution'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum resolution for Images'),
    '#default_value' => !empty($widget['max_resolution']) ? $widget['max_resolution'] : 0,
    '#size' => 15,
    '#maxlength' => 10,
    '#description' => t('The maximum allowed image size expressed as WIDTHxHEIGHT (e.g. 640x480). Set to 0 for no restriction. If a larger image is uploaded, it will be resized to reflect the given width and height. Resizing images on upload will cause the loss of <a href="http://en.wikipedia.org/wiki/Exchangeable_image_file_format">EXIF data</a> in the image.'),
    '#weight' => 2,
  );
  $form['min_resolution'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum resolution for Images'),
    '#default_value' => !empty($widget['min_resolution']) ? $widget['min_resolution'] : 0,
    '#size' => 15,
    '#maxlength' => 10,
    '#description' =>
    t('The minimum allowed image size expressed as WIDTHxHEIGHT (e.g. 640x480). Set to 0 for no restriction. If an image that is smaller than these dimensions is uploaded it will be rejected.'),
    '#weight' => 2,
  );

  $form['file_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Permitted upload file extensions'),
    '#default_value' => !empty($widget['file_extensions']) ? $widget['file_extensions'] : 'jpg jpeg png gif',
    '#size' => 64,
    '#maxlength' => 64,
    '#description' => t('Extensions a user can upload to this field. Separate extensions with a space and do not include the leading dot. Only jpg, png, and gif images are supported with this widget.'),
    '#weight' => 2,
  );

  $form['alt_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('ALT text settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 8,
  );
  $form['alt_settings']['custom_alt'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable custom alternate text'),
    '#default_value' =>  !empty($widget['custom_alt']) ? $widget['custom_alt'] : 0,
    '#description' => t('Enable user input alternate text for images.'),
  );
  $form['alt_settings']['alt'] = array(
    '#type' => 'textfield',
    '#title' => t('Default ALT text'),
    '#default_value' => !empty($widget['alt']) ? $widget['alt'] : '',
    '#description' => t('This value will be used for alternate text by default.'),
    '#suffix' => theme('token_help', 'file'),
  );

  $form['title_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Title text settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 8,
  );
  $form['title_settings']['custom_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable custom title text'),
    '#default_value' =>  !empty($widget['custom_title']) ? $widget['custom_title'] : 0,
    '#description' => t('Enable user input title text for images.'),
  );
  $form['title_settings']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Title text'),
    '#default_value' => !empty($widget['title']) ? $widget['title'] : '',
    '#description' => t('This value will be used as the image title by default.'),
    '#suffix' =>  theme('token_help', 'file'),
  );

  // Default image settings.
  $form['default'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default image'),
    '#element_validate' => array('_imagefield_widget_settings_default_validate'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 10
  );

  // Present a thumbnail of the current default image.
  $form['default']['use_default_image'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use default image'),
    '#default_value' =>  $widget['use_default_image'],
    '#description' => t('When an image is not uploaded, show a default image on display.'),
  );

  if (!empty($widget['default_image'])) {
    $form['default']['default_image_thumbnail'] = array(
      '#type' => 'markup',
      '#value' => theme('imagefield_image', $widget['default_image'], '', '', array('width' => '150'), FALSE),
    );
  }
  $form['default']['default_image_upload'] = array(
    '#type'  => 'file',
    '#title' => t('Upload image'),
    '#description' => t('Choose a image that will be used as default.'),
  );

  // We set this value on 'validate' so we can get CCK to add it
  // as a standard field setting.
  $form['default_image'] = array(
    '#type' => 'value',
    '#value' => $widget['default_image'],
  );

  return $form;
}

/**
 * Element specific validation for imagefield default value.
 *
 * Validated in a separate function from imagefield_field() to get access
 * to the $form_state variable.
 */
function _imagefield_widget_settings_default_validate($element, &$form_state) {
  // Verify the destination exists
  $destination = file_directory_path() .'/imagefield_default_images';
  if (!field_file_check_directory($destination, FILE_CREATE_DIRECTORY)) {
    form_set_error('default_image', t('The default image could not be uploaded. The destination %destination does not exist or is not writable by the server.', array('%destination' => dirname($destination))));
    return;
  }

  $validators = array(
    'file_validate_is_image' => array(),
  );

  // We save the upload here because we can't know the correct path until the file is saved.
  if (!$file = file_save_upload('default_image_upload', $validators, $destination)) {
    // No upload to save we hope... or file_save_upload() reported an error on its own.
    return;
  }

  // Remove old image (if any) & clean up database.
  $old_default = $form_state['values']['default_image'];
  if (!empty($old_default['fid'])) {
    if (file_delete(file_create_path($old_default['filepath']))) {
      db_query('DELETE FROM {files} WHERE fid=%d', $old_default['fid']);
    }
  }

  // Make the file permanent and store it in the form.
  file_set_status($file, FILE_STATUS_PERMANENT);
  $form_state['values']['default_image'] = (array)$file;
 }

/**
 * Validate callback for the CCK widget form.
 */
function imagefield_widget_settings_validate($widget) {
  // Check that only web images are specified in the callback.
  $extensions = array_filter(explode(' ', $widget['file_extensions']));
  $web_extensions = array('jpg', 'jpeg', 'gif', 'png');
  if (count(array_diff($extensions, $web_extensions))) {
    form_set_error('file_extensions', t('Only web-standard images (jpg, gif, and png) are supported through the image widget. If needing to upload other types of images, change the widget to use a standard file upload.'));
  }

  // Check that set resolutions are valid.
  foreach (array('min_resolution', 'max_resolution') as $resolution) {
    if (!empty($widget[$resolution]) && !preg_match('/^[0-9]+x[0-9]+$/', $widget[$resolution])) {
      form_set_error($resolution, t('Please specify a resolution in the format WIDTHxHEIGHT (e.g. 640x480).'));
    }
  }
}

/**
 * Save callback for the CCK widget form.
 */
function imagefield_widget_settings_save($widget) {
  // TODO: Rename custom_alt and custom_title to alt_custom and title_custom.
  $filefield_settings = module_invoke('filefield', 'widget_settings', 'save', $widget);
  return array_merge($filefield_settings, array('max_resolution', 'min_resolution', 'alt',  'custom_alt', 'title', 'custom_title', 'default_image', 'use_default_image'));
}

/**
 * Element #value_callback function.
 */
function imagefield_widget_value($element, $edit = FALSE) {
  $item = filefield_widget_value($element, $edit);
  if ($edit) {
    $item['alt'] = isset($edit['alt']) ? $edit['alt'] : '';
    $item['title'] = isset($edit['title']) ? $edit['title'] : '';
  }
  else {
    $item['alt'] = '';
    $item['title'] = '';
  }
  return $item;
}

/**
 * Element #process callback function.
 */
function imagefield_widget_process($element, $edit, &$form_state, $form) {
  $file = $element['#value'];
  $field = content_fields($element['#field_name'], $element['#type_name']);

  $element['#theme'] = 'imagefield_widget_item';

  if (isset($element['preview']) && $element['#value']['fid'] != 0) {
    $element['preview']['#value'] = theme('imagefield_widget_preview', $element['#value']);
  }

  // Check if using the default alt text and replace tokens.
  $default_alt = (!$field['widget']['custom_alt'] || ($file['status'] == 0 && empty($file['data']['alt'])));
  if ($default_alt && function_exists('token_replace')) {
    $field['widget']['alt'] = token_replace($field['widget']['alt'], 'user', $GLOBALS['user']);
  }
  $element['data']['alt'] = array(
    '#title' => t('Alternate Text'),
    '#type' => $field['widget']['custom_alt'] ? 'textfield' : 'value',
    '#default_value' => $default_alt ? $field['widget']['alt'] : $file['data']['alt'],
    '#description' => t('This text will be used by screen readers, search engines, or when the image cannot be loaded.'),
    '#maxlength' => variable_get('imagefield_alt_length', 80), // See http://www.gawds.org/show.php?contentid=28.
    '#attributes' => array('class' => 'imagefield-text'),
  );
  // #value must be hard-coded if #type = 'value'.
  if ($default_alt) {
    $element['data']['alt']['#value'] = $field['widget']['alt'];
  }

  // Check if using the default title and replace tokens.
  $default_title = (!$field['widget']['custom_title'] || ($file['status'] == 0 && empty($file['data']['title'])));
  if ($default_title && function_exists('token_replace')) {
    $field['widget']['title'] = token_replace($field['widget']['title'], 'user', $GLOBALS['user']);
  }
  $element['data']['title'] = array(
    '#type' => $field['widget']['custom_title'] ? 'textfield' : 'value',
    '#title' => t('Title'),
    '#default_value' => $default_title ? $field['widget']['title'] : $file['data']['title'],
    '#description' => t('The title is used as a tool tip when the user hovers the mouse over the image.'),
    '#maxlength' => variable_get('imagefield_title_length', 500),
    '#attributes' => array('class' => 'imagefield-text'),
  );
  // #value must be hard-coded if #type = 'value'.
  if ($default_title) {
    $element['data']['title']['#value'] = $field['widget']['title'];
  }

  return $element;
}

/**
 * FormAPI theme function. Theme the output of an image field.
 */
function theme_imagefield_widget(&$element) {
  drupal_add_css(drupal_get_path('module', 'imagefield') .'/imagefield.css');
  return theme('form_element', $element, $element['#children']);
}
