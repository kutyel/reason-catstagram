let component = ReasonReact.statelessComponent "Mention";

let make ::user _children => {
  ...component,
  render: fun _self =>
    <a target="blank" href=("https://www.instagram.com/" ^ user)>
      (ReasonReact.stringToElement ("@" ^ user))
    </a>
};
