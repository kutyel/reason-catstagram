let extend = ReasonReact.statelessComponent("Error");

let make = _children => {
  ...extend,
  render: _self =>
    <div className="centered">
      <h1> {ReasonReact.string("An error occurred! :(")} </h1>
    </div>,
};
