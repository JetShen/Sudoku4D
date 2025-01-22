include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

cmake_minimum_required(VERSION 3.10)
project(MiProyectoOpenGL)

set(CMAKE_C_STANDARD 99)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

# GLAD
include_directories(lib/glad/include)
file(GLOB GLAD_SOURCES "lib/glad/src/glad.c")

# exe
add_executable(MiProyecto src/main.c ${GLAD_SOURCES})
target_link_libraries(MiProyecto glfw)