let component = ReasonReact.statelessComponent("Grid");

open Belt;

let make = (~posts, ~onLike, ~onLink, _children) => {
  ...component,
  render: _self =>
    <div className="photo-grid">
      {
        List.map(posts, post =>
          <Post key={post.Types.Post.id} post onLike onLink />
        )
        |> List.toArray
        |> ReasonReact.array
      }
    </div>,
};