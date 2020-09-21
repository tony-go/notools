type state = {user: option(Db.user)};

type action =
  | Fetch(Db.user);

let initialState = { user: None };

let reducer = (_state, action) =>
  switch (action) {
  | Fetch(user) => { user: Some({ email: user.email, displayName: user.displayName, uid: user.uid }) }
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let read_user = (user: Js.Nullable.t(Db.user)) => {
    switch (Js.Nullable.toOption(user)) {
      | Some(user) => dispatch(Fetch(user))
      | None => Js.log("no user")
    }
    
  };

  let logOut = _event => {
    Db.logOut();
  }

  let logIn = _event => {
    Db.popGoogleAuth();
  }

  React.useEffect1(() => {
    Db.onAuthStateChanged(read_user);
    None;
  }, [||]);

  <div className="app">
    <div className="block">
      {switch (state.user) {
          | Some(user) => {
            <div className="header">
          <h1>
            {("Yo " ++ user.displayName ++ " !") |> React.string}
          </h1>
          <Ui.Button onClick={logOut} label="Off"/>
        </div>
          }
          | None => <Ui.Button onClick={logIn} label="Login"/>
        }
      }
      <Router user={state.user}/>
    </div>
  </div>
};
