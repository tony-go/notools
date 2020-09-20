[@react.component]
let make = (~user: Db.user) => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
    | ["todos"] => <List user={user}/>
    | ["todos", id] => <Todo id={id}/>
    | ["signIn"] => <SignIn />
    | [] => <List user={user}/>
    | _ => <div>{"Not Found" -> React.string}</div>
  };
}