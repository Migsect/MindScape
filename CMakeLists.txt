cmake_minimum_required(VERSION 3.8)
project(Mindscape VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 17)


enable_testing()

# top project folder
set(MINDSCAPE_TOP_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

# project wide output directories
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(PT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

# add dependencies to cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PT_ROOT}/cmake/Modules)

# set postfix
if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX -d)
endif()

add_subdirectory("exe")
add_subdirectory("lib")