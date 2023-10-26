add_executable(viewer viewer.cpp ${SRCFILES})

add_dependencies(
        viewer
        gifanim)

target_link_libraries(
        viewer
        project_options
        project_warnings
        igl::core
		igl::opengl
		igl::glfw
		igl::imgui
		igl::stb
		vivid
        hdf5
        hdf5_cpp)
