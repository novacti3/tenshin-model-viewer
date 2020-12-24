cmake_minimum_required(VERSION 3.15)

project(projectName)

make_directory(build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<CONFIG>/)

add_subdirectory(libs/glfw ${projectName_BINARY_DIR}/glfw)
add_subdirectory(libs/freetype ${projectName_BINARY_DIR}/freetype)

list(APPEND INCLUDES
    # external includes
    libs/glfw/include
    libs/glad/include
    libs/glm/
    libs/freetype/include

    # engine includes

    # game includes
)

list(APPEND SOURCES
    # external sources
    libs/glad/src/glad.c

    # engine sources

    # game sources
)

add_executable(projectName src/program.cpp)
# Change the executable's name and C++ language standard
set_target_properties(projectName PROPERTIES OUTPUT_NAME projectName CXX_STANDARD 17)
target_link_libraries(projectName glfw opengl32.lib freetype)
target_include_directories(projectName PRIVATE ${INCLUDES})
target_sources(projectName PRIVATE ${SOURCES})