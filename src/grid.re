let component = ReasonReact.statelessComponent("Grid");

let make = (~posts, ~onLike, ~navigate, _children) => {
  ...component,
  render: _self =>
    <div className="photo-grid">
      {
        List.map(posts, post =>
          <Post key={post.Types.Post.id} post onLike navigate />
        )
        |> List.toArray
        |> ReasonReact.array
      }
    </div>,
};
