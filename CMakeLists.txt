cmake_minimum_required(VERSION 3.10)
project(Sudoku4DOpenGL)

# Configura GLFW
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/lib/glfw)
add_subdirectory(${GLFW_DIR} ${CMAKE_BINARY_DIR}/glfw)

# Configura GLAD
include_directories(${CMAKE_SOURCE_DIR}/lib/glad/include)
file(GLOB GLAD_SOURCES ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)

# Configura GLM
include_directories(${CMAKE_SOURCE_DIR}/lib/glm)

# Configura el ejecutable
set(SOURCES src/main.cpp)
add_executable(Sudoku4D ${SOURCES} ${GLAD_SOURCES})

# Enlaza GLFW
target_link_libraries(Sudoku4D glfw)

# Enlaza OpenGL
if (WIN32)
    target_link_libraries(Sudoku4D opengl32)
else()
    target_link_libraries(Sudoku4D GL)
endif()