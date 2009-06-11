<?php

function nyss_senator_search_search($address_string = '') {
  $zip = substr($address_string, -5);
  if (is_numeric($zip) == TRUE) {
    if (substr($zip, 0, 2) == '11' && $zip[2] != '2') {
      drupal_set_message('Residents of Queens: Addresses that contain hyphens (ie 12-34 Main St.) may occasionally produce inaccurate search results.  If you live in Queens, please use the ' . l('New York Board of Election look up tool', 'http://nymap.elections.state.ny.us/nysboe/'). ' to verify your Senator. We apologize for any inconvenience.');
    }      
  } 
  
  $xml = nyss_senator_search_cd_lookup($address_string);

  if ($xml) {
    foreach($xml->districts->children() as $district) {
      switch($district->attributes()->type) {
        case 'congress':
          $cd = $district;
          break;
        case 'assembly_upper':
          $cd_upper = $district;
          break;
        case 'assembly_lower':
          $cd_lower = $district;
          break;
      }
    }
  }

  $items = array('Federal Congress: '. $cd, 'NYS Senate: '. $cd_upper, 'NYS Assembly: '. $cd_lower);
  if ($cd) {
    $senator_nid = db_result(db_query(db_rewrite_sql("SELECT s.nid FROM {content_type_senator} s JOIN {content_type_district} d ON s.field_senators_district_nid = d.nid JOIN {node} n ON s.vid = n.vid WHERE n.status = 1 AND d.field_district_number_value = %d"), $cd_upper));
    $senator = node_load($senator_nid);
    
    $senator->guest_address = $address_string;

    $output .= '<div style="float: left; width: 215px; padding: 0 10px 30px 0;" class="senator-search-left">';
    $output .= '<h3>Your Senator</h3>';
    $output .= '<div style="float: left; padding-right: 10px;"><a class="picture" href="'. url('node/'. $senator->nid) .'"><img src="' . base_path() . file_directory_path() . '/imagecache/senator_teaser/profile-pictures/' . $senator->field_profile_picture[0]['filename'] . '" alt="' . $senator->title . ' photo" /></a></div>';
    $output .= '<div style="float: left; clear: right;"><a href="'. url('node/'. $senator->nid) .'">Sen. ' . $senator->title . '</a><br />';
    $output .= substr($senator->field_party_affiliation[0]['value'], 0, 1) . '-District ' . $cd_upper;
    $output .= '</div>';
    //$output .= '<br />'.spamspan($senator->field_email[0]['email']);
    
    $output .= '<div style="clear: both;">';
    $output .= '<p>'. $senator->field_contact_information[0]['value'] .'</p>';

    $output .= theme('item_list', $items, t('Your Districts'));
    $output .= '</div></div>';

    $output .= '<div style="float: left; width: 300px; padding: 0 0 30px 0;" class="senator-search-right">';
    $output .= '<h3>Contact Your Senator</h3>';
    $output .= drupal_get_form('nyss_contact_mail_senator', $senator);
    $output .= '</div>';    
    
    $output .= '<div style="clear: both; border-top: solid 1px #E2DED5; padding: 20px 0 0 0;"><p>Not your district? Try: </p></div>';
  }
  else {
    $output .= '<p>Your district could not be located. Try: </p>';
  }
  $output .= '<ul>';
  $output .= '<li>'. l('Viewing the district map', 'districts/map') .'</li>';
  $output .= '<li>'. l('Picking from a list of all Senators', 'senators') .'</li>';
  $output .= '<li>'. l('Contacting the NY State Senate technology team for help', 'contact') .'</li>';
  $output .= '<li>Searching again in the top-left corner of this screen.</li>';
  $output .= '</ul>';
  
  $output .= '<p style="padding-top: 1em;"><em>Residents of Queens:</em> Addresses that contain hyphens (ie 12-34 Main St.) may occasionally produce inaccurate search results.  If you live in Queens, please use the ' . l('New York Board of Election look up tool', 'http://nymap.elections.state.ny.us/nysboe/'). ' to verify your Senator. We apologize for any inconvenience.</p>'; 
  
  return $output;
}

function nyss_senator_search_cd_lookup($address) {
  $url = "https://api.advomatic.com/polipoly/?address=". urlencode($address) ."&gmapapi=". variable_get('googlemap_api_key', '') ."&state=true";

  $ch = curl_init($url);
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  $html = curl_exec($ch);
  curl_close($ch);

  if (strpos($html, '<state>NY</state>') !== FALSE) {
    return simplexml_load_string($html);
  }
  return FALSE;
}
