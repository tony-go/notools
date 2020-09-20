type state = {user: Db.user};

type action =
  | Fetch(Db.user);

let initialState = { user: { email: "", displayName: "", uid: "" } };

let reducer = (_state, action) =>
  switch (action) {
  | Fetch(user) => { user: { email: user.email, displayName: user.displayName, uid: user.uid } }
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let read_user = (user: Db.user) => {
    dispatch(Fetch(user))
  };

  React.useEffect1(() => {
    Db.onAuthStateChanged(read_user);
    None;
  }, [||]);

  let shouldDisplayName = String.length(state.user.displayName) > 0;

  <div className="app">
    <div className="block">
      <div className="header">
        <h1>
          {(shouldDisplayName ? ("Yo " ++ state.user.displayName ++ " !") : "Chargement...") |> React.string}
        </h1>
      </div>
      <Router user={state.user}/>
    </div>
  </div>
};
