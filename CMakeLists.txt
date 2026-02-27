cmake_minimum_required(VERSION 3.30)
project(LearnOpenGL2026Bilibili)

set(CMAKE_CXX_STANDARD 20)
#add_compile_definitions(DEBUG)
find_package(glfw3 3.3 REQUIRED)
add_subdirectory(thirdparty/glad)
add_subdirectory(wrapper)
add_subdirectory(application)

add_executable(LearnOpenGL2026Bilibili main.cpp
        wrapper/checkerror.cpp
        wrapper/include/checkerror.h
        application/application.cpp
        application/include/application.h)


target_link_libraries(LearnOpenGL2026Bilibili glfw glad wrapper lwapp)
target_compile_definitions(wrapper PUBLIC DEBUG)
