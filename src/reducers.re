open Types;

let token = [%raw "process.env.API_TOKEN"];

let f = (action, state) =>
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
                 |> Post.decode
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
                 |> Comment.decode
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
        Route.urlToRoute(ReasonReact.Router.dangerouslyGetInitialUrl()),
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
  | DeleteComment(postId, commentId) =>
    switch (state) {
    | Loaded(route, posts) =>
      ReasonReact.Update(
        Loaded(
          route,
          posts
          ->List.map(p =>
              p.id == postId ?
                {
                  ...p,
                  comments: p.comments->List.keep(c => c.id != commentId),
                } :
                p
            ),
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
            let post = posts->List.getBy(p => p.id === id);
            switch (post) {
            | Some({Post.comments: []}) => send(FetchComments(id))
            | _ => ()
            };
          | _ => ()
          }
      ),
    )
  };
