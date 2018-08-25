module T = Types;

type state =
  | Error
  | Loading
  | Loaded(T.route, list(T.Post.t));

type action =
  | FetchPosts
  | FetchComments(string)
  | FailedToFetch
  | FetchedPosts(list(T.Post.t))
  | FetchedComments(list(T.Comment.t))
  | Like(T.Post.t, bool)
  | ChangeRoute(T.route);

let component = ReasonReact.reducerComponent("App");

let token = [%raw "process.env.API_TOKEN"];
let urlToRoute = url =>
  switch (ReasonReact.Router.(url.path)) {
  | ["view", postId] => T.Detail(postId)
  | _ => Base
  };

let make = _children => {
  ...component,
  initialState: () => Loading,
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
        Loading,
        (
          ({send}) =>
            Js.Promise.(
              Fetch.fetch(
                {j|https://api.instagram.com/v1/users/self/media/recent/?access_token=$token|j},
              )
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> T.Post.decodePosts
                   |> (posts => send(FetchedPosts(posts)))
                   |> resolve
                 )
              |> catch(_err => resolve(send(FailedToFetch)))
              |> ignore
            )
        ),
      )
    | FetchComments(mediaId) =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          ({send}) =>
            Js.Promise.(
              Fetch.fetch(
                {j|https://api.instagram.com/v1/media/$mediaId/comments?access_token=$token|j},
              )
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> T.Comment.decodeComments
                   |> (comments => send(FetchedComments(comments)))
                   |> resolve
                 )
              |> catch(_err => resolve(send(FailedToFetch)))
              |> ignore
            )
        ),
      )
    | Like(post, like) =>
      ReasonReact.Update(
        switch (state) {
        | Loaded(route, posts) =>
          Loaded(
            route,
            posts
            ->Belt.List.map(p =>
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
          )
        | _ => state
        },
      )
    | FailedToFetch => ReasonReact.Update(Error)
    | FetchedPosts(posts) =>
      ReasonReact.Update(
        Loaded(
          urlToRoute(ReasonReact.Router.dangerouslyGetInitialUrl()),
          posts,
        ),
      )
    | FetchedComments(comments) =>
      Js.log(comments);
      ReasonReact.NoUpdate;
    | ChangeRoute(route) =>
      ReasonReact.UpdateWithSideEffects(
        switch (state) {
        | Loaded(_, posts) => Loaded(route, posts)
        | _ => state
        },
        (
          self =>
            switch (route) {
            | Detail(id) => self.send(FetchComments(id))
            | _ => ()
            }
        ),
      )
    },
  render: ({state, send}) => {
    let onLink = id => send(ChangeRoute(id));
    let onLike = (post, like) => send(Like(post, like));
    <div>
      <h1> <a href="/"> {ReasonReact.string("Catstagram")} </a> </h1>
      {
        switch (state) {
        | Error => <Error />
        | Loading => <Spinner />
        | Loaded(route, posts) =>
          switch (route) {
          | Base => <Grid posts onLike onLink />
          | Detail(postId) => <Single posts postId onLike onLink />
          }
        }
      }
    </div>;
  },
};
