cmake_minimum_required(VERSION 3.10.0)
project(cpp_stl_containers VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
add_subdirectory(vector)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
add_executable(cpp_stl_containers main.cpp vector/Test_Vector.cpp)

target_link_libraries(cpp_stl_containers PRIVATE vector)