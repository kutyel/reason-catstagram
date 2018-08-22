let component = ReasonReact.statelessComponent("Spinner");

let make = _children => {
  ...component,
  render: _self =>
    <div className="lds-ring"> <div /> <div /> <div /> <div /> </div>,
};
