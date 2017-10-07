let component = ReasonReact.statelessComponent "App";

let make ::message _children => {
  ...component,
  render: fun _self =>
    <div>
      <h1> (ReasonReact.stringToElement message) </h1>
      <p> <Hashtag text="caturday" /> </p>
      <p> <Mention user="theschrodingercat" /> </p>
    </div>
};
