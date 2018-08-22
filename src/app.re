open Types;

type state = {
  load,
  activeRoute: route,
};

type action =
  | CatsFetch
  | CatsFailedToFetch
  | CatsFetched(list(post))
  | ChangeRoute(route);

let component = ReasonReact.reducerComponent("App");

let token = [%raw "process.env.API_TOKEN"];
let urlToRoute = url =>
  switch (ReasonReact.Router.(url.path)) {
  | ["view", postId] => Detail(postId)
  | _ => Default
  };

let make = _children => {
  ...component,
  initialState: () => {
    load: Loading,
    activeRoute: urlToRoute(ReasonReact.Router.dangerouslyGetInitialUrl()),
  },
  didMount: self => {
    let watcher =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(urlToRoute(url)))
      );
    self.send(CatsFetch);
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcher));
  },
  reducer: (action, state) =>
    switch (action) {
    | CatsFetch =>
      ReasonReact.UpdateWithSideEffects(
        {...state, load: Loading},
        (
          self =>
            Js.Promise.(
              Fetch.fetch(
                "https://api.instagram.com/v1/users/self/media/recent/?access_token="
                ++ token,
              )
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> Decode.posts
                   |> (cats => self.send(CatsFetched(cats)))
                   |> resolve
                 )
              |> catch(_err => resolve(self.send(CatsFailedToFetch)))
              |> ignore
            )
        ),
      )
    | CatsFailedToFetch => ReasonReact.Update({...state, load: Error})
    | CatsFetched(cats) =>
      ReasonReact.Update({...state, load: Loaded(cats)})
    | ChangeRoute(activeRoute) => ReasonReact.Update({...state, activeRoute})
    },
  render: ({state: {load, activeRoute}}) =>
    <div>
      <h1> <a href="/"> {ReasonReact.string("Catstagram")} </a> </h1>
      {
        switch (load, activeRoute) {
        | (Error, _) =>
          <div> {ReasonReact.string("An error occurred! :(")} </div>
        | (Loading, _) => <Spinner />
        | (Loaded(posts), Default) => <Grid posts />
        | (Loaded(posts), Detail(postId)) => <Single posts postId />
        }
      }
    </div>,
};
