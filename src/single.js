// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Post = require("./post.js");
var $$Error = require("./error.js");
var React = require("react");
var Comments = require("./comments.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");

function Single(Props) {
  var posts = Props.posts;
  var postId = Props.postId;
  var dispatch = Props.dispatch;
  var navigate = Props.navigate;
  var match = Belt_List.getBy(posts, (function (param) {
          return param[/* id */0] === postId;
        }));
  if (match !== undefined) {
    var post = match;
    return React.createElement("div", {
                className: "single-photo"
              }, React.createElement(Post.make, {
                    post: post,
                    dispatch: dispatch,
                    navigate: navigate
                  }), React.createElement(Comments.make, {
                    comments: post[/* comments */6],
                    dispatch: dispatch,
                    postId: postId
                  }));
  } else {
    return React.createElement($$Error.make, { });
  }
}

var make = Single;

exports.make = make;
/* Post Not a pure module */
