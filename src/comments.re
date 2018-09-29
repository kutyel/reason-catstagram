let component = ReasonReact.statelessComponent("Comments");

let make = (~comments, ~send, ~postId, _children) => {
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
                    className="remove-comment"
                    onClick={_e => send(Types.DeleteComment(postId, id))}>
                    {ReasonReact.string({js|✖️|js})}
                  </button>
                </p>
              </div>
            )
          |> List.toArray
          |> ReasonReact.array
        }
      </div>
      <Form
        handleSubmit={
          (author, text) => send(AddComment(postId, author, text))
        }
      />
    </div>,
};
