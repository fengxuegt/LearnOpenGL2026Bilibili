add_library(lwapp application.cpp
        assimpLoader.cpp)

target_include_directories(lwapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lwapp glad glfw glframework /opt/homebrew/lib/libassimp.dylib)