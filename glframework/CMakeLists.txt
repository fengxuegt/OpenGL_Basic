# thirdparty/glad/CMakeLists.txt

find_package(glfw3 3.3 REQUIRED)
add_library(glframe shader.cpp texture.cpp)
target_include_directories(glframe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(glframe PUBLIC glad glfw wrapper glm)