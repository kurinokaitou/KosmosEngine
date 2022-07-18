cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME "Kosmos")
project(${PROJECT_NAME} VERSION 0.0.1)
# # 设置cmake工具链为vcpkg
# if(NOT DEFINED ENV{VCPKG_ROOT_PATH})
# 	message(FATAL_ERROR "VCPKG_ROOT_PATH not defined!")
# endif()
# set(VCPKG_PATH $ENV{VCPKG_ROOT_PATH})
# set(VCPKG_ROOT ${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake CACHE PATH "")
# set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})

# 项目设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(engine/runtime)