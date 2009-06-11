<?php
// $Id: views-view-field.tpl.php,v 1.1 2008/05/16 22:22:32 merlinofchaos Exp $
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */

  // Create a suitable array for emfield. Make sure to unserialize data.
  $item = array(
    'embed' => $row->node_data_field_video_field_video_embed,
    'value' => $row->node_data_field_video_field_video_value,
    'provider' => $row->node_data_field_video_field_video_provider,
    'data' => unserialize($row->node_data_field_video_field_video_data),
  );
  $node = $row;

  // This will be wider than the default of 260px.
  $options = array(
    'width' => 265,
    'height' => 156,
    'autoplay' => FALSE,
  );
  $output = theme('emvideo_video_video', NULL, $item, '', $node, $options);
?>
<?php print $output; ?>
