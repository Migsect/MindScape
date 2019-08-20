# CMakeLists for MindScape executable 

cmake_minimum_required (VERSION 3.8)

add_executable(MindScape_Main 
  "source/main.cpp"
)

target_link_libraries(MindScape_Main PRIVATE MindScape)

# Include own header files
target_include_directories(MindScape_Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)