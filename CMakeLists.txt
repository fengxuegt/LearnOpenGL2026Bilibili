cmake_minimum_required(VERSION 3.30)
project(LearnOpenGL2026Bilibili)

set(CMAKE_CXX_STANDARD 20)
#add_compile_definitions(DEBUG)
find_package(glfw3 3.3 REQUIRED)
add_subdirectory(thirdparty/glad)
add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)
add_subdirectory(thirdparty/glm)
add_subdirectory(camera)
add_executable(LearnOpenGL2026Bilibili main.cpp)


target_link_libraries(LearnOpenGL2026Bilibili glfw glad wrapper lwapp glframework glm camera)
target_compile_definitions(wrapper PUBLIC DEBUG)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})