let component = ReasonReact.statelessComponent("Link");

type link =
  | Mention
  | Hashtag;

let make = (~text, ~link, _children) => {
  ...component,
  render: _self =>
    switch link {
    | Mention =>
      <a target="blank" href=("https://www.instagram.com/" ++ text)>
        (ReasonReact.string("@" ++ text))
      </a>
    | Hashtag =>
      <a
        target="blank"
        href=("https://www.instagram.com/explore/tags/" ++ text)>
        (ReasonReact.string("#" ++ text))
      </a>
    }
};
