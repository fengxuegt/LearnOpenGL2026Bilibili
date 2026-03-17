//
// Created by fengxuegt on 2026/2/27.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#define LWAPP Application::getInstance()
class GLFWwindow;
using FrameBufferSizeCallBack = void (*)(int width, int height);
using KeyCallBack = void (*)(int key, int scancode, int action, int mods);
using MouseButtonCallBack = void (*)(int button, int action, int mods);
using CursorPositionCallBack = void (*) (double xpos, double ypos);
using ScrollCallBack = void (*) (double xoffset, double yoffset);

class Application {
public:
    void setFrameBufferSizeCallback(FrameBufferSizeCallBack callback) {mFrameBufferSizeCallBack = callback;}
    void setKeyCallBack(KeyCallBack callback){mKeyCallBack = callback;}
    void setMouseButtonCallBack(MouseButtonCallBack callback) {mMouseButtonCallBack = callback;}
    void setCursorPositionCallBack(CursorPositionCallBack callback) {mCursorPositionCallBack = callback;}
    void setScrollCallBack(ScrollCallBack callback) {mScrollCallBack = callback;}

    void getCurrentXYPosition(double *x, double *y);
    GLFWwindow* getWindow();


public:
    bool init(const char* title, int width, int height);
    bool update();
    bool destroy();

    int getWidth();
    int getHeight();


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
    MouseButtonCallBack mMouseButtonCallBack;
    CursorPositionCallBack mCursorPositionCallBack;
    ScrollCallBack mScrollCallBack;

    static void frameSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
};



#endif //APPLICATION_H
