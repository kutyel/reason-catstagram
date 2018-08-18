// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.statelessComponent("Post");

function make(post, _) {
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
              var count = post[/* count */2];
              var id = post[/* id */0];
              var count$1 = count !== undefined ? String(count) : "0";
              return React.createElement("figure", {
                          className: "grid-figure"
                        }, React.createElement("div", {
                              className: "grid-photo-wrap"
                            }, React.createElement("a", {
                                  href: "/view/" + (String(id) + "")
                                }, React.createElement("img", {
                                      className: "grid-photo",
                                      alt: id,
                                      src: post[/* image */1]
                                    }))), React.createElement("figcaption", undefined, React.createElement("p", undefined, post[/* description */3]), React.createElement("div", {
                                  className: "control-buttons"
                                }, React.createElement("button", {
                                      className: "liked"
                                    }, "&hearts; " + count$1), React.createElement("a", {
                                      className: "button",
                                      href: "/view/" + (String(id) + "")
                                    }, React.createElement("span", {
                                          className: "comment-count"
                                        }, React.createElement("span", {
                                              className: "speech-bubble"
                                            }), count$1)))));
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
