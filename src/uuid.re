let s4 = () =>
  floor((1. +. Random.float(1.)) *. float_of_int(0x10000))
  |> int_of_float
  |> Printf.sprintf("%x")
  |> Js.String.substr(~from=1);

let make = () =>
  s4()
  ++ s4()
  ++ "-"
  ++ s4()
  ++ "-"
  ++ s4()
  ++ "-"
  ++ s4()
  ++ "-"
  ++ s4()
  ++ s4()
  ++ s4();
