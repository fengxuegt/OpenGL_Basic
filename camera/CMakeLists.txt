
file(GLOB CAMERA_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(camera ${CAMERA_SRC})
target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(camera PUBLIC glframe)