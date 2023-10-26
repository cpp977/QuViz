cmake_minimum_required(VERSION 3.20)
project(QuViz)

include(cmake/StandardProjectSettings.cmake)

include(cmake/PreventInSourceBuilds.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(QUVIZ_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS ${QUVIZ_DIR})

option(USE_LIBCXX "Use libc++ from llvm." OFF)
if(NOT CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
 if(USE_LIBCXX)
  message( FATAL_ERROR "It is only possible to use libc++ in combination with clang")
 endif()
endif()

include(libigl)

# libigl
igl_include(glfw)
igl_include(embree)
igl_include(imgui)
igl_include(opengl)
igl_include(stb)
#igl_include(predicates)
#igl_include(xml)
#igl_include(copyleft cgal)
#igl_include(copyleft comiso)
#igl_include(copyleft core)
#igl_include(copyleft cork)
#igl_include(copyleft tetgen)
#igl_include(restricted matlab)
#igl_include(restricted mosek)
#igl_include(restricted triangle)

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

find_package(Git REQUIRED)
find_package(Boost REQUIRED)

find_package(nlohmann_json REQUIRED)
find_package(glm REQUIRED)

include(cmake/addGitLibs.cmake)

option(QUVIZ_BUILD_EXAMPLES     "Build examples"    ON)

add_subdirectory(src)

if (QUVIZ_BUILD_EXAMPLES)
add_subdirectory(examples)
endif()
