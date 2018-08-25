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

type from = {username: string};

type comment = {
  id: string,
  from,
  text: string,
  created_time: string,
};

type post = {
  id: string,
  caption,
  images,
  likes: num,
  num_comments: num,
  user_has_liked: bool,
  comments: list(comment),
};

type route =
  | Base
  | Detail(string);
