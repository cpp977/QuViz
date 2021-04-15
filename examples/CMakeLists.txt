include_directories(${GIFANIM_INCLUDE_DIR} ${QUVIZ_DIR}/src)

file(GLOB SRCFILES
                   "../src/util/*.cpp"
                   "../src/IO/*.cpp"
                   "../src/shapes/*.cpp"
                   "../src/lattices/*.cpp"
                   "../src/molecules/*.cpp"
                   "../src/fonts/*.cpp"
                   "../src/render/*.cpp"
                   )

if (LIBIGL_WITH_EMBREE AND LIBIGL_WITH_PNG)
add_subdirectory(gif)
add_subdirectory(png)
endif()

if (LIBIGL_WITH_EMBREE AND LIBIGL_WITH_PNG)
add_subdirectory(stl)
endif()

if (LIBIGL_WITH_OPENGL AND LIBIGL_WITH_OPENGL_GLFW AND LIBIGL_WITH_OPENGL_GLFW_IMGUI AND LIBIGL_WITH_PNG)
add_subdirectory(viewer)
endif()
