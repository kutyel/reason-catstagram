[@react.component]
let make = (~text) =>
  <a target="blank" href={"https://www.instagram.com/explore/tags/" ++ text}>
    {React.string("#" ++ text)}
  </a>;
