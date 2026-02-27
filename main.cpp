#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "checkerror.h"
#include "application.h"


void frameSizeCallback(int width, int height) {
    std::cout << width << " " << height << std::endl;
    glViewport(0, 0, width/2, height);
}

void keyCallBack(int key, int scancode, int action, int mods) {
    std::cout << key << " " << scancode << " " << action << " " << mods << std::endl;
}



int main() {
    if (!LWAPP->init("OpenGL basic", 800, 600)) {
        return -1;
    }
    LWAPP->setFrameBufferSizeCallback(frameSizeCallback);
    LWAPP->setKeyCallBack(keyCallBack);

    LWGLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));


    while (LWAPP->update()) {
        LWGLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    LWAPP->destroy();
    return 0;
}
