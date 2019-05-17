open Types;

[@react.component]
let make = (~post, ~dispatch, ~navigate) => {
  let {
    Post.id,
    images: {standard_resolution: {url}},
    likes: {count},
    user_has_liked,
    caption: {text},
    comments,
    num_comments: {count: num_comments},
  } = post;
  let likes = string_of_int(count);
  let length = List.length(comments);
  <figure className="grid-figure">
    <div className="grid-photo-wrap">
      <a href={j|/view/$id|j} onClick={navigate(Route.Detail(id))}>
        <img src=url alt=id className="grid-photo" />
      </a>
    </div>
    <figcaption>
      <p> {React.string(text)} </p>
      <div className="control-buttons">
        <button
          onClick={_e => dispatch(Like(post, !user_has_liked))}
          className={user_has_liked ? "liked" : ""}>
          {React.string({j|♥ $likes|j})}
        </button>
        <a
          className="button"
          href={j|/view/$id|j}
          onClick={navigate(Detail(id))}>
          <span className="comment-count">
            <span className="speech-bubble" />
            {React.string(string_of_int(length == 0 ? num_comments : length))}
          </span>
        </a>
      </div>
    </figcaption>
  </figure>;
};
