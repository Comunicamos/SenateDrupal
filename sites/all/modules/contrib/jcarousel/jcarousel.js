// $Id: jcarousel.js,v 1.1.2.2.2.1 2008/12/02 20:22:46 robloach Exp $

/**
 * @file
 * Provides the jCarousel Drupal behavior.
 */

/**
 * The jCarousel Drupal behavior that creates the set of jCarousel elements from Drupal.settings.jcarousel.
 */
Drupal.behaviors.jcarousel = function() {
  for (selector in Drupal.settings.jcarousel) {
    // Retrieve the options.
    var options = Drupal.settings.jcarousel[selector];

    // Convert any callback arguments from strings to function calls.
    var callbacks = ['initCallback', 'itemLoadCallback', 'itemFirstInCallback', 'itemFirstOutCallback', 'itemLastOutCallback', 'itemLastInCallback', 'itemVisibleInCallback', 'itemVisibleOutCallback', 'buttonNextCallback', 'buttonPrevCallback'];
    for (callback in callbacks) {
      var callbackname = callbacks[callback];
      // The callback depends on its type.
      if (typeof(options[callbackname]) == 'string') {
        // Strings are evaluated as functions.
        options[callbackname] = eval(options[callbackname]);
      }
      else if (typeof(options[callbackname]) == 'object' && (options[callbackname] instanceof Array)) {
        // Arrays are evaluated as a list of callback registrations. This is because callbacks
        // like itemVisibleInCallback can either be a function call back, or an array of callbacks
        // consisting of both onBeforeAnimation and onAfterAnimation.
        for (subcallback in options[callbackname]) {
          var name = options[callbackname][subcallback];
          options[callbackname][name] = eval(options[callbackname][name]);
        }
      }
    }

    // Prepare the skin name to be added as a class name.
    var skin = options['skin'];
    if (typeof(skin) == 'string') {
      skin = ' jcarousel-skin-' + skin;
    }
    else {
      skin = '';
    }

    // Create the countdown element on non-processed elements.
    $(selector + ':not(.processed)').addClass('processed' + skin).jcarousel(options);
  }
}
