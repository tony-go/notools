[@react.component]
let make = (~user: option(Db.user)) => {
  let url = ReasonReactRouter.useUrl();

  switch (user) {
    | Some(user) => {
      switch (url.path) {
        | ["todos"] => <List user={user}/>
        | ["todos", id] => <Todo id={id}/>
        | ["signIn"] => <SignIn />
        | [] => <List user={user}/>
        | _ => <div>{"Not Found" -> React.string}</div>
      };
    }
    | None => React.null
  };

  
}