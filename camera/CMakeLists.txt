add_library(camera camera.cpp
        orthographiccamera.cpp
        include/orthographiccamera.h
        perspectivecamera.cpp
        include/perspectivecamera.h)
target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(camera glframework)