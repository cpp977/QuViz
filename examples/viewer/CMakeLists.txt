add_executable(viewer viewer.cpp ${SRCFILES})

add_dependencies(
        viewer
        gifanim)

target_link_libraries(
        viewer
        project_options
        project_warnings
        igl::core
        igl::opengl_glfw
        igl::png
        igl::opengl_glfw_imgui
        vivid
        hdf5
        hdf5_cpp)
