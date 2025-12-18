<template>
  <div class="app">
    <h1>{{ title }}</h1>
  
    <input id="todo-input" v-model="newTask" @keyup.enter="addTodo" placeholder="Что нужно сделать?">
    <button @click="addTodo">Добавить</button>
  
    <ul>
      <li v-for="(todo, index) in todos" :key="index">
        <input type="checkbox" v-model="todo.done">
        <span :style="{ textDecoration: todo.done ? 'line-through' : 'none' }">
          {{ todo.text }}
        </span>
        <button @click="removeTodo(index)">x</button>
      </li>
    </ul>
  </div>
</template>

<script lang="js" setup>
import { ref, onMounted } from 'vue'

const API_URL = 'http://127.0.0.1:18080/api/todos'
const title = ref('C++ + Vue To-Do')
const newTask = ref('')
const todos = ref([])

const fetchTodos = async () => {
const response = await fetch(API_URL);
  const buffer = await response.arrayBuffer();

  const root = await protobuf.load("/todo.proto");
  const TodoList = root.lookupType("TodoList");

  const message = TodoList.decode(new Uint8Array(buffer));
  todos.value = TodoList.toObject(message, { arrays: true }).items;
}

const addTodo = async () => {
  if (!newTask.value.trim()) return
  
  await fetch(API_URL, {
    method: 'POST',
    body: JSON.stringify({ text: newTask.value }),
    headers: { 'Content-Type': 'application/json' }
  })
  
  newTask.value = ''
  fetchTodos()
}

onMounted(fetchTodos)
</script>
