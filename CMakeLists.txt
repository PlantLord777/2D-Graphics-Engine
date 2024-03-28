cmake_minimum_required(VERSION 3.10)

project(Ratworld  LANGUAGES CXX CSharp )

add_library(RatGraphics SHARED 
    graphics.cpp
    )

set(CMAKE_CSharp_FLAGS "/langversion:latest")
include(CSharpUtilities)

add_subdirectory(glfw3)
add_subdirectory(glew)


add_executable(Ratworld main.cs )

#set_target_properties(Ratworld PROPERTIES
 #   DOTNET_TARGET_FRAMEWORK_VERSION "v4.6.1")

LIST(APPEND VS_DOTNET_REFERENCES "Microsoft.CSharp")
LIST(APPEND VS_DOTNET_REFERENCES "PresentationCore")
LIST(APPEND VS_DOTNET_REFERENCES "PresentationFramework")
LIST(APPEND VS_DOTNET_REFERENCES "System")
LIST(APPEND VS_DOTNET_REFERENCES "System.Xaml")
LIST(APPEND VS_DOTNET_REFERENCES "System.Xml")
LIST(APPEND VS_DOTNET_REFERENCES "System.Xml.Linq")
LIST(APPEND VS_DOTNET_REFERENCES "WindowsBase")

set_target_properties(Ratworld PROPERTIES
    VS_DOTNET_REFERENCES "${VS_DOTNET_REFERENCES}")

target_include_directories(RatGraphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw3/include)

target_include_directories(RatGraphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)

target_link_libraries(RatGraphics glfw libglew_static)

target_link_libraries(Ratworld SYSTEM)

    