<?php

if($_REQUEST['email'] != '' && $_REQUEST['email'] != 'NYCitizen@domain.com') {

require_once('bronto_api.inc');

// Get the list that the user is subscribing to, depending on context
$list = 'New York Senate Updates';

$bronto = new bronto_api('newyorksenate', 'newyorksenate', 'Agency4Building');

$emailaddr = $_REQUEST['email'];
//$emailexplode = explode('@', $emailaddr);
//$emailaddr = str_replace('.', '', $emailexplode[0]) . '@' . $emailexplode[1]; 

// Add the email to the mailing list
$response = $bronto->add_email_to_list($emailaddr, $list);
if (!$response) {
  print 'Error entered address: ' . $bronto->get_error_code() . "<br/>" . $bronto->get_error_message();
  return;
}

// Update the fields
$fields = array();
if ($_REQUEST['mobile'] != '' && $_REQUEST['mobile'] != '123-456-7890') {
  $fields['mobile'] = $_REQUEST['mobile'];
  $_SESSION['bronto_mobile'] = $_REQUEST['mobile'];
}
if (count($fields)) {
  $response = $bronto->update_fields($emailaddr, $fields);
  if (!$response) {
    print 'Error mobile: ' . $bronto->get_error_code() . "<br/>" . $bronto->get_error_message();
    return;
  }
}

// Send confirmation email
$body = strtr('Thank you for subscribing to <strong>YOUR</strong> New York State <strong>SENATE</strong> mailing list.

You will receive regular New York State Senate Updates. We hope you will stop by http://www.nysenate.gov often and participate in the conversation about YOUR New York State SENATE.

Thanks,
The !site Team', array('!site' => 'NY State Senate', '!lists' => $list, '!unsubscribe_link' => '%%!unsubscribe_url%%'));

//$body = t(variable_get('bronto_subscription_confirm_body', nyss_signup_confirm_body_default()), array('!site' => variable_get('site_name', ''), '!lists' => $list, '!unsubscribe_link' => '%%!unsubscribe_url%%'));

$response = $bronto->send_message(
  '',
  'webmaster@senate.state.ny.us',
  $emailaddr,
  strtr('Confirmation of subscription to !list mailing list', array('!list' => $list)),
  preg_replace('/\n/', '<br />', $body),
  'html',
  'contact'
);

if (!$response) {
    print 'Error sending email: ' . $bronto->get_error_code() . "<br/>" . $bronto->get_error_message();
    return;
  }
else {
  $info = '<p><strong>THANK YOU</strong></p><p>' . $_REQUEST['email'];
  if ($_REQUEST['mobile'] != '' && $_REQUEST['mobile'] != '123-456-7890') {
    $info .= ' and ' . $_REQUEST['mobile'] .' have';
  }
  else {
    $info .= ' has';
  }
  $info .= ' been added to<br />YOUR New York State SENATE contact list.</p><p>You will receive a confirmation email from<br />Your New York State Senate Team<br />shortly.</p>';
}

$_SESSION['bronto_email'] = $form_state['values']['email'];
$_SESSION['bronto_list'] = $list;

}

else { $info = '<p>Invalid request! Please ensure that you entered a valid email address.</p>'; } ?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en" dir="ltr">

<head>
  <title>Your New York State: Online May 7</title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <link type="text/css" rel="stylesheet" media="all" href="/splash/splash.css" /
</head>
<body class="body">

<div id="main-splash">

<div id="info" style="text-align: center;">
<?php print $info; ?>
<p><a href="../" style="text-decoration: underline;">Go back</a></p>
</div>

</div>

</body>
</html>
