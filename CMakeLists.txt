cmake_minimum_required(VERSION 3.10)

project(Ratworld  LANGUAGES CXX CSharp )

add_library(RatGraphics SHARED 
    graphics.cpp
    )

set(CMAKE_CSharp_FLAGS "/langversion:latest")

add_subdirectory(glfw3)
add_subdirectory(glew)


add_executable(Ratworld main.cs )

target_include_directories(RatGraphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw3/include)

target_include_directories(RatGraphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)

target_link_libraries(RatGraphics glfw libglew_static)

    