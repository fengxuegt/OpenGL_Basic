//
// Created by fengxuegt on 2025/7/11.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include <ostream>

class GLFWwindow;

#define LWAPP Application::getInstance()
using FrameBufferSizeCallback = void(*) (GLFWwindow* window, int width, int height);
using KeyCallBack = void(*) (GLFWwindow* window, int, int, int, int);
using MouseCallBack = void(*) (GLFWwindow*, int, int, int);
using CursorCallBack = void(*) (GLFWwindow*, double, double);
using ScrollCallBack = void(*) (GLFWwindow*, double, double);

class Application {
public:
    bool init(uint32_t width = 800, uint32_t height = 600);

    bool update();

    void destroy();

    static Application * getInstance();
    ~Application();
    uint32_t getWidth() const {
        return mWidth;
    };
    uint32_t getHeight() const {
        return mHeight;
    }
    void setFrameBufferSizeCallback(FrameBufferSizeCallback callback);
    void setKeyCallBack(KeyCallBack callback);
    void setMouseCallBack(MouseCallBack callback);
    void setCursorCallBack(CursorCallBack callback);
    void setScrollCallBack(ScrollCallBack callback);
private:
    FrameBufferSizeCallback mFrameBufferSizeCallback{nullptr}; // 成员变量
    KeyCallBack mKeyCallBack{nullptr};
    MouseCallBack mMouseCallBack{nullptr};
    CursorCallBack mCursorCallBack{nullptr};
    ScrollCallBack mScrollCallBack{nullptr};

private:
      Application();
      static Application *mInstance;

    uint32_t mWidth; // 宽
    uint32_t mHeight; // 长
    GLFWwindow *mWindow; // 保存的窗口对象

};



#endif //APPLICATION_H
