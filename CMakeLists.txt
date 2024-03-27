cmake_minimum_required(VERSION 3.10)
project(Ratworld)

find_package(OpenGL REQUIRED)
#find_library(GLFW REQUIRED)

add_executable(Ratworld rat.cpp)

#link_libraries(Ratworld glfw)

include_directories("${GLFW_SOURCE_DIR}")
add_library(OpenGL32 STATIC ${OPENGL_INCLUDE_DIRS} rat.cpp)

#add_subdirectory(OpenGL32)
add_subdirectory(glfw)

target_link_libraries(Ratworld PUBLIC  ${OPENGL_LIBRARIES} glfw)

target_include_directories(Ratworld PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/OpenGL")


    