[@react.component]
let make = (~name: string, ~isDone: bool, ~id: string) => {
  let onChange = _event => {
    Db.updateTaskStatus(~id=id, ~status=true);
  };

  let onDeleteTask = _event => {
    Db.deleteTask(~id=id);
  };

  <div className="task-item">
    <Ui.CheckBox checked={isDone} onChange label={name}/>
    <span className="task-item-delete" onClick={onDeleteTask}>{"x"->React.string}</span>
  </div>
};