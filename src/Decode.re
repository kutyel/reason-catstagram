open Types;

let caption = json => Json.Decode.{text: json |> field("text", string)};
let resolution = json => Json.Decode.{url: json |> field("url", string)};
let num = json => Json.Decode.{count: json |> field("count", int)};
let images = json =>
  Json.Decode.{
    standard_resolution: json |> field("standard_resolution", resolution),
  };
let from = json => Json.Decode.{username: json |> field("username", string)};
let post = json =>
  Json.Decode.{
    id: json |> field("id", string),
    caption: json |> field("caption", caption),
    images: json |> field("images", images),
    likes: json |> field("likes", num),
    comments: json |> field("comments", num),
    user_has_liked: json |> field("user_has_liked", bool),
  };
let comment = json =>
  Json.Decode.{
    id: json |> field("id", string),
    from: json |> field("from", from),
    created_time: json |> field("created_time", string),
    text: json |> field("text", string),
  };
let posts = json => Json.Decode.(json |> field("data", list(post)));
let comments = json => Json.Decode.(json |> field("data", list(comment)));
