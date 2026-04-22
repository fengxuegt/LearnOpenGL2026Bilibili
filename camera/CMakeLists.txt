add_library(camera camera.cpp
        orthographiccamera.cpp
        perspectivecamera.cpp
        cameracontrol.cpp
        trackballcameracontrol.cpp
        include/trackballcameracontrol.h
        gamecameracontrol.cpp
        include/gamecameracontrol.h)
target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(camera glframework)