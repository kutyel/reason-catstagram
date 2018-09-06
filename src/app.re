open Types;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => Loading,
  didMount: self => {
    let watcher =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(Route.urlToRoute(url)))
      );
    self.send(FetchPosts);
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcher));
  },
  reducer: Reducers.f,
  render: ({state, send}) => {
    let navigate = (route, e) => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReact.Router.push(Route.toUrl(route));
    };
    <div>
      <h1>
        <a href="/" onClick={navigate(Base)}>
          {ReasonReact.string("Catstagram")}
        </a>
      </h1>
      {
        switch (state) {
        | Error => <Error />
        | Loading => <Spinner />
        | Loaded(route, posts) =>
          switch (route) {
          | Base => <Grid posts send navigate />
          | Detail(postId) => <Single posts postId send navigate />
          }
        }
      }
    </div>;
  },
};
