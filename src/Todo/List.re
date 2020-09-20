type todos = array(Types.todo);

type action =
  | SetTodos(todos)
  | FetchTodos;

type state = {
  todos: todos,
  isLoading: bool
};

let initialState = { todos: [||], isLoading: false };

let reducer = (state, action) => {
  switch (action) {
    | SetTodos(todos) => { todos: todos, isLoading: false }
    | FetchTodos => { ...state, isLoading: true}
  }
};

[@react.component]
let make = (~user: Db.user) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let (todoName, setTodoName) = React.useState(() => "");
  let (todoDescription, setTodoDescription) = React.useState(() => "");

  let onClick = _event => Db.addTodo(todoName, todoDescription, user.uid);
  let handleNavigate = id => _event => ReasonReactRouter.push("/todos/" ++ id);

  let read_todos = data => {
    dispatch(SetTodos(data));
  };

  React.useEffect1(() => {
    dispatch(FetchTodos);
    Db.getTodos(user.uid, read_todos);
    None;
  }, [|user|]);


  <div>
    <h2>{"Create a new todo"->React.string}</h2>
    <div className="todo-form">
      <Ui.Box direction="row" gap="medium">
        <Ui.TextInput
          placeholder="Todo name"
          value={todoName}
          onChange={event => {
            let value = ReactEvent.Form.target(event)##value;
            setTodoName(_ => value);
          }}
        />
        <Ui.TextInput
          placeholder="Description"
          value={todoDescription}
          onChange={event => {
            let value = ReactEvent.Form.target(event)##value;
            setTodoDescription(_ => value);
          }}
        />
        <Ui.Button label="+" onClick/>
      </Ui.Box>
    </div>
    <h2>{"Your todos:"->React.string}</h2>
    <div className="todo-list">
      {state.todos ->Belt.Array.map(todo => <div onClick={handleNavigate(todo.id)} className="todo-item" key={todo.name}>{("- " ++ todo.name)->React.string}</div>) -> React.array}
    </div>
  </div>
};