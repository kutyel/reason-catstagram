let component = ReasonReact.statelessComponent("Post");

open Types;

let make = (~post, _children) => {
  ...component,
  render: _self => {
    let {
      id,
      images: {standard_resolution: {url}},
      likes: {count},
      caption: {text},
    } = post;
    <figure className="grid-figure">
      <div className="grid-photo-wrap">
        <a href={j|/view/$id|j}>
          <img src=url alt=id className="grid-photo" />
        </a>
      </div>
      <figcaption>
        <p> {ReasonReact.string(text)} </p>
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
