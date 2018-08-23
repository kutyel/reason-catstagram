let component = ReasonReact.statelessComponent("Single");

open Belt;
open Types;

let make = (~posts, ~postId, ~onLike, _children) => {
  ...component,
  render: _self => {
    let post = posts->List.getBy(({id}) => id == postId);
    <div className="single-photo">
      {
        switch (post) {
        | None => <Error />
        | Some(post) => <Post post onLike />
        }
      }
    </div>;
  },
};
