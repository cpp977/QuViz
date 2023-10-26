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

add_subdirectory(gif)
add_subdirectory(png)
add_subdirectory(stl)
add_subdirectory(viewer)
