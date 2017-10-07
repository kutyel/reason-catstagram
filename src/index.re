[%bs.raw {|require('./styles/style.css')|}];

external register_service_worker : unit => unit =
  "default" [@@bs.module "./registerServiceWorker"];

ReactDOMRe.renderToElementWithId <App message="Catstagram" /> "root";

register_service_worker ();
