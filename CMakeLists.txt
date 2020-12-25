cmake_minimum_required(VERSION 3.15)

project(ModelViewer)

make_directory(build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<CONFIG>/)

add_subdirectory(libs/glfw ${ModelViewer_BINARY_DIR}/glfw)
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

list(APPEND INCLUDES
    # external includes
    libs/glfw/include
    libs/glad/include
    libs/glm/

    src/window.hpp
)

list(APPEND SOURCES
    # external sources
    libs/glad/src/glad.c

    src/window.cpp
)

add_executable(ModelViewer src/program.cpp)
# Change the executable's name and C language standard
set_target_properties(ModelViewer PROPERTIES OUTPUT_NAME ModelViewer CXX_STANDARD 17)
target_link_libraries(ModelViewer glfw opengl32.lib)
target_include_directories(ModelViewer PRIVATE ${INCLUDES})
target_sources(ModelViewer PRIVATE ${SOURCES})