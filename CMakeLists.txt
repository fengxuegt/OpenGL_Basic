cmake_minimum_required(VERSION 3.30)
project(OpenGL_Basic)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-DDEBUG)


# glfw配置
find_package(glfw3 3.3 REQUIRED)


# glad 配置
add_subdirectory(thirdparty/glad)
add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)


# 复制文件
file(GLOB ASSETS "./assets" )
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

add_executable(OpenGL_Basic main.cpp)
target_link_libraries(OpenGL_Basic glfw glad wrapper application glframe)
