let component = ReasonReact.statelessComponent("Grid");

let make = (~posts, ~send, ~navigate, _children) => {
  ...component,
  render: _self =>
    <div className="photo-grid">
      {
        List.map(posts, post =>
          <Post key={post.Types.Post.id} post send navigate />
        )
        |> List.toArray
        |> ReasonReact.array
      }
    </div>,
};
