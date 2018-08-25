let component = ReasonReact.statelessComponent("Single");

open Types;

let make = (~posts, ~postId, ~comments, ~onLike, ~onLink, _children) => {
  ...component,
  render: _self => {
    let post = posts->Belt.List.getBy(({id}) => id == postId);
    <div className="single-photo">
      {
        switch (post) {
        | None => <Error />
        | Some(post) => <Post post onLike onLink />
        }
      }
      <Comments comments />
    </div>;
  },
};
