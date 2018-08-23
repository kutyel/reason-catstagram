let extend = ReasonReact.statelessComponent("Error");

let make = _children => {
  ...extend,
  render: _self =>
    <div className="spinner">
      <h1> {ReasonReact.string("An error occurred! :(")} </h1>
    </div>,
};
