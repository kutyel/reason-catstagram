// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';


var make = (
  function guid() {
  	function s4() {
    	return Math.floor((1 + Math.random()) * 0x10000)
      	.toString(16)
      	.substring(1);
  	}
  	return s4() + s4() + '-' + s4() + '-' + s4() + '-' + s4() + '-' + s4() + s4() + s4();
}
  );

exports.make = make;
/* make Not a pure module */
