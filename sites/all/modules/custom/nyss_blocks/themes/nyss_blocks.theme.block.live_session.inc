<?php
// $Id$

/**
 *  @file
 *  Theme functions for the nyss_blocks 'Live Session' block
 */

/**
 *  Subject of the 'Live Search' block.
 *
 *  @return
 *    The subject of this block.
 */
function theme_nyss_blocks_view_subject_live_session() {
  return 'Live Session';
}

/**
 *  Display the content of the 'Live Session' block.
 *
 *  @return
 *    The content of this block.
 */
function theme_nyss_blocks_view_content_live_session() {
  $output = '<script src="http://static.mogulus.com/scripts/playerv2.js?channel=nysenate&amp;layout=playerEmbedDefault&amp;backgroundColor=0xffffff&amp;backgroundAlpha=1&amp;backgroundGradientStrength=0&amp;chromeColor=0x000000&amp;headerBarGlossEnabled=true&amp;controlBarGlossEnabled=true&amp;chatInputGlossEnabled=false&amp;uiWhite=true&amp;uiAlpha=0.5&amp;uiSelectedAlpha=1&amp;dropShadowEnabled=true&amp;dropShadowHorizontalDistance=10&amp;dropShadowVerticalDistance=10&amp;paddingLeft=0&amp;paddingRight=0&amp;paddingTop=0&amp;paddingBottom=0&amp;cornerRadius=3&amp;backToDirectoryURL=null&amp;bannerURL=null&amp;bannerText=null&amp;bannerWidth=320&amp;bannerHeight=50&amp;showViewers=true&amp;embedEnabled=true&amp;chatEnabled=false&amp;onDemandEnabled=true&amp;programGuideEnabled=false&amp;fullScreenEnabled=true&amp;reportAbuseEnabled=false&amp;gridEnabled=false&amp;initialIsOn=false&amp;initialIsMute=false&amp;initialVolume=10&amp;contentId=null&amp;initThumbUrl=null&amp;playeraspectwidth=4&amp;playeraspectheight=3&amp;mogulusLogoEnabled=false&amp;width=270&amp;height=211&amp;wmode=window" type="text/javascript"></script>';
  $output .= '<p style="padding: 0; font-size: .8em;">';
  $output .= 'Watch in a <a href="">larger window.</a><br />';
  $output .= 'Having trouble? Try viewing with our <a href="http://senreal3.senate.state.ny.us/ramgen/sennet_tv.smil">RealPlayer Stream.</a><br />';
  $output .= '</p>';

  return $output;
}
