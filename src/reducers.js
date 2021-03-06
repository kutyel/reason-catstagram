// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Uuid = require("./uuid.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Types = require("./Types.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

var token = (process.env.API_TOKEN);

function appReducer(action, state) {
  if (typeof action === "number") {
    if (action === 0) {
      return /* UpdateWithSideEffects */Block.__(1, [
                /* Loading */1,
                (function (param) {
                    var send = param[/* send */0];
                    fetch("https://api.instagram.com/v1/users/self/media/recent/?access_token=" + (String(token) + "")).then((function (prim) {
                                return prim.json();
                              })).then((function (json) {
                              var posts = Types.Post[/* decode */1](json);
                              return Promise.resolve(Curry._1(send, /* FetchedPosts */Block.__(1, [posts])));
                            })).catch((function (_e) {
                            return Promise.resolve(Curry._1(send, /* FailedToFetch */1));
                          }));
                    return undefined;
                  })
              ]);
    } else {
      return /* Update */Block.__(0, [/* Error */0]);
    }
  } else {
    switch (action.tag | 0) {
      case 0 : 
          var mediaId = action[0];
          return /* SideEffects */Block.__(2, [(function (param) {
                        var send = param[/* send */0];
                        fetch("https://api.instagram.com/v1/media/" + (String(mediaId) + ("/comments?access_token=" + (String(token) + "")))).then((function (prim) {
                                    return prim.json();
                                  })).then((function (json) {
                                  var comments = Types.$$Comment[/* decode */1](json);
                                  return Promise.resolve(Curry._1(send, /* FetchedComments */Block.__(2, [
                                                    mediaId,
                                                    comments
                                                  ])));
                                })).catch((function (_e) {
                                return Promise.resolve(Curry._1(send, /* FailedToFetch */1));
                              }));
                        return undefined;
                      })]);
      case 1 : 
          return /* Update */Block.__(0, [/* Loaded */[
                      Types.Route[/* urlToRoute */0](ReasonReactRouter.dangerouslyGetInitialUrl(/* () */0)),
                      action[0]
                    ]]);
      case 2 : 
          var comments = action[1];
          var postId = action[0];
          if (typeof state === "number") {
            return /* NoUpdate */0;
          } else {
            return /* Update */Block.__(0, [/* Loaded */[
                        state[0],
                        Belt_List.map(state[1], (function (p) {
                                var match = p[/* id */0] === postId;
                                if (match) {
                                  return /* record */[
                                          /* id */p[/* id */0],
                                          /* caption */p[/* caption */1],
                                          /* images */p[/* images */2],
                                          /* likes */p[/* likes */3],
                                          /* num_comments */p[/* num_comments */4],
                                          /* user_has_liked */p[/* user_has_liked */5],
                                          /* comments */comments
                                        ];
                                } else {
                                  return p;
                                }
                              }))
                      ]]);
          }
      case 3 : 
          var comment = action[2];
          var author = action[1];
          var postId$1 = action[0];
          if (typeof state === "number") {
            return /* NoUpdate */0;
          } else {
            return /* Update */Block.__(0, [/* Loaded */[
                        state[0],
                        Belt_List.map(state[1], (function (p) {
                                var match = p[/* id */0] === postId$1;
                                if (match) {
                                  return /* record */[
                                          /* id */p[/* id */0],
                                          /* caption */p[/* caption */1],
                                          /* images */p[/* images */2],
                                          /* likes */p[/* likes */3],
                                          /* num_comments */p[/* num_comments */4],
                                          /* user_has_liked */p[/* user_has_liked */5],
                                          /* comments : :: */[
                                            /* record */[
                                              /* id */Uuid.make(/* () */0),
                                              /* from : record */[/* username */author],
                                              /* text */comment,
                                              /* created_time */new Date().toISOString()
                                            ],
                                            p[/* comments */6]
                                          ]
                                        ];
                                } else {
                                  return p;
                                }
                              }))
                      ]]);
          }
      case 4 : 
          var commentId = action[1];
          var postId$2 = action[0];
          if (typeof state === "number") {
            return /* NoUpdate */0;
          } else {
            return /* Update */Block.__(0, [/* Loaded */[
                        state[0],
                        Belt_List.map(state[1], (function (p) {
                                var match = p[/* id */0] === postId$2;
                                if (match) {
                                  return /* record */[
                                          /* id */p[/* id */0],
                                          /* caption */p[/* caption */1],
                                          /* images */p[/* images */2],
                                          /* likes */p[/* likes */3],
                                          /* num_comments */p[/* num_comments */4],
                                          /* user_has_liked */p[/* user_has_liked */5],
                                          /* comments */Belt_List.keep(p[/* comments */6], (function (c) {
                                                  return c[/* id */0] !== commentId;
                                                }))
                                        ];
                                } else {
                                  return p;
                                }
                              }))
                      ]]);
          }
      case 5 : 
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
      case 6 : 
          return /* UpdateWithSideEffects */Block.__(1, [
                    typeof state === "number" ? state : /* Loaded */[
                        action[0],
                        state[1]
                      ],
                    (function (param) {
                        var state = param[/* state */1];
                        if (typeof state !== "number") {
                          var match = state[0];
                          if (match) {
                            var id = match[0];
                            var match$1 = Belt_List.getBy(state[1], (function (p) {
                                    return p[/* id */0] === id;
                                  }));
                            if (match$1 !== undefined) {
                              if (match$1[/* comments */6]) {
                                
                              } else {
                                Curry._1(param[/* send */0], /* FetchComments */Block.__(0, [id]));
                              }
                            }
                            
                          }
                          
                        }
                        return undefined;
                      })
                  ]);
      
    }
  }
}

exports.token = token;
exports.appReducer = appReducer;
/* token Not a pure module */
