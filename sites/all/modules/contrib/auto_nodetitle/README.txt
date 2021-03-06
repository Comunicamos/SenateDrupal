$Id: README.txt,v 1.7.2.1 2008/06/08 13:10:07 fago Exp $

Automatic Nodetitle Module
------------------------
by Wolfgang Ziegler, nuppla@zites.net


Description
-----------
This is a small and efficent module that allows hiding of the content title field. To prevent
empty content title fields it sets the title to the content type name or to an configurable
string. If the token module is installled it's possible to use various content data for the
autogenerated title - e.g. use the text of a CCK field.

Advanced users can also provide some PHP code, that is used for automatically generating an
appropriate title.

Installation 
------------
 * (optional) Download and install the token module.
 * Copy the module's directory to your modules directory and activate the module.
 * For each content type you want to have an automatic title, click on the
   "edit" link for it on 'admin/content/types'
 * At the top of the content type edit form, there is a "Automatic title
   generation" box allowing you to configure the details for the current content
   type.
 
 
 
 
 Advanced Use: PHP Code
------------------------
 You can access $node from your php code. Look at this simple example, which just adds the node's
 author as title:
 
<?php return "Author: $node->name"; ?>

 
 
 Advanced Use: Combining tokens and PHP
 ---------------------------------------
 
 You can combine php evalution with the token module, because tokens are replaced first.
 Here is an example:
 
<?php
  $token = '[field_testtext-raw]';
  if (empty($token)) {
    return '[type]';
  }
  else {
    return $token;
  } 
?>

 So if the text of the CCK textfield [field_testtext-raw] isn't empty it will be used as title.
 Otherwise the node type will be used.

