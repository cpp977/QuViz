add_subdirectory(colors)
add_subdirectory(molecules)

# Add your project files
file(GLOB SRCFILES "*.cpp"
                   "*.h"
                   "colors/*.h"
                   "molecules/*.h"
                   "molecules/*.cpp")
add_executable(${PROJECT_NAME} ${SRCFILES})
target_link_libraries(${PROJECT_NAME} igl::core igl::opengl_glfw igl::png igl::xml igl::opengl_glfw_imgui)
