type post = {
  id: string,
  image: string,
  count: option(int),
  description: string,
};

type load =
  | Loading
  | Error
  | Loaded(list(post));

type route =
  | Default
  | Detail(string);
