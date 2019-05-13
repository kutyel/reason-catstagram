type state = {
  author: string,
  comment: string,
};

type action =
  | ClearForm
  | ChangeAuthor(string)
  | ChangeComment(string);

[@react.component]
let make = (~handleSubmit) => {
  let ({author, comment}, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ClearForm => {author: "", comment: ""}
        | ChangeAuthor(author) => {...state, author}
        | ChangeComment(comment) => {...state, comment}
        },
      {author: "", comment: ""},
    );

  <form
    className="comment-form"
    onSubmit={e => {
      e->ReactEvent.Form.preventDefault;
      handleSubmit(author, comment);
      dispatch(ClearForm);
    }}>
    <input
      type_="text"
      placeholder="author"
      value=author
      onChange={e =>
        dispatch(ChangeAuthor(e->ReactEvent.Form.target##value))
      }
    />
    <input
      type_="text"
      placeholder="comment"
      value=comment
      onChange={e =>
        dispatch(ChangeComment(e->ReactEvent.Form.target##value))
      }
    />
    <input type_="submit" hidden=true />
  </form>;
};
