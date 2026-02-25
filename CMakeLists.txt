cmake_minimum_required(VERSION 3.30)
project(LearnOpenGL2026Bilibili)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
add_subdirectory(thirdparty/glad)

add_executable(LearnOpenGL2026Bilibili main.cpp)


target_link_libraries(LearnOpenGL2026Bilibili glfw glad)