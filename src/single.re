let component = ReasonReact.statelessComponent("Single");

let make = (~posts, ~postId, ~onLike, ~onClick, _children) => {
  ...component,
  render: _self =>
    switch (posts->Belt.List.getBy(({Types.Post.id}) => id == postId)) {
    | None => <Error />
    | Some(post) =>
      <div className="single-photo">
        <Post post onLike onClick />
        <Comments comments={post.comments} />
      </div>
    },
};
