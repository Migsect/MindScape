# CMakeLists for MindScape library

cmake_minimum_required (VERSION 3.8)
add_library(MindScape SHARED
  "include/MindScapeGame.h"
  "include/MindScape/Core/EventController.h"
  "include/MindScape/Core/TemplateRegion.h"
  "include/MindScape/Utils/DllUtils.h"
  
  "source/Core/EventController.cpp"
  "source/MindScapeGame.cpp"
)
set_target_properties(MindScape PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

# GameBackbone has these as public targets. This means that they are automatically
# added to the target_link_libraries for MindScape
# MindScape still needs to find the packages for GB to link against though.
find_package(SFML 2 COMPONENTS network audio graphics window system)
find_package(TGUI 0.8.2 REQUIRED)

find_package(GameBackbone 0.2.1 REQUIRED) 
target_link_libraries(MindScape PUBLIC GameBackbone) 

message("current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(MindScape PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")