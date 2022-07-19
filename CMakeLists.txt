cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME "Kosmos")
project(${PROJECT_NAME} VERSION 0.0.1)

# 项目设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(engine/runtime)
add_subdirectory(engine/editor)
