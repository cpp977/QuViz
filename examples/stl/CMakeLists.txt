add_executable(createSTL stl.cpp ${SRCFILES})

# add_dependencies(
#         createSTL
#         gifanim)

target_link_libraries(
        createSTL
        project_options
        project_warnings
        igl::core
		vivid
        hdf5
        hdf5_cpp)
