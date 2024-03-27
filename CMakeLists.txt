cmake_minimum_required(VERSION 3.10)

project(Ratworld)

add_subdirectory(glfw)
add_subdirectory(glew)


add_executable(Ratworld rat.cpp)

target_include_directories(Ratworld PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)

target_include_directories(Ratworld PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)

target_link_libraries(Ratworld glfw libglew_static)

    