let component = ReasonReact.statelessComponent("Single");

open Belt;
open Types;

let make = (~posts: list(post), ~postId, _children) => {
  ...component,
  render: _self => {
    let post = posts->List.getBy(p => p.id == postId);
    <div className="single-photo">
      {
        switch (post) {
        | Some(post) => <Post post />
        | None => ReasonReact.string("cat not found... :(")
        }
      }
    </div>;
  },
};
