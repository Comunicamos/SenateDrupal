<?php

print $output;
$senator = node_load($row->nid);
print '<div class="social_buttons">' . theme('nyss_blocks_view_content_social_buttons', $senator) . '</div>';
