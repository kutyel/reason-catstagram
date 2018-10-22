module NodeFetch = {
  type response;

  [@bs.send] external text: response => Js.Promise.t(string) = "";

  type fetch = (. string) => Js.Promise.t(response);

  [@bs.module "node-fetch"] external fetch: fetch = "default";
};

let token: option(string) =
  Js.Nullable.toOption([%raw "process.env.API_TOKEN"]);

let buildUrl = token => {j|https://api.instagram.com/v1/users/self/media/recent/?access_token=$token|j};

switch (token) {
| Some(token) =>
  let url = buildUrl(token);
  Js.Promise.(
    NodeFetch.fetch(. url)
    |> then_(NodeFetch.text)
    |> then_(txt => {
         switch (Node.Fs.writeFileAsUtf8Sync("./posts.json", txt)) {
         | _ => Js.log("all posts written to ./posts.json!")
         | exception (Js.Exn.Error(e)) =>
           switch (Js.Exn.message(e)) {
           | Some(message) =>
             Js.log({j|Error writing the posts to posts.json: $message|j})
           | None =>
             Js.log(
               "An unknown error occurred while writing the posts to posts.json",
             )
           }
         };
         resolve();
       })
    |> catch(_ =>
         Js.log(
           "Something went wrong while fetching the posts from instagram",
         )
         |> resolve
       )
  )
  |> ignore;

| None => Js.log("Please supply your instagram token as API_TOKEN env var")
};
