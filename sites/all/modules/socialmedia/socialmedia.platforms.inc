<?php

/**
 * @file
 * Defines social media platforms
 */

function socialmedia_socialmedia_platform_info() {
  $platforms = array();
  $platforms = array_merge($platforms, socialmedia_twitter_platform_info());
  $platforms = array_merge($platforms, socialmedia_facebook_platform_info());
  $platforms = array_merge($platforms, socialmedia_flickr_platform_info());
  $platforms = array_merge($platforms, socialmedia_googleplus_platform_info());
  $platforms = array_merge($platforms, socialmedia_instagram_platform_info());
  $platforms = array_merge($platforms, socialmedia_linkedin_platform_info());
  $platforms = array_merge($platforms, socialmedia_pinterest_platform_info());
  $platforms = array_merge($platforms, socialmedia_rss_platform_info());
  $platforms = array_merge($platforms, socialmedia_slideshare_platform_info());
  $platforms = array_merge($platforms, socialmedia_vimeo_platform_info());
  $platforms = array_merge($platforms, socialmedia_youtube_platform_info());
  
  $platforms = array_merge($platforms, socialmedia_addthis_platform_info());
 
  return $platforms;
}

function socialmedia_addthis_platform_info() {
  $platforms = array();
  $platforms['addthis'] = array(
    'title' => t('AddThis'),
    'description' => t('URL to your Facebook profile or page'),
    'group' => t('Widget platforms'),
    'homepage' => 'http://www.addthis.com',
    'form callback' => 'socialmedia_addthis_form',
    'parser callback' => 'socialmedia_addthis_parser',
    'tokens callback' => 'socialmedia_addthis_tokens',
  ); 
  $platforms['addthis']['form'] = array(
    'title' => t('Facebook profile'),
    'description' => t('URL to your Facebook profile'),
  );
  $platforms['addthis']['tokens']['multi'] = array(
    'addthis_pubid' => array(
      'name' => t("AddThis pubid"),
      'description' => t("AddThis pubid"),
    ),   
  );
  return $platforms;  
}

function socialmedia_addthis_form($profile) {
  $fields['input_addthis_pubid'] = array(
    '#type' => 'textfield',
    '#title' => t('AddThis pub id'),
    '#default_value' => (isset($profile['inputs']['pubid'])) ? $profile['inputs']['pubid'] : '',
    '#description' => t('This is the pubid used to tie AddThis widgets back to your AddThis account.'),
    '#size' => 80,
  );
  return $fields;
}

function socialmedia_addthis_parser($values, $scope = 'site') {
  $profile['pubid'] = $values['pubid'];
  return $profile;
}

function socialmedia_addthis_tokens($key, $profile) {
  switch ($key) {
    case 'pubid':
      return isset($profile['pubid']) ? $profile['pubid'] : '';
  }
  return '';
}

function socialmedia_facebook_platform_info() {
  $platforms = array();
  $platforms['facebook'] = array(
    'title' => t('Facebook'),
    'description' => t('URL to your Facebook profile or page'),
    'homepage' => 'http://www.facebook.com',
    'redirect path' => 'facebook',
    'parser callback' => 'socialmedia_facebook_parser',
    'tokens callback' => 'socialmedia_facebook_tokens',
  ); 
  $platforms['facebook']['form'] = array(
    'title' => t('Facebook profile'),
    'description' => t('URL to your Facebook profile'),
  );
  $platforms['facebook']['tokens']['multi'] = array(
    'facebook_url' => array(
      'name' => t("Facebook profile url"), 
      'description' => t("URL to Facebook profile."),
    ),
    'facebook_url-brief' => array(
      'name' => t("Facebook profile url (brief)"), 
      'description' => t("URL to Facebook profile without protocol."),
    ), 
    'facebook_username' => array(
      'name' => t("Facebook name"), 
      'description' => t("Facebook profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_facebook_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(facebook\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_facebook_url', t('Facebook URL invalid.'));
    }
    return FALSE;
  }
  $a = explode('facebook.com/', $str);
  $profile['url'] = 'www.facebook.com/' . $a[1];

  $b = explode('?', $a[1]);
  $c = explode('/', $b[0]);
  if (!isset($b[1]) && ($b[0] != 'profile.php')) {
    $profile['userid'] = $profile['username'] = $b[0];
  }
  elseif ($b[0] == 'pages') {
    $profile['userid'] = $profile['username'] = $b[1];
  }

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }

  form_set_error('input_facebook_username', t('Cannot derive username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_facebook_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}

function socialmedia_flickr_platform_info() {
  $platforms = array();
  $platforms['flickr'] = array(
    'title' => t('Flickr'),
    'description' => t('URL to your Flickr profile or page'),
    'homepage' => 'http://www.flickr.com',
    'redirect path' => 'flickr',
    'parser callback' => 'socialmedia_flickr_parser',
    'tokens callback' => 'socialmedia_flickr_tokens',
  ); 
  $platforms['flickr']['form'] = array(
    'title' => t('Flickr profile'),
    'description' => t('URL to your Flickr profile'),
  );
  $platforms['flickr']['tokens']['multi'] = array(
    'flickr_url' => array(
      'name' => t("Flickr profile url"), 
      'description' => t("URL to Flickr profile."),
    ),
    'flickr_url-brief' => array(
      'name' => t("Flickr profile url (brief)"), 
      'description' => t("URL to Flickr profile without protocol."),
    ), 
    'flickr_username' => array(
      'name' => t("Flickr name"), 
      'description' => t("Flickr profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_flickr_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'username' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(flickr\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_flickr_url', t('Flickr URL invalid.'));
    }
    return FALSE;
  }  
  $a = explode('www.flickr.com/', $str);
  $profile['url'] = 'www.flickr.com/' . $a[1];

  $b = explode('/', $a[1]);
  if (($b[0] == 'people') || ($b[0] == 'photos')) {
    $profile['userid'] = $profile['username'] = $b[1];
  }

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }
  
  form_set_error('input_flickr_username', t('Cannot derive username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_flickr_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['useid'];
  }
  return '';
}

function socialmedia_foursquare_platform_info() {
  $platforms = array();
  $platforms['foursquare'] = array(
    'title' => t('Foursquare'),
    'description' => t('URL to your Foursquare profile'),
    'homepage' => 'http://foursquare.com/',
    'redirect path' => 'foursquare',
    'parser callback' => 'socialmedia_foursquare_parser',
    'tokens callback' => 'socialmedia_foursquare_tokens',
  );
  $platforms['foursquare']['form'] = array(
    'title' => t('Foursquare profile'),
    'description' => t('URL to your Foursquare profile'),
  );
  $platforms['foursquare']['tokens']['multi'] = array(
    'foursquare_url' => array(
      'name' => t("Foursquare profile url"),
      'description' => t("URL to Foursquare profile."),
    ),
    'foursquare_url-brief' => array(
      'name' => t("Foursquare profile url (brief)"),
      'description' => t("URL to Foursquare profile without protocol."),
    ),
    'foursquare_username' => array(
      'name' => t("Foursquare name"),
      'description' => t("Foursquare profile name"),
    ),
  );
  return $platforms;
}

function socialmedia_foursquare_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(foursquare\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_foursquare_url', t('Foursquare URL invalid.'));
    }
    return FALSE;
  }
  $a = explode('foursquare.com/', $str);
  $profile['url'] = 'foursquare.com/' . $a[1];
  $profile['userid'] = $profile['username'] = $a[1];

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }
//dsm($profile['url']);
  form_set_error('input_foursquare_username', t('Cannot derive Foursquare username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_foursquare_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
    // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}

function socialmedia_googleplus_platform_info() {
  $platforms = array();
  $platforms['googleplus'] = array(
    'title' => t('Google+'),
    'description' => t('URL to your Google+ profile or page'),
    'homepage' => 'https://plus.google.com/',
    'redirect path' => 'google',
    'parser callback' => 'socialmedia_googleplus_parser',
    'tokens callback' => 'socialmedia_googleplus_tokens',
  ); 
  $platforms['googleplus']['form'] = array(
    'title' => t('Google+ profile'),
    'description' => t('URL to your Google+ profile'),
  );
  $platforms['googleplus']['tokens']['multi'] = array(
    'googleplus_url' => array(
      'name' => t("Google+ profile url"), 
      'description' => t("URL to Google+ profile."),
    ),
    'googleplus_url-brief' => array(
      'name' => t("Google+ profile url (brief)"), 
      'description' => t("URL to Google+ profile without protocol."),
    ), 
    'googleplus_username' => array(
      'name' => t("Google+ name"), 
      'description' => t("Google+ profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_googleplus_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];


  // check +name format
  $pattern = '/(?:http(?:s)?:\/\/)?(plus\.)(google\.com\/)?(\+)(\w+)+/i';
  if (preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    $a = explode('plus.google.com/', $str);
    $profile['url'] = 'plus.google.com/' . $a[1];
    $b = explode('/', $a[1]);
    // check if + format name is used
    if (substr($b[0], 0, 1) == '+') {
      $profile['userid'] = $b[0];
      $values['username'] = substr($b[0], 1);
    }
  }
  else {
    // check numeric id format.
    $pattern = '/(?:http(?:s)?:\/\/)?(plus\.)(google\.com\/)?([0-9]*)/i';
    if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
      if (!isset($matches[3][0])) {
        form_set_error('input_googleplus_url', t('Google+ URL invalid.'));
      }
      return FALSE;
    }
    $a = explode('plus.google.com/', $str);
    $profile['url'] = 'plus.google.com/' . $a[1];
    $profile['userid'] = $matches[3][0];
  }


  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }
  
  form_set_error('input_googleplus_username', t('Cannot derive username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_googleplus_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}

function socialmedia_instagram_platform_info() {
  $platforms = array();
  $platforms['instagram'] = array(
    'title' => t('Instagram'),
    'description' => t('URL to your Instagram profile'),
    'homepage' => 'http://instagram.com/',
    'redirect path' => 'instagram',
    'parser callback' => 'socialmedia_instagram_parser',
    'tokens callback' => 'socialmedia_instagram_tokens',
  );
  $platforms['instagram']['form'] = array(
    'title' => t('Instagram profile'),
    'description' => t('URL to your Instagram profile'),
  );
  $platforms['instagram']['tokens']['multi'] = array(
    'instagram_url' => array(
      'name' => t("Instagram profile url"),
      'description' => t("URL to Instagram profile."),
    ),
    'instagram_url-brief' => array(
      'name' => t("Instagram profile url (brief)"),
      'description' => t("URL to Instagram profile without protocol."),
    ),
    'instagram_username' => array(
      'name' => t("Instagram name"),
      'description' => t("Instagram profile name"),
    ),
  );
  return $platforms;
}

function socialmedia_instagram_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(instagram\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_instagram_url', t('Instagram URL invalid.'));
    }
    return FALSE;
  }
  $a = explode('instagram.com/', $str);
  $profile['url'] = 'instagram.com/' . $a[1];
  $profile['userid'] = $a[1];

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }

//dsm($profile['url']);
  form_set_error('input_instagram_username', t('Cannot derive Instagram username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_instagram_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
    // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}

function socialmedia_linkedin_platform_info() {
  $platforms = array();
  $platforms['linkedin'] = array(
    'title' => t('LinkedIn'),
    'description' => t('URL to your LinkedIn profile or page'),
    'homepage' => 'http://www.linkedin.com/',
    'redirect path' => 'linkedin',
    'parser callback' => 'socialmedia_linkedin_parser',
    'tokens callback' => 'socialmedia_linkedin_tokens',
  ); 
  $platforms['linkedin']['form'] = array(
    'title' => t('LinkedIn profile'),
    'description' => t('URL to your LinkedIn profile'),
  );
  $platforms['linkedin']['tokens']['multi'] = array(
    'linkedin_url' => array(
      'name' => t("LinkedIn profile url"), 
      'description' => t("URL to LinkedIn profile."),
    ),
    'linkedin_url-brief' => array(
      'name' => t("LinkedIn profile url (brief)"), 
      'description' => t("URL to LinkedIn profile without protocol."),
    ), 
    'linkedin_username' => array(
      'name' => t("LinkedIn name"), 
      'description' => t("LinkedIn profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_linkedin_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(linkedin\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_linkedin_url', t('LinkedIn URL invalid.'));
    }
    return FALSE;
  }
  $a = explode('linkedin.com/', $str);
  $profile['url'] = 'www.linkedin.com/' . $a[1];

  if (strpos($a[1], 'in/') === 0) {
    $profile['userid'] = $profile['username'] = substr($a[1], 3);
  }
  else if (strpos($a[1], 'company/') === 0) {
    $profile['userid'] = $profile['username'] = substr($a[1], 8);
    $profile['type'] = 'company';
  }
  else if (strpos($a[1], 'groups/') === 0) {
    // extract group id is encoded in query string value gid
    $c = explode('gid=', $str);
    $d = explode('&', $c[1]);
    $profile['userid'] = $profile['username'] = $d[0];
    $profile['type'] = 'group';
  }

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }

  form_set_error('input_linkedin_username', t('Cannot derive username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_linkedin_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
    case 'type':
      return isset($profile['type']) ? $profile['type'] : '<none>';
  }
  return '';
}

function socialmedia_pinterest_platform_info() {
  $platforms = array();
  $platforms['pinterest'] = array(
    'title' => t('Pinterest'),
    'description' => t('URL to your Pinterest profile or board'),
    'homepage' => 'http://pinterest.com/',
    'redirect path' => 'pinterest',
    'parser callback' => 'socialmedia_pinterest_parser',
    'tokens callback' => 'socialmedia_pinterest_tokens',
  ); 
  $platforms['pinterest']['form'] = array(
    'title' => t('LinkedIn profile'),
    'description' => t('URL to your LinkedIn profile'),
  );
  $platforms['pinterest']['tokens']['multi'] = array(
    'pinterest_url' => array(
      'name' => t("Pinterest profile url"), 
      'description' => t("URL to Pinterest profile."),
    ),
    'pinterest_url-brief' => array(
      'name' => t("Pinterest profile url (brief)"), 
      'description' => t("URL to Pinterest profile without protocol."),
    ), 
    'pinterest_username' => array(
      'name' => t("Pinterest name"), 
      'description' => t("Pinterest profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_pinterest_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(pinterest\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_pinterest_url', t('Pinterest URL invalid.'));
    }
    return FALSE;
  }

  $a = explode('pinterest.com/', $str);
  $profile['url'] = 'pinterest.com/' . $a[1];
  $profile['userid'] = $profile['username'] = $a[1];

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }

  form_set_error('input_pintrest_username', t('Cannot derive username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_pinterest_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}

function socialmedia_rss_platform_info() {
  $platforms = array();
  $platforms['rss'] = array(
    'title' => t('RSS'),
    'description' => t('URL to your RSS feed'),
    'group' => t('Syndication'),
    //'homepage' => '',
    'form callback' => 'socialmedia_rss_form',
    'parser callback' => 'socialmedia_rss_parser',
    'tokens callback' => 'socialmedia_rss_tokens',
  ); 
  $platforms['rss']['form'] = array(
    'title' => t('RSS'),
    'description' => t('URL to your RSS feed'),
  );
  $platforms['rss']['tokens']['multi'] = array(
    'rss_url' => array(
      'name' => t("RSS feed url"), 
      'description' => t("URL to RSS feed."),
    ),  
  );
  return $platforms;  
}

function socialmedia_rss_form($profile) {
  $fields['input_rss_url'] = array(
    '#type' => 'textfield',
    '#title' => t('RSS url'),
    '#default_value' => (isset($profile['inputs']['url'])) ? $profile['inputs']['url'] : 'rss.xml',
    '#description' => t('This is the url to your rss feed. The default feed is located at rss.xml but you might want to link to another feed.'),
    '#size' => 80,
  );
  return $fields;
}

function socialmedia_rss_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $profile['url'] = $values['url'];
  return $profile;
}

function socialmedia_rss_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
    case 'url':
      // removed leading '/' if it exists. Used to support old format before url function added.
      if (substr($profile['url'], 0, 1) == '/') {
        $profile['url'] = substr($profile['url'], 1);
      }
      //return isset($profile['url']) ? $profile['url'] : '';
      return isset($profile['url']) ? url($profile['url']) : '';
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}

function socialmedia_slideshare_platform_info() {
  $platforms = array();
  $platforms['slideshare'] = array(
    'title' => t('SlideShare'),
    'description' => t('URL to your SlideShare profile or page'),
    'homepage' => 'http://www.slideshare.net/',
    'redirect path' => 'slideshare',
    'parser callback' => 'socialmedia_slideshare_parser',
    'tokens callback' => 'socialmedia_slideshare_tokens',
  ); 
  $platforms['slideshare']['form'] = array(
    'title' => t('SlideShare profile'),
    'description' => t('URL to your SlideShare profile'),
  );
  $platforms['slideshare']['tokens']['multi'] = array(
    'slideshare_url' => array(
      'name' => t("SlideShare profile url"), 
      'description' => t("URL to SlideShare profile."),
    ),
    'slideshare_url-brief' => array(
      'name' => t("SlideShare profile url (brief)"), 
      'description' => t("URL to SlideShare profile without protocol."),
    ), 
    'slideshare_username' => array(
      'name' => t("SlideShare name"), 
      'description' => t("SlideShare profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_slideshare_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(slideshare\.net\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_slideshare_url', t('SlideShare URL invalid.'));
    }
    return FALSE;
  }
  $a = explode('slideshare.net/', $str);
  $profile['url'] = 'www.slideshare.net/' . $a[1];

  $b = explode('/', $a[1]);
  $profile['userid'] = $profile['username'] = $b[0];

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }

  return $profile;

  form_set_error('input_slideshare_username', t('Cannot derive username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_slideshare_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
  }
  return '';
}

function socialmedia_tumblr_platform_info() {
  $platforms = array();
  $platforms['tumblr'] = array(
    'title' => t('Tumblr'),
    'description' => t('URL to your Tumblr profile'),
    'homepage' => 'http://tumblr.com/',
    'redirect path' => 'tumblr',
    'parser callback' => 'socialmedia_tumblr_parser',
    'tokens callback' => 'socialmedia_tumblr_tokens',
  );
  $platforms['tumblr']['form'] = array(
    'title' => t('Tumblr profile'),
    'description' => t('URL to your Tumblr profile'),
  );
  $platforms['tumblr']['tokens']['multi'] = array(
    'tumblr_url' => array(
      'name' => t("Tumblr profile url"),
      'description' => t("URL to Tumblr profile."),
    ),
    'tumblr_url-brief' => array(
      'name' => t("Tumblr profile url (brief)"),
      'description' => t("URL to Tumblr profile without protocol."),
    ),
    'tumblr_username' => array(
      'name' => t("Tumblr name"),
      'description' => t("Tumblr profile name"),
    ),
  );
  return $platforms;
}

function socialmedia_tumblr_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(tumblr\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_tumblr_url', t('Tumblr profile URL invalid.'));
    }
    return FALSE;
  }
  $profile['url'] = $matches[1][0] . $matches[2][0];
  $profile['userid'] = $profile['username'] = (isset($values['username']) && $values['username']) ? $values['username'] : $matches[1][0];

  return FALSE;
}

function socialmedia_tumblr_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
    // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}

function socialmedia_twitter_platform_info() {
  $platforms = array();
  $platforms['twitter'] = array(
    'title' => t('Twitter'),    
    //'description' => t('URL to your Twitter account'),
    'homepage' => 'http://twitter.com/',
    'redirect path' => 'twitter',
    'parser callback' => 'socialmedia_twitter_parser',
    'tokens callback' => 'socialmedia_twitter_tokens',
  ); 
  $platforms['twitter']['form'] = array(
    'title' => t('Twitter profile'),
    'description' => t('URL to your Twitter profile'),
  );
  $platforms['twitter']['tokens']['multi'] = array(
    'twitter_url' => array(
      'name' => t("Twitter account url"), 
      'description' => t("URL to twitter account."),
    ),
    'twitter_url-brief' => array(
      'name' => t("Twitter account url (brief)"), 
      'description' => t("URL to twitter account without protocol."),
    ), 
    'twitter_username' => array(
      'name' => t("Twitter username"), 
      'description' => t("Twitter account username"),
    ),   
    'twitter_amp-username' => array(
      'name' => t("Twitter @username"), 
      'description' => t("Twitter account username preceded by @"),
    ),
    'twitter_user-timeline-widget-id' => array(
      'name' => t("Twitter user timeline widget ID"),
      'description' => t("Widget ID provided in Twitter widgets settings for the user timeline."),
    ),
  );
  return $platforms;  
}

function socialmedia_twitter_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(twitter\.com\/)(#!\/)?(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_twitter_url', t('Twitter profile URL invalid.'));
    }
    return FALSE;   
  }
  $profile['url'] = $matches[2][0] . $matches[4][0];
  $profile['userid'] = $profile['username'] = (isset($values['username']) && $values['username']) ? $values['username'] : $matches[4][0];

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($values['user_timeline_widget_id']) && trim($values['user_timeline_widget_id'])) {
    $profile['user_timeline_widget_id'] = $values['user_timeline_widget_id'];
  }
  return $profile;
}

function socialmedia_twitter_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return ($profile['username']) ? $profile['username'] : FALSE;
    case 'userid':
      return ($profile['userid']) ? $profile['userid'] : FALSE;
    case 'amp-username':
      return '@' . $profile['username'];
    case 'user-timeline-widget-id':
      return isset($profile['user_timeline_widget_id']) ? $profile['user_timeline_widget_id'] : FALSE;
  }
  return '';
}

function socialmedia_vimeo_platform_info() {
  $platforms = array();
  $platforms['vimeo'] = array(
    'title' => t('Vimeo'),
    'description' => t('URL to your Vimeo profile or page'),
    'homepage' => 'http://vimeo.com/',
    'redirect path' => 'vimeo',
    'parser callback' => 'socialmedia_vimeo_parser',
    'tokens callback' => 'socialmedia_vimeo_tokens',
  ); 
  $platforms['vimeo']['form'] = array(
    'title' => t('Vimeo profile'),
    'description' => t('URL to your Vimeo profile'),
  );
  $platforms['vimeo']['tokens']['multi'] = array(
    'vimeo_url' => array(
      'name' => t("Vimeo profile url"), 
      'description' => t("URL to Vimeo profile."),
    ),
    'vimeo_url-brief' => array(
      'name' => t("Vimeo profile url (brief)"), 
      'description' => t("URL to Vimeo profile without protocol."),
    ), 
    'vimeo_username' => array(
      'name' => t("Vimeo name"), 
      'description' => t("Vimeo profile name"),
    ),   
  );
  return $platforms;  
}

function socialmedia_vimeo_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(vimeo\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_vimeo_url', t('Vimeo profile URL invalid.'));
    }
    return FALSE;
  }
  $a = explode('vimeo.com/', $str);
  $profile['url'] = 'vimeo.com/' . $a[1];
  $profile['userid'] = $profile['username'] = $a[1];

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }

//dsm($profile['url']);   
  form_set_error('input_vimeo_username', t('Cannot derive Vimeo username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_vimeo_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}

function socialmedia_youtube_platform_info() {
  $platforms = array();
  $platforms['youtube'] = array(
    'title' => t('YouTube'),
    'description' => t('URL to your YouTube profile or page'),
    'homepage' => 'http://www.youtube.com/',
    'redirect path' => 'youtube',
    'parser callback' => 'socialmedia_youtube_parser',
    'tokens callback' => 'socialmedia_youtube_tokens',
  ); 
  $platforms['youtube']['form'] = array(
    'title' => t('YouTube profile'),
    'description' => t('URL to your YouTube profile'),
  );
  $platforms['youtube']['tokens']['multi'] = array(
    'youtube_url' => array(
      'name' => t("YouTube profile url"), 
      'description' => t("URL to YouTube profile."),
    ),
    'youtube_url-brief' => array(
      'name' => t("YouTube profile url (brief)"), 
      'description' => t("URL to YouTube profile without protocol."),
    ), 
    'youtube_username' => array(
      'name' => t("YouTube name"), 
      'description' => t("YouTube profile name"),
    ),
    'youtube_userid' => array(
      'name' => t("YouTube user id"),
      'description' => t("YouTube profile id"),
    ),
  );
  return $platforms;  
}

function socialmedia_youtube_parser($values, $scope = 'site') {
  $profile = array('url' => '', 'username' => '', 'userid' => '');
  $str = $values['url'];
  $pattern = '/(?:http:\/\/)?(www\.)*(youtube\.com\/)(\w+)+/i';
  //$pattern = '/^http:\/\/(www\.)?twitter\.com\/(#!\/)?(?<name>[^\/]+)(/\w+)*$/';
  if (!preg_match($pattern, $str, $matches, PREG_OFFSET_CAPTURE)) {
    if (trim($values['url'])) {
      form_set_error('input_youtube_url', t('YouTube profile URL invalid.'));
    }
    return FALSE;    
  }
  $a = explode('youtube.com/', $str);
  $profile['url'] = 'www.youtube.com/' . $a[1];

  $b = explode('/', $a[1]);
  if (strpos($b[0], 'user') === 0) {
    $profile['userid'] = $profile['username'] = substr($a[1], 5);
  }
  elseif (count($b) == 1) {
    $profile['userid'] = $profile['username'] = $b[0];
  }

  if (isset($values['username']) && trim($values['username'])) {
    $profile['username'] = $values['username'];
  }

  if (isset($profile['username'])) {
    return $profile;
  }

  form_set_error('input_youtube_username', t('Cannot derive username for this type URL. Please provide a username.'));
  return FALSE;
}

function socialmedia_youtube_tokens($key, $profile) {
  if (empty($profile['url'])) {
    return FALSE;
  }
  switch ($key) {
  // Simple key values on the node.
    case 'url':
      return 'http://' . $profile['url'];
    case 'url-brief':
      return $profile['url'];
    case 'username':
      return $profile['username'];
    case 'userid':
      return $profile['userid'];
  }
  return '';
}