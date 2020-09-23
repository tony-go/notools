type state = {user: option(Db.user), isLoading: bool};

type action =
  | Fetching
  | Fetched(Db.user)
  | Init;

let initialState = { user: None, isLoading: false };

let reducer = (_state, action) =>
  switch (action) {
  | Fetched(user) => { user: Some({ email: user.email, displayName: user.displayName, uid: user.uid }), isLoading: false }
  | Init => { user: None, isLoading: false }
  | Fetching => { user: None, isLoading: true }
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let read_user = (user: Js.Nullable.t(Db.user)) => {
    switch (Js.Nullable.toOption(user)) {
      | Some(user) => dispatch(Fetched(user))
      | None => dispatch(Init)
      
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
    dispatch(Fetching)
    None;
  }, [||]);

  <div className="app">
    <div className="block">
      <div className="header">
        {switch (state.user) {
            | Some(user) => {
              <>
                <h1>
                  {("Hi " ++ user.displayName) |> React.string}
                </h1>
                <Ui.Button onClick={logOut} label="Off"/>
              </>
            }
            | None => state.isLoading ? <div>{"Loading ..."->React.string}</div> : <Ui.Button onClick={logIn} label="Login"/>
          }
        }
      </div>
      <Router user={state.user}/>
    </div>
  </div>
};
