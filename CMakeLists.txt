cmake_minimum_required(VERSION 3.11)
project(Sudoku4DOpenGL)

set(GLFW_DIR ${CMAKE_SOURCE_DIR}/lib/glfw)
add_subdirectory(${GLFW_DIR} ${CMAKE_BINARY_DIR}/glfw)

include_directories(${CMAKE_SOURCE_DIR}/lib/glad/include)
file(GLOB GLAD_SOURCES ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)

include_directories(${CMAKE_SOURCE_DIR}/lib/glm)

set(SOURCES src/main.cpp)
add_executable(Sudoku4D ${SOURCES} ${GLAD_SOURCES})

target_link_libraries(Sudoku4D glfw)

if (WIN32)
    target_link_libraries(Sudoku4D opengl32)
else()
    target_link_libraries(Sudoku4D GL)
endif()