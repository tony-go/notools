[@react.component]
let make = () => {
  let onClick = _event => Db.popGoogleAuth();
  <div onClick>{"Sign in !" |> React.string}</div>
}
