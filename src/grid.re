let component = ReasonReact.statelessComponent("Grid");

open Belt;
open Types;

let make = (~posts, _children) => {
  ...component,
  render: _self =>
    <div className="photo-grid">
      {
        List.map(posts, post => <Post key={post.id} post />)
        |> List.toArray
        |> ReasonReact.array
      }
    </div>,
};
