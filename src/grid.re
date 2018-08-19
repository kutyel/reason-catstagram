let component = ReasonReact.statelessComponent("Grid");

open Belt;

let make = (~posts, _children) => {
  ...component,
  render: _self =>
    <div className="photo-grid">
      {
        List.map(posts, post => <Post post />)
        |> List.toArray
        |> ReasonReact.array
      }
    </div>,
};
