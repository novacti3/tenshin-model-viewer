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
    "libs/glfw/include"
    "libs/glad/include"
    "libs/glm/"
    "libs/Dear ImGui/"
    "./src/"
)

list(APPEND SOURCES
    # external sources
    "libs/glad/src/glad.c"
    "libs/Dear ImGui/imgui_demo.cpp"
    "libs/Dear ImGui/imgui_draw.cpp"
    "libs/Dear ImGui/imgui_tables.cpp"
    "libs/Dear ImGui/imgui_widgets.cpp"
    "libs/Dear ImGui/imgui.cpp"
    "libs/Dear ImGui/backends/imgui_impl_opengl3.cpp"
    "libs/Dear ImGui/backends/imgui_impl_glfw.cpp"
    
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
    "src/core/ui_manager.cpp"
    "src/core/window.cpp"
    "src/core/input.cpp"
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