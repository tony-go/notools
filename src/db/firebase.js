const firebase = require("firebase/app");
require('firebase/auth');
require('firebase/database');

const { v4: uuid } = require('uuid');
const config = require('../../firebase.config.json');

const fb = firebase.initializeApp(config);

function popGoogleAuth() {
  const provider = new firebase.auth.GoogleAuthProvider();

  fb.auth()
    .signInWithPopup(provider)
    .then(function () {
      console.log('logged!');
    })
    .catch(function (error) {
      console.error(error);
    });
}

function onAuthStateChanged(fn) {
  fb.auth().onAuthStateChanged(fn);
}

function logOut() {
  fb.auth().signOut();
}

function addTodo(name, description, userId) {
  if (!userId) {
    throw new Error('You should provide an ID');
  }
  const id = uuid();
  fb.database().ref('todos/' + id).set({
    name, description, userId
  }).then(() => {
    console.log(`todo ${id} created`);
  });
}

function getTodos(userId, fn) {
  return fb.database().ref('todos/').orderByChild('userId').equalTo(userId).on('value', (snapShot) => {
    fn(Object.entries(snapShot.val() || {}).map(([key, value])=> ({ ...value, id: key})))
  })
}

function getTodo(todoId, callBack) {
  return fb.database().ref('todos/' + todoId).on('value', (snapShot) => {
    callBack(snapShot.val())
  })
}

function addTask(name, todoId) {
  if (!todoId) {
    throw new Error('Provide an id asshole!')
  }
  const id = uuid();
  fb.database().ref('tasks/' + id).set({
    name, todoId, isDone: false
  }).then(() => {
    console.log(`todo ${id} created`);
  });
}

function getTasks(todoId, callBack) {
  return fb.database().ref('tasks/').orderByChild('todoId').equalTo(todoId).on('value', (snapShot) => {
    callBack(Object.entries(snapShot.val() || {}).map(([key, value])=> ({ ...value, id: key})))
  })
}

function updateTaskStatus(taskId, status) {
  return fb.database().ref().update({ ['tasks/' + taskId + '/isDone']: status })
}

function deleteTask(taskId) {
  return fb.database().ref('tasks/' + taskId).remove();
}

module.exports = {
  // auth
  popGoogleAuth,
  onAuthStateChanged,
  logOut,
  // todo
  addTodo,
  getTodos,
  getTodo,
  // task
  addTask,
  getTasks,
  updateTaskStatus,
  deleteTask
};
