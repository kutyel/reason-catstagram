[@react.component]
let make = (~posts, ~dispatch, ~navigate) =>
  <div className="photo-grid">
    {List.map(posts, post =>
       <Post key={post.Types.Post.id} post dispatch navigate />
     )
     |> List.toArray
     |> React.array}
  </div>;
