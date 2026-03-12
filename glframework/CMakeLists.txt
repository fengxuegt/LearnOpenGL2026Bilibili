add_library(glframework shader.cpp
        texture.cpp
        include/texture.h
        geometry.cpp
        include/geometry.h)
target_include_directories(glframework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(glframework glad glfw lwapp glm)