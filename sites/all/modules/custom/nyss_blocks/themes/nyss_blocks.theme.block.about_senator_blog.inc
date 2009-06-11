<?php
// $Id$

/**
 *  @file
 *  Theme functions for the 'About this blog' block for Senators' Blogs.
 */

/**
 *  Subject of the 'About this blog' block.
 *  @return
 *    The subject of that block.
 */
function theme_nyss_blocks_view_subject_about_senator_blog() {
  $senator = nyss_senator();
  if ($senator) {
    return t('What my senator can do for me');
  }
  else {
    return t('About this blog');
  }
}

/**
 *  Display the content of the 'About this blog' block.
 *
 *  @TODO: we need to build the blog view and figure out the senator.
 *
 *  @param $node
 *    (optional) The senator's node.
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_about_senator_blog() {
  $senator = nyss_senator();

  if ($senator) {
    return <<<ABOUT
      <p>Your state senator works for the citizens of your
      district. Your senator talks with constituents about
      how <strong>proposed laws</strong> will affect their lives. Your
      senator can relay information on bill status, committee
      hearings, resolutions and floor activity.</p>

      <p><strong>Contact your senator</strong> if you have concerns about
      issues affecting your community.</p>
ABOUT;
  }
  else {
    return <<<ABOUT
      <p>This blog is maintained by the Senate Communications 
Department. Please direct all questions to <strong><a 
href="mailto:nyss.content@gmail.com">Emmy 
Suzuki 
Harris.</a></strong></p>
ABOUT;
  }
}
