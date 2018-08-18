[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo: string = "./logo.svg";

type state = {gifUrl: option(string)};

type action =
  | FetchCats
  | SaveCatsUrl(option(string));

let parseGiphyResponse = json =>
  switch (Js.Json.decodeObject(json)) {
  | Some(jsDict) =>
    switch (Js.Dict.get(jsDict, "data")) {
    | Some(data) =>
      switch (Js.Json.decodeObject(data)) {
      | Some(dataDict) =>
        switch (Js.Dict.get(dataDict, "image_url")) {
        | Some(jsonUrl) => Js.Json.decodeString(jsonUrl)
        | None => None
        }
      | None => None
      }
    | None => None
    }
  | None => None
  };

let fetchCats = cb =>
  Fetch.fetch(
    "https://api.giphy.com/v1/gifs/random?api_key=dc6zaTOxFJmzC&tag=cats",
  )
  |> Repromise.andThen(Fetch.json)
  |> Repromise.wait(json => {
       let catsUrl = parseGiphyResponse(json);
       cb(catsUrl);
     });

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {gifUrl: None},
  reducer: (action, _state) =>
    switch (action) {
    | FetchCats =>
      ReasonReact.SideEffects(
        (self => fetchCats(newCatUrl => self.send(SaveCatsUrl(newCatUrl)))),
      )

    | SaveCatsUrl(newCatsUrl) => ReasonReact.Update({gifUrl: newCatsUrl})
    },
  render: self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> {ReasonReact.string(message)} </h2>
      </div>
      <p className="App-intro">
        {ReasonReact.string("To get started, edit")}
        <code> {ReasonReact.string(" src/app.re ")} </code>
        {ReasonReact.string("and save to reload.")}
        <Link text="ReasonML" link=Hashtag />
      </p>
      <br />
      <br />
      <br />
      <br />
      <br />
      <br />
      <p>
        <button onClick={_ => self.send(FetchCats)}>
          {ReasonReact.string({js|Necesito más gatos!|js})}
        </button>
      </p>
      <p>
        {
          switch (self.state.gifUrl) {
          | Some(url) => <img src=url />
          | None => ReasonReact.string("Faltan gatos en este momento.")
          }
        }
      </p>
    </div>,
};
