cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME "Kosmos")
project(${PROJECT_NAME} VERSION 0.0.1)

# 项目设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 在项目中启用宏定义头
add_definitions(
    -DGLFW_INCLUDE_VULKAN
    -DGLM_FORCE_RADIANS
    -DGLM_FORCE_DEPTH_ZERO_TO_ONE
    -DSTB_IMAGE_IMPLEMENTATION
    -DTINYOBJLOADER_IMPLEMENTATION
    -DGLM_ENABLE_EXPERIMENTAL
)
add_subdirectory(engine/runtime)
add_subdirectory(engine/editor)
