cmake_minimum_required(VERSION 3.15)

project(projectName)

make_directory(build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<CONFIG>/)

add_subdirectory(libs/glfw ${projectName_BINARY_DIR}/glfw)

list(APPEND INCLUDES
    # external includes
    libs/glfw/include
    libs/glad/include
    libs/glm/

    # engine includes

    # game includes
)

list(APPEND SOURCES
    # external sources
    libs/glad/src/glad.c

    # engine sources

    # game sources
)

add_executable(projectName src/program.c)
# Change the executable's name and C++ language standard
set_target_properties(projectName PROPERTIES OUTPUT_NAME projectName CXX_STANDARD 17)
target_link_libraries(projectName glfw opengl32.lib)
target_include_directories(projectName PRIVATE ${INCLUDES})
target_sources(projectName PRIVATE ${SOURCES})