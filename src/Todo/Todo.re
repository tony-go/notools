type action =
| SetTodo(Types.todo)
| SetTasks(array(Types.task))
| FecthTodo;

type state = {
  todo: Types.todo,
  tasks: option(array(Types.task)),
  isLoading: bool
};

let reducer = (state, action) => {
  switch (action) {
    | FecthTodo => { ...state, isLoading: true }
    | SetTodo(todo) => { ...state, todo: todo, isLoading: false }
    | SetTasks(tasks) => { ...state, tasks: Some(tasks), isLoading: false}
  }
};

let initialState = { todo: { name: "", description: "", id: "" }, isLoading: false, tasks: None};

[@react.component]
let make = (~id: string) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let (taskName, setTaskName) = React.useState(() => "");

  let set_todo = (todo) => {
    dispatch(SetTodo(todo));
  };

  let set_tasks = (tasks) => {
    dispatch(SetTasks(tasks));
  };

  let handleAddTask = _event => {
    if (String.length(taskName) > 0) {
      Db.addTask(taskName, id);
      setTaskName(_ => "");
    }
  };

  let handleKeyPress = event => {
    if (
      ReactEvent.Keyboard.key(event) == "Enter"
      && String.length(taskName) > 0
    ) {
      Db.addTask(taskName, id);
      setTaskName(_ => "");
    }
  };

  React.useEffect1(() => {
    dispatch(FecthTodo);
    Db.getTodo(id, set_todo);
    Db.getTasks(id, set_tasks);
    None;
  }, [||]);

  {state.isLoading == false
    ? <div onKeyPress={handleKeyPress}>
      <h2>
        {state.todo.name->React.string}
        {" - "->React.string}
        <span className="todo-description">{state.todo.description->React.string}</span>
      </h2>
      <Ui.Box direction="row" gap="medium">
        <Ui.TextInput
          autoFocus={true}
          placeholder="Task"
          value={taskName}
          onChange={event => {
            let value = ReactEvent.Form.target(event)##value;
            setTaskName(_ => value);
          }}
        />
        <Ui.Button label="+" onClick={handleAddTask}/>
      </Ui.Box>
      <div className="task-list">
      { switch (state.tasks) {
        | None => React.null
        | Some(tasks) => tasks -> Belt.Array.map(task =>
          <Task
            key={task.id}
            name={task.name}
            id={task.id}
            isDone={task.isDone}
          />
        ) -> React.array
      }}
      </div>
    </div>
    : <div>{"Loading ..."->React.string}</div>
  }
}