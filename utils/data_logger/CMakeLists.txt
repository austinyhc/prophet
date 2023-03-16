cmake_minimum_required(VERSION 2.8)

project(datalogger)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(${PROJECT_NAME} "main.cpp" "main.h")

set(INCLUDE_DIRECTROIES
    ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/nlohmann
    ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/hs_datalog)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTROIES})

# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/nlohmann/)
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/hs_datalog/)

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/deps/hs_datalog/libhs_datalog.so)
target_link_libraries(${PROJECT_NAME} pthread)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
