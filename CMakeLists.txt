cmake_minimum_required(VERSION 3.15)
project(todo_backend)

set(CMAKE_CXX_STANDARD 17)

find_package(Crow CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(todo_app
  main.cpp
  todo.pb.cc
)

target_link_libraries(todo_app PRIVATE Crow::Crow protobuf::libprotobuf)