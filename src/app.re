[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo: string = "./logo.svg";

open Types;

type state = {
  posts: list(post),
  activeRoute: route,
};

type action =
  | FetchCats
  | ChangeRoute(route);

let component = ReasonReact.reducerComponent("App");

let urlToRoute = url =>
  switch (ReasonReact.Router.(url.path)) {
  | ["view", postId] => Detail(postId)
  | _ => Default
  };

let make = _children => {
  ...component,
  initialState: () => {
    posts: [
      {
        id: "1",
        count: Some(0),
        image: "https://instagram.falc2-2.fna.fbcdn.net/vp/144b6ac07f994a13a7f85fda32f9b8d5/5C160DBC/t51.2885-15/e35/33630499_1741098989349139_7374174821044715520_n.jpg",
        description: "cat",
      },
    ],
    activeRoute: {
      /* See https://reasonml.github.io/reason-react/docs/en/router#directly-get-a-route */
      let url = ReasonReact.Router.dangerouslyGetInitialUrl();
      urlToRoute(url);
    },
  },
  didMount: self => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(urlToRoute(url)))
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  reducer: (action, state) =>
    switch (action) {
    | ChangeRoute(activeRoute) =>
      ReasonReact.Update({...state, activeRoute})
    | FetchCats => ReasonReact.NoUpdate
    },
  render: ({state: {posts, activeRoute}}) => {
    let posts =
      posts
      ->Belt.List.map(post => <Post post />)
      ->Belt.List.toArray
      ->ReasonReact.array;
    <div className="App">
      {
        switch (activeRoute) {
        | Default => posts
        | Detail(route) => ReasonReact.string("route:" ++ route)
        }
      }
    </div>;
  },
};