// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

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
          /* likes */Json_decode.field("likes", likes, json),
          /* user_has_liked */Json_decode.field("user_has_liked", Json_decode.bool, json)
        ];
}

function posts(json) {
  return Json_decode.field("data", (function (param) {
                return Json_decode.list(post, param);
              }), json);
}

exports.caption = caption;
exports.resolution = resolution;
exports.likes = likes;
exports.images = images;
exports.post = post;
exports.posts = posts;
/* No side effect */
