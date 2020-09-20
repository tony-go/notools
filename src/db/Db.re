type user = { email: string, displayName: string, uid: string };

[@bs.module "./firebase.js"]
external onAuthStateChanged : ((user) => unit) => unit = "onAuthStateChanged";

[@bs.module "./firebase.js"]
external popGoogleAuth: unit => unit = "popGoogleAuth";

[@bs.module "./firebase.js"]
external addTodo: (string, string, string) => unit = "addTodo";

[@bs.module "./firebase.js"]
external getTodos: (string, (array(Types.todo) => unit)) => unit = "getTodos";

[@bs.module "./firebase.js"]
external getTodo: (string, (Types.todo => unit)) => unit = "getTodo";

[@bs.module "./firebase.js"]
external addTask: (string, string) => unit = "addTask";

[@bs.module "./firebase.js"]
external getTasks: (string, (array(Types.task) => unit)) => unit = "getTasks";

[@bs.module "./firebase.js"]
external updateTaskStatus: (~id: string, ~status: bool) => unit = "updateTaskStatus";

[@bs.module "./firebase.js"]
external deleteTask: (~id: string) => unit = "deleteTask";