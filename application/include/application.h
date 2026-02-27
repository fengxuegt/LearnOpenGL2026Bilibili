//
// Created by fengxuegt on 2026/2/27.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#define LWAPP Application::getInstance()
class GLFWwindow;
using FrameBufferSizeCallBack = void (*)(int width, int height);
using KeyCallBack = void (*)(int key, int scancode, int action, int mods);

class Application {
public:
    void setFrameBufferSizeCallback(FrameBufferSizeCallBack callback) {mFrameBufferSizeCallBack = callback;}
    void setKeyCallBack(KeyCallBack callback){mKeyCallBack = callback;}
public:
    bool init(const char* title, int width, int height);
    bool update();
    bool destroy();


public:
    ~Application();
    static Application *getInstance();
private:
    Application();
    inline static Application *mInstance = nullptr;

private:
    GLFWwindow *mWindow;
    int mWidth, mHeight;
private:
    FrameBufferSizeCallBack mFrameBufferSizeCallBack;
    KeyCallBack mKeyCallBack;
    static void frameSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
};



#endif //APPLICATION_H
