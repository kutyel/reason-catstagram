let component = ReasonReact.statelessComponent("Spinner");

let make = _children => {
  ...component,
  render: _self =>
    <div className="centered"> <div /> <div /> <div /> <div /> </div>,
};
