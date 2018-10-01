let toHex = x => {
  let rec loop = (acc, x) => {
    let division = x /. 16.;
    let result = floor(division);
    let remainder = (division -. result) *. 16.;
    let stringRemainder = remainder->int_of_float->string_of_int;
    result === 0. ?
      String.concat("", [stringRemainder, ...acc]) :
      loop([stringRemainder, ...acc], result);
  };
  loop([], x);
};

let s4 = () =>
  floor((1. +. Random.float(1.)) *. float_of_int(0x10000))
  |> toHex
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
