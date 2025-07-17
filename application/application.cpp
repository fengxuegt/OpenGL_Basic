//
// Created by fengxuegt on 2025/7/11.
//

#include "application.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

Application * Application::mInstance = nullptr;

bool Application::init(uint32_t width, uint32_t height) {
    mWidth = width;
    mHeight = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 应该是苹果需要这条
    mWindow = glfwCreateWindow(mWidth, mHeight, "Hello World!", NULL, NULL);
    if (mWindow == NULL) {
        return false;
    }
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, mFrameBufferSizeCallback);
    glfwSetKeyCallback(mWindow, mKeyCallBack);

    // glad load function pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;

}

bool Application::update() {
    if (glfwWindowShouldClose(mWindow)) {
        return false;
    }
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
    return true;
}

void Application::destroy() {
    glfwTerminate();
}

Application *Application::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new Application();
    }
    return mInstance;
}

void Application::setFrameBufferSizeCallback(FrameBufferSizeCallback callback) {
    mFrameBufferSizeCallback = callback;
}

void Application::setKeyCallBack(KeyCallBack callback) {
    mKeyCallBack = callback;
}

Application::Application() {

}
Application::~Application() {

}



