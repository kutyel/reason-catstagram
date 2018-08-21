let component = ReasonReact.statelessComponent("Single");

open Belt;
open Types;

let make = (~posts, ~postId, _children) => {
  ...component,
  render: _self => {
    let post = posts->List.getBy(({id}) => id == postId);
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
