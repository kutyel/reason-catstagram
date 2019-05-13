open Types;

[@react.component]
let make = () => {
  let (state, dispatch) =
    ReactUpdate.useReducer(Loading, Reducers.appReducer);

  React.useEffect0(() => {
    let watcher =
      ReasonReactRouter.watchUrl(url =>
        dispatch(ChangeRoute(Route.urlToRoute(url)))
      );
    dispatch(FetchPosts);
    Some(() => ReasonReactRouter.unwatchUrl(watcher));
  });

  let navigate = (route, e) => {
    ReactEvent.Mouse.preventDefault(e);
    ReasonReactRouter.push(Route.toUrl(route));
  };

  <>
    <h1>
      <a href="/" onClick={navigate(Base)}> {React.string("Catstagram")} </a>
    </h1>
    {switch (state) {
     | Error => <Error />
     | Loading => <Spinner />
     | Loaded(route, posts) =>
       switch (route) {
       | Base => <Grid posts dispatch navigate />
       | Detail(postId) => <Single posts postId dispatch navigate />
       }
     }}
  </>;
};
