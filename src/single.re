[@react.component]
let make = (~posts, ~postId, ~dispatch, ~navigate) =>
  switch (posts->List.getBy(({Types.Post.id}) => id == postId)) {
  | None => <Error />
  | Some(post) =>
    <div className="single-photo">
      <Post post dispatch navigate />
      <Comments postId dispatch comments={post.comments} />
    </div>
  };
