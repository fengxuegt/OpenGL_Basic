//
// Created by fengxuegt on 2025/7/23.
//

#include "cameracontrol.h"

#include <iostream>
#include <ostream>

CameraControl::CameraControl() {
}

CameraControl::CameraControl(Camera *camera) {
    mCamera = camera;
}

CameraControl::~CameraControl() {
}

void CameraControl::update() {
    // 因为没有共性的操作，因此这个函数保持为空函数
}

void CameraControl::onMouse(int button, int action, float xPos, float yPos) {
    // 用于检测鼠标的键位哪个按下了
    bool pressed = action == GLFW_PRESS ? true : false;
    // 同时记录按下的时候，鼠标的位置在哪里
    if (pressed) {
        mCurrentX = xPos;
        mCurrentY = yPos;
        std::cout << mCurrentX << ", " << mCurrentY << std::endl;
    }

    // 更改鼠标键位的状态
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mLeftMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mRightMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mMiddleMouseDown = pressed;
            break;
    }
}

void CameraControl::onCursor(float xPos, float yPos) {
    // 没有共同操作
}

void CameraControl::onKey(int key, int scancode, int action, int mods) {
    // 过滤掉repeat的情况 , 这一点也很重要
    if (action == GLFW_REPEAT) {
        return;
    }
    bool pressed = action == GLFW_PRESS ? true : false;
    mKeyMap[key] = pressed;

}

void CameraControl::onScroll(double yOffset) {
    mCamera->scale(yOffset);
}

void CameraControl::setCamera(Camera *camera) {
    mCamera = camera;
}

void CameraControl::setSensitivity(float sensitivity) {
    mSensitivity = sensitivity;
}
