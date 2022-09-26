set(KOSMOS_ENV_TEST "EnvTest")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})
add_executable(${KOSMOS_ENV_TEST} "stb_image.h" "EnvTest.h" "EnvTest.cpp" )


target_link_libraries(${KOSMOS_ENV_TEST} PRIVATE glm::glm)
target_link_libraries(${KOSMOS_ENV_TEST} PRIVATE glfw)
target_link_libraries(${KOSMOS_ENV_TEST} PRIVATE Vulkan::Vulkan)
target_link_libraries(${KOSMOS_ENV_TEST} PRIVATE tinyobjloader::tinyobjloader)


target_include_directories(${KOSMOS_ENV_TEST} PRIVATE ${PROJECT_SOURCE_DIR}/include)


target_compile_definitions(${KOSMOS_ENV_TEST} 
    PUBLIC
        GLFW_INCLUDE_VULKAN
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        STB_IMAGE_IMPLEMENTATION
        TINYOBJLOADER_IMPLEMENTATION
        GLM_ENABLE_EXPERIMENTAL
)

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

include(CompileShaders)

source_group("shaders" FILES ${SHADER_FILES})
set(SHADER_INCLUDE_DIR ${SHADER_DIR}/include)
compile_shader(${KOSMOS_ENV_TEST}Precompile "${SHADER_FILES}" "${SHADER_INCLUDE_DIR}")

add_dependencies(${KOSMOS_ENV_TEST} ${KOSMOS_ENV_TEST}Precompile)

target_include_directories(${KOSMOS_ENV_TEST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/generated/cpp)