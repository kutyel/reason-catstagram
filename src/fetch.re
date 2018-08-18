type response;

[@bs.val] external fetch: string => Repromise.t(response) = "fetch";
[@bs.send] external text: response => Repromise.t(string) = "";
[@bs.send] external json: response => Repromise.t(Js.Json.t) = "";