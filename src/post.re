let component = ReasonReact.statelessComponent("Post");

open Types;

let make = (~post, ~onLike, ~onLink, _children) => {
  ...component,
  render: _self => {
    let {
      Post.id,
      images: {standard_resolution: {url}},
      likes: {count},
      user_has_liked,
      caption: {text},
      num_comments: {count: num_comments},
    } = post;
    let likes = string_of_int(count);
    let onClick = e => {
      ReactEvent.Mouse.preventDefault(e);
      onLink(Detail(id));
    };
    <figure className="grid-figure">
      <div className="grid-photo-wrap">
        <a href={j|/view/$id|j} onClick>
          <img src=url alt=id className="grid-photo" />
        </a>
      </div>
      <figcaption>
        <p> {ReasonReact.string(text)} </p>
        <div className="control-buttons">
          <button
            onClick={_e => onLike(post, !user_has_liked)}
            className={user_has_liked ? "liked" : ""}>
            {ReasonReact.string({j|♥ $likes|j})}
          </button>
          <a className="button" href={j|/view/$id|j} onClick>
            <span className="comment-count">
              <span className="speech-bubble" />
              {ReasonReact.string(string_of_int(num_comments))}
            </span>
          </a>
        </div>
      </figcaption>
    </figure>;
  },
};
