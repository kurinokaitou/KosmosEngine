set(KOSMOS_ENGINE_NAME "KosmosEngine")

# Vulkan SDK设置
if(NOT DEFINED ENV{VULKAN_SDK})
	message(FATAL_ERROR "VULKAN_SDK not defined!")
endif()
set(VULKAN_SDK $ENV{VULKAN_SDK})
set(VK_SDK_INCLUDE ${VULKAN_SDK}/Include)
set(VK_SDK_LIB ${VULKAN_SDK}/Lib/vulkan-1.lib)

# vcpkg安装的glm和glfw3引入包
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
# find_package(PThreads4W CONFIG REQUIRED)

# 将源代码添加到此项目的可执行文件
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR} "include/*.h")
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})
add_library(${KOSMOS_ENGINE_NAME} STATIC ${SOURCE_FILES})

# 链接到库文件
target_link_libraries(${KOSMOS_ENGINE_NAME} PUBLIC glm::glm)
target_link_libraries(${KOSMOS_ENGINE_NAME} PUBLIC fmt::fmt)
target_link_libraries(${KOSMOS_ENGINE_NAME} PUBLIC tinyobjloader::tinyobjloader)
target_link_libraries(${KOSMOS_ENGINE_NAME} PUBLIC imgui::imgui)
# target_link_libraries(${KOSMOS_ENGINE_NAME} PUBLIC PThreads4W::PThreads4W)

target_link_libraries(${KOSMOS_ENGINE_NAME} PRIVATE glfw)
target_link_libraries(${KOSMOS_ENGINE_NAME} PRIVATE ${VK_SDK_LIB})
# 添加预编译头
target_compile_definitions(${KOSMOS_ENGINE_NAME} 
    PUBLIC
        GLFW_INCLUDE_VULKAN
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        STB_IMAGE_IMPLEMENTATION
        TINYOBJLOADER_IMPLEMENTATION
        GLM_ENABLE_EXPERIMENTAL
)

# set_target_properties(${KOSMOS_ENGINE_NAME} PROPERTIES
# COMPILE_FLAGS "-pthread"
# LINK_FLAGS "-pthread")
# 添加包含目录
target_include_directories(${KOSMOS_ENGINE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${KOSMOS_ENGINE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/vendor)
target_include_directories(${KOSMOS_ENGINE_NAME} PUBLIC ${VK_SDK_INCLUDE})


# 编译着色器
set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
file(GLOB SHADER_FILES CONFIGURE_DEPENDS "${SHADER_DIR}/*.vert"
                                                 "${SHADER_DIR}/*.frag"
                                                 "${SHADER_DIR}/*.comp"
                                                 "${SHADER_DIR}/*.geom"
                                                 "${SHADER_DIR}/*.tesc"
                                                 "${SHADER_DIR}/*.tese"
                                                 "${SHADER_DIR}/*.mesh"
                                                 "${SHADER_DIR}/*.task"
                                                 "${SHADER_DIR}/*.rgen"
                                                 "${SHADER_DIR}/*.rchit"
                                                 "${SHADER_DIR}/*.rmiss"
                                                 "${SHADER_DIR}/*.rcall")

include(${CMAKE_SOURCE_DIR}/cmake/CompileShaders.cmake)

source_group("shaders" FILES ${SHADER_FILES})
set(SHADER_INCLUDE_DIR ${SHADER_DIR}/include)
set(SHADER_TARGET_NAME "KosmosShaderPrecompile")
compile_shader(${SHADER_TARGET_NAME} "${SHADER_FILES}" "${SHADER_INCLUDE_DIR}")

add_dependencies(${KOSMOS_ENGINE_NAME} ${SHADER_TARGET_NAME})

target_include_directories(${KOSMOS_ENGINE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/generated/cpp)