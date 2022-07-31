set(KOSMOS_ENV_TEST "EnvTest")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})
add_executable(${KOSMOS_ENV_TEST} "stb_image.h" "EnvTest.h" "EnvTest.cpp" )

# 链接到库文件
target_link_libraries(${KOSMOS_ENV_TEST} PRIVATE glm::glm)
target_link_libraries(${KOSMOS_ENV_TEST} PRIVATE glfw)
target_link_libraries(${KOSMOS_ENV_TEST} PRIVATE ${VK_SDK_LIB})
target_link_libraries(${KOSMOS_ENV_TEST} PRIVATE tinyobjloader::tinyobjloader)

# 添加包含目录
target_include_directories(${KOSMOS_ENV_TEST} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${KOSMOS_ENV_TEST} PRIVATE ${VK_SDK_INCLUDE})

# 添加预处理器宏
target_compile_definitions(${KOSMOS_ENV_TEST} 
    PUBLIC
        GLFW_INCLUDE_VULKAN
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        STB_IMAGE_IMPLEMENTATION
        TINYOBJLOADER_IMPLEMENTATION
        GLM_ENABLE_EXPERIMENTAL
)
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

include(${CMAKE_SOURCE_DIR}/cmake/compileShaders.cmake)

source_group("shaders" FILES ${SHADER_FILES})
set(SHADER_INCLUDE_DIR ${SHADER_DIR}/include)
compile_shader(${KOSMOS_ENV_TEST}Precompile "${SHADER_FILES}" "${SHADER_INCLUDE_DIR}")

add_dependencies(${KOSMOS_ENV_TEST} ${KOSMOS_ENV_TEST}Precompile)

target_include_directories(${KOSMOS_ENV_TEST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/generated/cpp)