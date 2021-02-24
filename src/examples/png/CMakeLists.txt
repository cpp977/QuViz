add_executable(createPNG png.cpp ${SRCFILES})

add_dependencies(
        createPNG
        gifanim)

target_link_libraries(
        createPNG
        project_options
        project_warnings
        igl::core
        igl::embree
        igl::png
        vivid
        hdf5
        hdf5_cpp)
