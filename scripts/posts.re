/* minimal bindings to node_fetch */
module NodeFetch = {
  type response;
  /* gives you a function "text" that you can call on response */
  [@bs.send] external text: response => Js.Promise.t(string) = "";

  /* type fetch as an uncurried function */
  type fetch = (. string) => Js.Promise.t(response);

  /* binding to the default export of "node-fetch" */
  [@bs.module "node-fetch"] external fetch: fetch = "default";
};

/* Access the API_token from the node env and convert it to an option */
let token: option(string) =
  Js.Nullable.toOption([%raw "process.env.API_TOKEN"]);

/* helper to build the posts instagram api url */
let buildUrl = token => {j|https://api.instagram.com/v1/users/self/media/recent/?access_token=$token|j};

/* if we have a token, fetch the posts & write them in a file */
switch (token) {
| Some(token) =>
  let url = buildUrl(token);

  /* actually fetch the posts */
  Js.Promise.(
    NodeFetch.fetch(. url)
    |> then_(NodeFetch.text)
    |> then_(txt => {
				 /* write the fetched posts as text in "./posts.json" */
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
