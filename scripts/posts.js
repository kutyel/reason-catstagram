// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Fs = require("fs");
var Js_exn = require("bs-platform/lib/js/js_exn.js");
var NodeFetch = require("node-fetch");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");

var NodeFetch$1 = /* module */[];

var token = (process.env.API_TOKEN);

function buildUrl(token) {
  return "https://api.instagram.com/v1/users/self/media/recent/?access_token=" + (String(token) + "");
}

if (token == null) {
  console.log("Please supply your instagram token as API_TOKEN env var");
} else {
  var url = buildUrl(token);
  NodeFetch.default(url).then((function (prim) {
              return prim.text();
            })).then((function (txt) {
            var exit = 0;
            var val;
            try {
              Fs.writeFileSync("./posts.json", txt, "utf8");
              val = /* () */0;
              exit = 1;
            }
            catch (raw_exn){
              var exn = Caml_js_exceptions.internalToOCamlException(raw_exn);
              if (exn[0] === Js_exn.$$Error) {
                var match = exn[1].message;
                if (match !== undefined) {
                  console.log("Error writing the posts to posts.json: " + (String(match) + ""));
                } else {
                  console.log("An unknown error occurred while writing the posts to posts.json");
                }
              } else {
                throw exn;
              }
            }
            if (exit === 1) {
              console.log("all posts written to ./posts.json!");
            }
            return Promise.resolve(/* () */0);
          })).catch((function (param) {
          return Promise.resolve((console.log("Something went wrong while fetching the posts from instagram"), /* () */0));
        }));
}

var token$1 = (token == null) ? undefined : Caml_option.some(token);

exports.NodeFetch = NodeFetch$1;
exports.token = token$1;
exports.buildUrl = buildUrl;
/* token Not a pure module */
