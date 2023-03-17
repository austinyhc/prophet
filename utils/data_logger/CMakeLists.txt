cmake_minimum_required(VERSION 2.8)

project(data_logger)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} "main.cpp" "main.h")

set(INCLUDE_DIRECTROIES
    ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/cxxopts
    ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/nlohmann
    ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/hsd)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTROIES})

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/deps/hsd/libhsd.so)
target_link_libraries(${PROJECT_NAME} pthread)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
