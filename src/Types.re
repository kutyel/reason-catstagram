type route =
  | Default
  | Detail(string);

type caption = {
  text: string /* description */
};

type likes = {
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
  likes,
  user_has_liked: bool,
};

type load =
  | Loading
  | Error
  | Loaded(list(post));
