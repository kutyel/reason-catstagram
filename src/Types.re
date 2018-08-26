type route =
  | Base
  | Detail(string);

let decode = (from, json) =>
  Json.Decode.(json |> field("data", list(from)));

module Caption = {
  type t = {
    text: string /* description */
  };
  let fromJson = json => Json.Decode.{text: json |> field("text", string)};
};

module Num = {
  type t = {
    count: int /* count */
  };
  let fromJson = json => Json.Decode.{count: json |> field("count", int)};
};

module Resolution = {
  type t = {
    url: string /* image */
  };
  let fromJson = json => Json.Decode.{url: json |> field("url", string)};
};

module Images = {
  type t = {standard_resolution: Resolution.t};
  let fromJson = json =>
    Json.Decode.{
      standard_resolution:
        json |> field("standard_resolution", Resolution.fromJson),
    };
};

module From = {
  type t = {username: string};
  let fromJson = json =>
    Json.Decode.{username: json |> field("username", string)};
};

module Comment = {
  type t = {
    id: string,
    from: From.t,
    text: string,
    created_time: string,
  };
  let fromJson = json =>
    Json.Decode.{
      id: json |> field("id", string),
      from: json |> field("from", From.fromJson),
      created_time: json |> field("created_time", string),
      text: json |> field("text", string),
    };
  let decode = decode(fromJson);
};

module Post = {
  type t = {
    id: string,
    caption: Caption.t,
    images: Images.t,
    likes: Num.t,
    num_comments: Num.t,
    user_has_liked: bool,
    comments: list(Comment.t),
  };
  let fromJson = json =>
    Json.Decode.{
      id: json |> field("id", string),
      caption: json |> field("caption", Caption.fromJson),
      images: json |> field("images", Images.fromJson),
      likes: json |> field("likes", Num.fromJson),
      num_comments: json |> field("comments", Num.fromJson),
      user_has_liked: json |> field("user_has_liked", bool),
      comments: [],
    };
  let decode = decode(fromJson);
};
