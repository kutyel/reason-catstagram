let component = ReasonReact.statelessComponent("Comments");

let make = (~comments, ~remove, _children) => {
  ...component,
  render: _self =>
    <div className="comments">
      <div className="comments-list">
        {
          comments
          ->List.map(({Types.Comment.id, text, from: {username}}) =>
              <div className="comment" key=id>
                <p>
                  <strong> {ReasonReact.string(username)} </strong>
                  {ReasonReact.string(text)}
                  <button
                    className="remove-comment" onClick={_e => remove(id)}>
                    {ReasonReact.string({js|✖️|js})}
                  </button>
                </p>
              </div>
            )
          |> List.toArray
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
