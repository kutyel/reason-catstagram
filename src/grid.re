let component = ReasonReact.statelessComponent("Grid");

module B = Belt;

let make = (~posts, ~onLike, ~onClick, _children) => {
  ...component,
  render: _self =>
    <div className="photo-grid">
      {
        B.List.map(posts, post =>
          <Post key={post.Types.Post.id} post onLike onClick />
        )
        |> B.List.toArray
        |> ReasonReact.array
      }
    </div>,
};
