// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Post = require("./post.js");
var $$Error = require("./error.js");
var React = require("react");
var Comments = require("./comments.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.statelessComponent("Single");

function make(posts, postId, onLike, onClick, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              var post = Belt_List.getBy(posts, (function (param) {
                      return param[/* id */0] === postId;
                    }));
              if (post !== undefined) {
                var post$1 = post;
                return React.createElement("div", {
                            className: "single-photo"
                          }, ReasonReact.element(undefined, undefined, Post.make(post$1, onLike, onClick, /* array */[])), ReasonReact.element(undefined, undefined, Comments.make(post$1[/* comments */6], /* array */[])));
              } else {
                return ReasonReact.element(undefined, undefined, $$Error.make(/* array */[]));
              }
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */
