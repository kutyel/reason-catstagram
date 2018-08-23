open Types;
open Belt;

type state = {
  load,
  posts: list(post),
  activeRoute: route,
  comments: list(string),
};

type action =
  | FetchPosts
  /* | FetchComment(string) */
  | FailedToFetch
  | FetchedPosts(list(post))
  | FetchedComments(list(string))
  | Like(post, bool)
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
    posts: [],
    comments: [],
    load: Loading,
    activeRoute: urlToRoute(ReasonReact.Router.dangerouslyGetInitialUrl()),
  },
  didMount: self => {
    let watcher =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(urlToRoute(url)))
      );
    self.send(FetchPosts);
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcher));
  },
  reducer: (action, state) =>
    switch (action) {
    | FetchPosts =>
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
                   |> (posts => self.send(FetchedPosts(posts)))
                   |> resolve
                 )
              |> catch(_err => resolve(self.send(FailedToFetch)))
              |> ignore
            )
        ),
      )
    | Like(post, like) =>
      ReasonReact.Update({
        ...state,
        posts:
          List.map(state.posts, p =>
            p == post ?
              {
                ...p,
                user_has_liked: like,
                likes: {
                  count: p.likes.count + (like ? 1 : (-1)),
                },
              } :
              p
          ),
      })
    | FailedToFetch => ReasonReact.Update({...state, load: Error})
    | FetchedPosts(posts) =>
      ReasonReact.Update({...state, load: Loaded, posts})
    | FetchedComments(comments) =>
      ReasonReact.Update({...state, load: Loaded, comments})
    | ChangeRoute(activeRoute) => ReasonReact.Update({...state, activeRoute})
    },
  render: ({state: {load, posts, activeRoute}, send}) => {
    let onLike = (post, like) => send(Like(post, like));
    <div>
      <h1> <a href="/"> {ReasonReact.string("Catstagram")} </a> </h1>
      {
        switch (load, activeRoute) {
        | (Error, _) => <Error />
        | (Loading, _) => <Spinner />
        | (Loaded, Default) => <Grid posts onLike />
        | (Loaded, Detail(postId)) => <Single posts postId onLike />
        }
      }
    </div>;
  },
};
