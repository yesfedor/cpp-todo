cmake_minimum_required(VERSION 3.15)
project(todo_backend)

set(CMAKE_CXX_STANDARD 17)

find_package(Crow CONFIG REQUIRED)

add_executable(todo_app main.cpp)

target_link_libraries(todo_app PRIVATE Crow::Crow)