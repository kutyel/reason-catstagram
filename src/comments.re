let component = ReasonReact.statelessComponent("Comments");

module B = Belt;

let make = (~comments, _children) => {
  ...component,
  render: _self =>
    <div className="comments">
      <div className="comments-list">
        {
          comments
          ->B.List.map(({Types.Comment.id, text, from: {username}}) =>
              <div className="comment" key=id>
                <p>
                  <strong> {ReasonReact.string(username)} </strong>
                  {ReasonReact.string(text)}
                  <button className="remove-comment">
                    {ReasonReact.string({js|✖️|js})}
                  </button>
                </p>
              </div>
            )
          |> B.List.toArray
          |> ReasonReact.array
        }
      </div>
      <form className="comment-form">
        <input type_="text" placeholder="author" />
        <input type_="text" placeholder="comment" />
        <input type_="submit" hidden=true />
      </form>
    </div>,
};
