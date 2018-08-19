type post = {
  id: string,
  image: string,
  count: option(int),
  description: string,
};

type route =
  | Default
  | Detail(string);
