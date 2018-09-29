type form = {
  author: string,
  comment: string,
};

type state = {form};

type action =
  | HandleChange(form);

let component = ReasonReact.reducerComponent("Form");

let make = (~handleSubmit, _children) => {
  ...component,
  initialState: () => {
    form: {
      author: "",
      comment: "",
    },
  },
  reducer: (action, state) =>
    switch (action) {
    | HandleChange(form) => ReasonReact.Update({...state, form}) /* TODO: strange warning "with" */
    },
  render: ({state: {form}, send}) =>
    <form className="comment-form">
      <input
        type_="text"
        placeholder="author"
        value={form.author}
        onChange={
          event => {
            let nextForm = {
              ...form,
              author: event->ReactEvent.Form.target##value,
            };
            send(HandleChange(nextForm));
          }
        }
      />
      <input
        type_="text"
        placeholder="comment"
        value={form.comment}
        onChange={
          event => {
            let nextForm = {
              ...form,
              comment: event->ReactEvent.Form.target##value,
            };
            send(HandleChange(nextForm));
          }
        }
      />
      <input
        type_="submit"
        hidden=true
        onSubmit={
          e => {
            ReactEvent.Form.preventDefault(e);
            handleSubmit(form.author, form.comment);
          }
        }
      />
    </form>,
};
