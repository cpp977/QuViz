add_subdirectory(molecules)
add_subdirectory(shapes)
add_subdirectory(lattices)
add_subdirectory(util)
add_subdirectory(render)
add_subdirectory(fonts)
add_subdirectory(IO)

include_directories(${GIFANIM_INCLUDE_DIR} ${QUVIZ_DIR}/src)

#"*.h"
#                   "molecules/*.h"

file(GLOB SRCFILES 
                   "molecules/*.cpp"
                   "shapes/*.cpp"
                   "lattices/*.cpp"
                   "fonts/*.cpp"
                   "render/*.cpp"
                   )
                   
if (QUVIZ_BUILD_EXAMPLES)
add_subdirectory(examples)
endif()
