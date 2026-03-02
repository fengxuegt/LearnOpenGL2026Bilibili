add_library(glframework shader.cpp)
target_include_directories(glframework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(glframework glad glfw)