let component = ReasonReact.statelessComponent "Hashtag";

let make ::text _children => {
  ...component,
  render: fun _self =>
    <a target="blank" href=("https://www.instagram.com/explore/tags/" ^ text)>
      (ReasonReact.stringToElement ("#" ^ text))
    </a>
};
