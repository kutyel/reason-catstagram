// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

function identity(x) {
  return x;
}

function caption(json) {
  return /* record */[/* text */Json_decode.field("text", Json_decode.string, json)];
}

function resolution(json) {
  return /* record */[/* url */Json_decode.field("url", Json_decode.string, json)];
}

function likes(json) {
  return /* record */[/* count */Json_decode.field("count", Json_decode.$$int, json)];
}

function images(json) {
  return /* record */[/* standard_resolution */Json_decode.field("standard_resolution", resolution, json)];
}

function post(json) {
  return /* record */[
          /* id */Json_decode.field("id", Json_decode.string, json),
          /* caption */Json_decode.field("caption", caption, json),
          /* images */Json_decode.field("images", images, json),
          /* likes */Json_decode.field("likes", likes, json)
        ];
}

function posts(json) {
  return List.map(identity, Json_decode.field("data", (function (param) {
                    return Json_decode.list(post, param);
                  }), json));
}

var Decode = /* module */[
  /* identity */identity,
  /* caption */caption,
  /* resolution */resolution,
  /* likes */likes,
  /* images */images,
  /* post */post,
  /* posts */posts
];

exports.Decode = Decode;
/* No side effect */
