<?php

print $output;
$senurl = trim(preg_replace('#[^\p{L}\p{N}]+#u', ' ', $row->node_title));
$senurl = str_replace(' ', '-', strtolower($senurl));

print '<span class="contact"> | '. l('Contact', 'senator/'. $senurl . '/contact').'</span>';

?>
