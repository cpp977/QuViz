cmake_minimum_required(VERSION 3.1)
project(QuViz)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# libigl
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
option(LIBIGL_WITH_PNG               "Use png"            ON)
option(LIBIGL_WITH_XML               "Use xml"            ON)
option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGui"          ON)

find_package(LIBIGL REQUIRED QUIET)


add_subdirectory(src)
