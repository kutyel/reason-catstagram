open Types;
open ReactUpdate;

let token = [%raw "process.env.API_TOKEN"];

let appReducer = (action, state) =>
  switch (action) {
  | FetchPosts =>
    UpdateWithSideEffects(
      Loading,
      ({send}) => {
        Js.Promise.(
          Fetch.fetch(
            {j|https://api.instagram.com/v1/users/self/media/recent/?access_token=$token|j},
          )
          |> then_(Fetch.Response.json)
          |> then_(json =>
               json
               ->Post.decode
               ->(posts => send(FetchedPosts(posts)))
               ->resolve
             )
          |> catch(_e => resolve(send(FailedToFetch)))
          |> ignore
        );
        None;
      },
    )
  | FetchComments(mediaId) =>
    SideEffects(
      ({send}) => {
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
          |> catch(_e => resolve(send(FailedToFetch)))
          |> ignore
        );
        None;
      },
    )
  | Like(post, like) =>
    Update(
      switch (state) {
      | Loaded(route, posts) =>
        Loaded(
          route,
          List.map(posts, p =>
            p == post
              ? {
                ...p,
                user_has_liked: like,
                likes: {
                  count: p.likes.count + (like ? 1 : (-1)),
                },
              }
              : p
          ),
        )
      | _ => state
      },
    )
  | FailedToFetch => Update(Error)
  | FetchedPosts(posts) =>
    Update(
      Loaded(
        Route.urlToRoute(ReasonReactRouter.dangerouslyGetInitialUrl()),
        posts,
      ),
    )
  | FetchedComments(postId, comments) =>
    switch (state) {
    | Loaded(route, posts) =>
      Update(
        Loaded(
          route,
          posts->List.map(p => p.id == postId ? {...p, comments} : p),
        ),
      )
    | _ => NoUpdate
    }
  | AddComment(postId, author, comment) =>
    switch (state) {
    | Loaded(route, posts) =>
      Update(
        Loaded(
          route,
          posts->List.map(p =>
            p.id == postId
              ? {
                ...p,
                comments: [
                  {
                    id: Uuid.make(),
                    created_time: Js.Date.make()->Js.Date.toISOString,
                    from: {
                      username: author,
                    },
                    text: comment,
                  },
                  ...p.comments,
                ],
              }
              : p
          ),
        ),
      )
    | _ => NoUpdate
    }
  | DeleteComment(postId, commentId) =>
    switch (state) {
    | Loaded(route, posts) =>
      Update(
        Loaded(
          route,
          posts->List.map(p =>
            p.id == postId
              ? {
                ...p,
                comments: p.comments->List.keep(c => c.id != commentId),
              }
              : p
          ),
        ),
      )
    | _ => NoUpdate
    }
  | ChangeRoute(route) =>
    UpdateWithSideEffects(
      switch (state) {
      | Loaded(_, posts) => Loaded(route, posts)
      | _ => state
      },
      ({state, send}) => {
        switch (state) {
        | Loaded(Detail(id), posts) =>
          switch (posts->List.getBy(p => p.id == id)) {
          | Some({Post.comments: []}) => send(FetchComments(id))
          | _ => ()
          }
        | _ => ()
        };
        None;
      },
    )
  };
