# thirdparty/glad/CMakeLists.txt

add_library(glad glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)