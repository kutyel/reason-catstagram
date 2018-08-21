open Types;

module Decode = {
  let caption = json => Json.Decode.{text: json |> field("text", string)};
  let resolution = json => Json.Decode.{url: json |> field("url", string)};
  let likes = json => Json.Decode.{count: json |> field("count", int)};
  let images = json =>
    Json.Decode.{
      standard_resolution: json |> field("standard_resolution", resolution),
    };
  let post = json =>
    Json.Decode.{
      id: json |> field("id", string),
      caption: json |> field("caption", caption),
      images: json |> field("images", images),
      likes: json |> field("likes", likes),
    };
  let posts = json => Json.Decode.(json |> field("data", list(post)));
};
