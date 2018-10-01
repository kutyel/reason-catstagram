type state = {
  author: string,
  comment: string,
};

type action =
  | ClearForm
  | ChangeAuthor(string)
  | ChangeComment(string);

let component = ReasonReact.reducerComponent("Form");

let make = (~handleSubmit, _children) => {
  ...component,
  initialState: () => {author: "", comment: ""},
  reducer: (action, state) =>
    switch (action) {
    | ClearForm => ReasonReact.Update({author: "", comment: ""})
    | ChangeAuthor(author) => ReasonReact.Update({...state, author})
    | ChangeComment(comment) => ReasonReact.Update({...state, comment})
    },
  render: ({state: {author, comment}, send}) =>
    <form
      className="comment-form"
      onSubmit={
        e => {
          ReactEvent.Form.preventDefault(e);
          handleSubmit(author, comment);
          send(ClearForm);
        }
      }>
      <input
        type_="text"
        placeholder="author"
        value=author
        onChange={e => send(ChangeAuthor(e->ReactEvent.Form.target##value))}
      />
      <input
        type_="text"
        placeholder="comment"
        value=comment
        onChange={e => send(ChangeComment(e->ReactEvent.Form.target##value))}
      />
      <input type_="submit" hidden=true />
    </form>,
};
