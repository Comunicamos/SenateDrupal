/* $Id: align.js,v 1.2 2008/07/15 16:30:30 bdragon Exp $ */

/**
 * Alignment widget.
 * Applies CSS classes to a macro.
 */

////////////////////////////////////////
//           Align widget             //
////////////////////////////////////////
Drupal.gmap.addHandler('align', function(elem) {
  var obj = this;
  // Respond to incoming alignment changes.
  var binding = obj.bind("alignchange", function(){
    elem.value = obj.vars.align;
  });
  // Send out outgoing alignment changes.
  $(elem).change(function() {
    obj.vars.align = elem.value;
    obj.change("alignchange",binding);
  });
});

Drupal.gmap.addHandler('gmap',function(elem) {
  var obj = this;
  // Respond to incoming alignment changes.
  var binding = obj.bind("alignchange", function() {
    var cont = obj.map.getContainer();
    $(cont)
      .removeClass('gmap-left')
      .removeClass('gmap-center')
      .removeClass('gmap-right');
    if (obj.vars.align=='Left') {$(cont).addClass('gmap-left');}
    if (obj.vars.align=='Center') {$(cont).addClass('gmap-center');}
    if (obj.vars.align=='Right') {$(cont).addClass('gmap-right');}
  });
  // Send out outgoing alignment changes.
  // N/A

  obj.bind('buildmacro',function(add) {
    if (obj.vars.align && obj.vars.align != 'None') {
      add.push('align='+obj.vars.align);
    }
  });
});
