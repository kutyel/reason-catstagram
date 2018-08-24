let component = ReasonReact.statelessComponent("Grid");

open Belt;
open Types;

let make = (~posts: list(post), ~onLike, ~onLink, _children) => {
  ...component,
  render: _self =>
    <div className="photo-grid">
      {
        List.map(posts, post => <Post key={post.id} post onLike onLink />)
        |> List.toArray
        |> ReasonReact.array
      }
    </div>,
};
