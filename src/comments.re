[@react.component]
let make = (~comments, ~dispatch, ~postId) =>
  <div className="comments">
    <div className="comments-list">
      {comments->List.map(({Types.Comment.id, text, from: {username}}) =>
         <div className="comment" key=id>
           <p>
             <strong> {React.string(username)} </strong>
             {React.string(text)}
             <button
               className="remove-comment"
               onClick={_e => dispatch(Types.DeleteComment(postId, id))}>
               {React.string({js|✖️|js})}
             </button>
           </p>
         </div>
       )
       |> List.toArray
       |> React.array}
    </div>
    <Form
      handleSubmit={(author, text) =>
        dispatch(AddComment(postId, author, text))
      }
    />
  </div>;
