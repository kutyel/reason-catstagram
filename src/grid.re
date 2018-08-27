let component = ReasonReact.statelessComponent("Grid");

open Belt;

let make = (~posts, ~onLike, ~onClick, _children) => {
  ...component,
  render: _self =>
    <div className="photo-grid">
      {
        List.map(posts, post =>
          <Post key={post.Types.Post.id} post onLike onClick />
        )
        |> List.toArray
        |> ReasonReact.array
      }
    </div>,
};
