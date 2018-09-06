let component = ReasonReact.statelessComponent("Single");

let make = (~posts, ~postId, ~send, ~navigate, _children) => {
  ...component,
  render: _self =>
    switch (posts->Belt.List.getBy(({Types.Post.id}) => id == postId)) {
    | None => <Error />
    | Some(post) =>
      <div className="single-photo">
        <Post post send navigate />
        <Comments postId send comments={post.comments} />
      </div>
    },
};
