let component = ReasonReact.statelessComponent("Post");

open Types;

let make = (~post, _children) => {
  ...component,
  render: _self => {
    let {id, image, count, description} = post;
    let count =
      switch (count) {
      | None => 0
      | Some(num) => num
      };
    <figure className="grid-figure">
      <div className="grid-photo-wrap">
        <a href={j|/view/$id|j}>
          <img src=image alt=id className="grid-photo" />
        </a>
      </div>
      <figcaption>
        <p> {ReasonReact.string(description)} </p>
        <div className="control-buttons">
          <button className="liked">
            {ReasonReact.string("&hearts; " ++ string_of_int(count))}
          </button>
          <a className="button" href={j|/view/$id|j}>
            <span className="comment-count">
              <span className="speech-bubble" />
              {ReasonReact.string(string_of_int(count))}
            </span>
          </a>
        </div>
      </figcaption>
    </figure>;
  },
};