// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Grid = require("./grid.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var $$Error = require("./error.js");
var Types = require("./Types.js");
var React = require("react");
var Single = require("./single.js");
var Spinner = require("./spinner.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.reducerComponent("App");

var token = (process.env.API_TOKEN);

function urlToRoute(url) {
  var match = url[/* path */0];
  if (match && match[0] === "view") {
    var match$1 = match[1];
    if (match$1 && !match$1[1]) {
      return /* Detail */[match$1[0]];
    } else {
      return /* Base */0;
    }
  } else {
    return /* Base */0;
  }
}

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              var watcher = ReasonReact.Router[/* watchUrl */1]((function (url) {
                      return Curry._1(self[/* send */3], /* ChangeRoute */Block.__(4, [urlToRoute(url)]));
                    }));
              Curry._1(self[/* send */3], /* FetchPosts */0);
              return Curry._1(self[/* onUnmount */4], (function () {
                            return ReasonReact.Router[/* unwatchUrl */2](watcher);
                          }));
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (param) {
              var send = param[/* send */3];
              var state = param[/* state */1];
              var onLink = function (id) {
                return Curry._1(send, /* ChangeRoute */Block.__(4, [id]));
              };
              var onLike = function (post, like) {
                return Curry._1(send, /* Like */Block.__(3, [
                              post,
                              like
                            ]));
              };
              var tmp;
              if (typeof state === "number") {
                tmp = state !== 0 ? ReasonReact.element(undefined, undefined, Spinner.make(/* array */[])) : ReasonReact.element(undefined, undefined, $$Error.make(/* array */[]));
              } else {
                var posts = state[1];
                var route = state[0];
                tmp = route ? ReasonReact.element(undefined, undefined, Single.make(posts, route[0], onLike, onLink, /* array */[])) : ReasonReact.element(undefined, undefined, Grid.make(posts, onLike, onLink, /* array */[]));
              }
              return React.createElement("div", undefined, React.createElement("h1", undefined, React.createElement("a", {
                                  href: "/"
                                }, "Catstagram")), tmp);
            }),
          /* initialState */(function () {
              return /* Loading */1;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (typeof action === "number") {
                if (action === 0) {
                  return /* UpdateWithSideEffects */Block.__(2, [
                            /* Loading */1,
                            (function (param) {
                                var send = param[/* send */3];
                                fetch("https://api.instagram.com/v1/users/self/media/recent/?access_token=" + (String(token) + "")).then((function (prim) {
                                            return prim.json();
                                          })).then((function (json) {
                                          var posts = Types.Post[/* decodePosts */1](json);
                                          return Promise.resolve(Curry._1(send, /* FetchedPosts */Block.__(1, [posts])));
                                        })).catch((function () {
                                        return Promise.resolve(Curry._1(send, /* FailedToFetch */1));
                                      }));
                                return /* () */0;
                              })
                          ]);
                } else {
                  return /* Update */Block.__(0, [/* Error */0]);
                }
              } else {
                switch (action.tag | 0) {
                  case 0 : 
                      var mediaId = action[0];
                      return /* UpdateWithSideEffects */Block.__(2, [
                                /* Loading */1,
                                (function (param) {
                                    var send = param[/* send */3];
                                    fetch("https://api.instagram.com/v1/media/" + (String(mediaId) + ("/comments?access_token=" + (String(token) + "")))).then((function (prim) {
                                                return prim.json();
                                              })).then((function (json) {
                                              var comments = Types.Comment[/* decodeComments */1](json);
                                              return Promise.resolve(Curry._1(send, /* FetchedComments */Block.__(2, [comments])));
                                            })).catch((function () {
                                            return Promise.resolve(Curry._1(send, /* FailedToFetch */1));
                                          }));
                                    return /* () */0;
                                  })
                              ]);
                  case 1 : 
                      return /* Update */Block.__(0, [/* Loaded */[
                                  urlToRoute(ReasonReact.Router[/* dangerouslyGetInitialUrl */3](/* () */0)),
                                  action[0]
                                ]]);
                  case 2 : 
                      console.log(action[0]);
                      return /* NoUpdate */0;
                  case 3 : 
                      var like = action[1];
                      var post = action[0];
                      return /* Update */Block.__(0, [typeof state === "number" ? state : /* Loaded */[
                                    state[0],
                                    Belt_List.map(state[1], (function (p) {
                                            var match = Caml_obj.caml_equal(p, post);
                                            if (match) {
                                              return /* record */[
                                                      /* id */p[/* id */0],
                                                      /* caption */p[/* caption */1],
                                                      /* images */p[/* images */2],
                                                      /* likes : record */[/* count */p[/* likes */3][/* count */0] + (
                                                          like ? 1 : -1
                                                        ) | 0],
                                                      /* num_comments */p[/* num_comments */4],
                                                      /* user_has_liked */like,
                                                      /* comments */p[/* comments */6]
                                                    ];
                                            } else {
                                              return p;
                                            }
                                          }))
                                  ]]);
                  case 4 : 
                      var route = action[0];
                      return /* UpdateWithSideEffects */Block.__(2, [
                                typeof state === "number" ? state : /* Loaded */[
                                    route,
                                    state[1]
                                  ],
                                (function (self) {
                                    if (route) {
                                      return Curry._1(self[/* send */3], /* FetchComments */Block.__(0, [route[0]]));
                                    } else {
                                      return /* () */0;
                                    }
                                  })
                              ]);
                  
                }
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

var T = 0;

exports.T = T;
exports.component = component;
exports.token = token;
exports.urlToRoute = urlToRoute;
exports.make = make;
/* component Not a pure module */
