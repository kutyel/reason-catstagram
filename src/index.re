[%bs.raw {|require("./index.css")|}];

/* [@bs.module "./registerServiceWorker"] */
/* external register_service_worker : unit => unit = "default"; */

ReactDOMRe.renderToElementWithId(<App />, "root");

Js.log("hello world");

/* register_service_worker(); */