cmake_minimum_required(VERSION 3.11)
project(Sudoku4D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/lib/glfw)
add_subdirectory(${GLFW_DIR})

# GLAD
include_directories(${CMAKE_SOURCE_DIR}/lib/glad/include)
file(GLOB GLAD_SOURCES ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)

# GLM
include_directories(${CMAKE_SOURCE_DIR}/lib/glm)

# Sources
set(SOURCES
    src/main.cpp
    src/camera.cpp
    src/model.cpp
    src/shader.cpp
    src/sudokucube.cpp 
    src/utils.cpp
)

add_executable(Sudoku4D ${SOURCES} ${GLAD_SOURCES})

target_link_libraries(Sudoku4D glfw)

if (WIN32)
    target_link_libraries(Sudoku4D opengl32)
else()
    target_link_libraries(Sudoku4D GL)
endif()