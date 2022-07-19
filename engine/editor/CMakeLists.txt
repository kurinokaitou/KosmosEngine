set(KOSMOS_EDITOR_NAME "KosmosEditor")
set(KOSMOS_ENGINE_NAME "KosmosEngine")
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR} "include/*.h")
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${KOSMOS_EDITOR_NAME} ${SOURCE_FILES})

target_link_libraries(${KOSMOS_EDITOR_NAME} PRIVATE ${KOSMOS_ENGINE_NAME})
# target_include_directories(${KOSMOS_EDITOR_NAME} PRIVATE ../runtime/include)
target_include_directories(${KOSMOS_EDITOR_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_dependencies(${KOSMOS_EDITOR_NAME} ${KOSMOS_ENGINE_NAME})
