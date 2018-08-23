type caption = {
  text: string /* description */
};

type num = {
  count: int /* count */
};

type resolution = {
  url: string /* image */
};

type images = {standard_resolution: resolution};

type post = {
  id: string, /* id */
  caption,
  images,
  likes: num,
  comments: num,
  user_has_liked: bool,
};

type route =
  | Default
  | Detail(string);

type load =
  | Loading
  | Loaded
  | Error;
