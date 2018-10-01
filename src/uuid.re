[@bs.send] external toString: (int, int) => string = "";

let s4 = () =>
  Js.Math.floor((1. +. Js.Math.random()) *. float_of_int(0x10000))
  ->toString(16)
  ->Js.String.substr(~from=1);

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
