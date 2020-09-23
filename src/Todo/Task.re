[@react.component]
let make = (~name: string, ~isDone: bool, ~id: string) => {
  let onChange = event => {
    let value = ReactEvent.Form.target(event)##checked;
    Js.log(value);
    Db.updateTaskStatus(~id=id, ~status=value);
  };

  let onDeleteTask = _event => {
    Db.deleteTask(~id=id);
  };

  <div className="task-item">
    <Ui.CheckBox checked={isDone} onChange label={name}/>
    <span className="task-item-delete" onClick={onDeleteTask}>{"x"->React.string}</span>
  </div>
};
