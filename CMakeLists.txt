cmake_minimum_required(VERSION 3.15)

# Fail compilation if on Mac because it's not supported
if(APPLE)
    message(FATAL_ERROR "Mac is not a supported platform. Cancelling compilation")
endif()

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

    # General stuff
    "src/core/log.hpp"
    "src/core/types.hpp"
    "src/core/utils.hpp"

    # Rendering
    "src/rendering/shader.hpp"

    # Primitives
    "src/rendering/primitives/primitive.hpp"
    "src/rendering/primitives/quad.hpp"
    "src/rendering/primitives/cube.hpp"

    # Components
    "src/components/transform.hpp"
    "src/components/camera.hpp"
    "src/components/primitive_renderer.hpp"

    # Core engine stuff
    "src/core/resource_manager.hpp"
    "src/core/window.hpp"
    "src/core/app.hpp"
)

list(APPEND SOURCES
    # external sources
    "libs/glad/src/glad.c"
    
    # Rendering
    "src/rendering/shader.cpp"

    # Primitives
    "src/rendering/primitives/quad.cpp"
    "src/rendering/primitives/cube.cpp"
    
    # Components
    "src/components/primitive_renderer.cpp"
    "src/components/camera.cpp"
    
    # Core engine stuff
    "src/core/resource_manager.cpp"
    "src/core/window.cpp"
    "src/core/app.cpp"
)

add_executable(ModelViewer src/main.cpp)
# Change the executable's name and C language standard
set_target_properties(ModelViewer PROPERTIES OUTPUT_NAME ModelViewer CXX_STANDARD 17)
target_link_libraries(ModelViewer glfw)

# Link the proper OpenGL lib based on the platform
if(WIN32)
    target_link_libraries(ModelViewer opengl32.lib)
elseif(UNIX)
    target_link_libraries(ModelViewer libGL.so)
endif()

target_include_directories(ModelViewer PRIVATE ${INCLUDES})
target_sources(ModelViewer PRIVATE ${SOURCES})