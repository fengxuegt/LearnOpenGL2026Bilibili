add_library(glframework shader.cpp
        texture.cpp
        geometry.cpp
        object.cpp
        material/material.cpp
        material/phongmaterial.cpp
        mesh.cpp
        light/light.cpp
        light/directionallight.cpp
        light/ambientlight.cpp
        renderer/renderer.cpp
        scene.cpp
        include/scene.h
        material/whitematerial.cpp
        material/whitematerial.h
        material/screenplanematerial.cpp
        material/screenplanematerial.h
        framebuffer.cpp
        framebuffer.h
        material/cubematerial.cpp
        material/cubematerial.h)
target_include_directories(glframework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(glframework glad glfw lwapp glm camera)