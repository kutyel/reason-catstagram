let component = ReasonReact.statelessComponent("Single");

open Types;

let make = (~posts, ~postId, ~onLike, ~onLink, _children) => {
  ...component,
  render: _self => {
    let post = posts->Belt.List.getBy(({id}) => id == postId);
    switch (post) {
    | None => <Error />
    | Some(post) =>
      <div className="single-photo">
        <Post post onLike onLink />
        <Comments comments={post.comments} />
      </div>
    };
  },
};
