add_executable(createGif gif.cpp ${SRCFILES})

add_dependencies(
        createGif
        gifanim)

target_link_libraries(
        createGif
        project_options
        project_warnings
        igl::core
        igl::embree
		igl::stb
		vivid
        hdf5
        hdf5_cpp)
