module T = Types;

type state =
  | Error
  | Loading
  | Loaded(T.Route.t, list(T.Post.t));

type action =
  | FetchPosts
  | FetchComments(string)
  | FailedToFetch
  | FetchedPosts(list(T.Post.t))
  | FetchedComments(string, list(T.Comment.t))
  | Like(T.Post.t, bool)
  | ChangeRoute(T.Route.t);

let component = ReasonReact.reducerComponent("App");

let token = [%raw "process.env.API_TOKEN"];

let make = _children => {
  ...component,
  initialState: () => Loading,
  didMount: self => {
    let watcher =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(T.Route.urlToRoute(url)))
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
                   |> T.Post.decode
                   |> (posts => send(FetchedPosts(posts)))
                   |> resolve
                 )
              |> catch(_err => resolve(send(FailedToFetch)))
              |> ignore
            )
        ),
      )
    | FetchComments(mediaId) =>
      ReasonReact.SideEffects(
        (
          ({send}) =>
            Js.Promise.(
              Fetch.fetch(
                {j|https://api.instagram.com/v1/media/$mediaId/comments?access_token=$token|j},
              )
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> T.Comment.decode
                   |> (comments => send(FetchedComments(mediaId, comments)))
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
            List.map(posts, p =>
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
          T.Route.urlToRoute(ReasonReact.Router.dangerouslyGetInitialUrl()),
          posts,
        ),
      )
    | FetchedComments(postId, comments) =>
      switch (state) {
      | Loaded(route, posts) =>
        ReasonReact.Update(
          Loaded(
            route,
            posts->List.map(p => p.id == postId ? {...p, comments} : p),
          ),
        )
      | _ => ReasonReact.NoUpdate
      }
    | ChangeRoute(route) =>
      ReasonReact.UpdateWithSideEffects(
        switch (state) {
        | Loaded(_, posts) => Loaded(route, posts)
        | _ => state
        },
        (
          ({state, send}) =>
            switch (state) {
            | Loaded(Detail(id), posts) =>
              let p = posts->List.getBy(p => p.id === id);
              switch (p) {
              | Some({T.Post.comments: []}) => send(FetchComments(id))
              | _ => ()
              };
            | _ => ()
            }
        ),
      )
    },
  render: ({state, send}) => {
    let navigate = (route, e) => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReact.Router.push(T.Route.toUrl(route));
    };
    let onLike = (post, like) => send(Like(post, like));
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
          | Base => <Grid posts onLike navigate />
          | Detail(postId) => <Single posts postId onLike navigate />
          }
        }
      }
    </div>;
  },
};
