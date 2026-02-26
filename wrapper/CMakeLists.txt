add_library(wrapper checkerror.cpp)
target_include_directories(wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(wrapper glad)

