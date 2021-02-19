if (LIBIGL_WITH_EMBREE AND LIBIGL_WITH_PNG)
add_subdirectory(gif)
add_subdirectory(png)
endif()

if (LIBIGL_WITH_OPENGL AND LIBIGL_WITH_OPENGL_GLFW AND LIBIGL_WITH_OPENGL_GLFW_IMGUI AND LIBIGL_WITH_PNG)
add_subdirectory(viewer)
endif()
