cmake_minimum_required(VERSION 3.1)
project(QuViz)

include(cmake/StandardProjectSettings.cmake)

include(cmake/PreventInSourceBuilds.cmake)

#set(CMAKE_CXX_FLAGS -stdlib=libc++)
#set(MAKE_EXE_LINKER_FLAGS "-stdlib=libc++")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(QUVIZ_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS ${QUVIZ_DIR})

option(USE_LIBCXX "Use libc++ from llvm." OFF)
if(NOT CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
 if(USE_LIBCXX)
  message( FATAL_ERROR "It is only possible to use libc++ in combination with clang")
 endif()
endif()

# libigl
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
option(LIBIGL_WITH_EMBREE            "Use Embree"         ON)
option(LIBIGL_WITH_PNG               "Use png"            ON)
option(LIBIGL_WITH_XML               "Use xml"            OFF)
option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGui"          ON)
option(LIBIGL_WITH_STL               "Use stl"            ON)

find_package(LIBIGL REQUIRED QUIET)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

# include compiler options from cmake/CompilerOptions.cmake
include(cmake/CompilerOptions.cmake)
set_project_options(project_options)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

#git is required to clone libraries used from github/gitlab
find_package(Git REQUIRED)
find_package(Boost REQUIRED)

set( CMAKE_PREFIX_PATH "/home/user/__LIBS__/vivid/build/;/home/user/__LIBS__/vivid/dependencies/json" )

find_package(vivid REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(glm REQUIRED)

include(cmake/addGitLibs.cmake)

option(QUVIZ_BUILD_EXAMPLES     "Build examples"    ON)

add_subdirectory(src)

if (QUVIZ_BUILD_EXAMPLES)
add_subdirectory(examples)
endif()
