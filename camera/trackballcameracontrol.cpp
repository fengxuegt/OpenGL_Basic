//
// Created by fengxuegt on 2025/7/23.
//

#include "trackballcameracontrol.h"

TrackBallCameraControl::TrackBallCameraControl() {
}

TrackBallCameraControl::~TrackBallCameraControl() {
}

void TrackBallCameraControl::onCursor(float xPos, float yPos) {
    if (mLeftMouseDown) { // 点击鼠标左键时
        float deltaX = (xPos - mCurrentX) * mSensitivity;
        float deltaY = (yPos - mCurrentY) * mSensitivity;
        pitch(-deltaY);
        yaw(-deltaX);
    } else if (mMiddleMouseDown) {
        float deltaX = (xPos - mCurrentX)  * mMoveSpeed;
        float deltaY = (yPos - mCurrentY) * mMoveSpeed;

        // 通过向量乘法
        // mCamera->mPosition += mCamera->mUp * deltaY;
        // mCamera->mPosition -= mCamera->mRight * deltaX;

        // 通过translate
        auto mat = glm::translate(glm::mat4(1.0f), mCamera->mUp * deltaY);
        mat = glm::translate(mat, -mCamera->mRight * deltaX);
        mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);

    }
    // 最终给xy赋值
    mCurrentX = xPos;
    mCurrentY = yPos;
}

void TrackBallCameraControl::onScroll(double yOffset) {
    mCamera->scale(yOffset * mScaleSpeed);
}

void TrackBallCameraControl::pitch(float angle) {
    // 上下点头
    // 这个旋转是绕着摄像机本身的right向量进行旋转，因此构建旋转矩阵
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
    mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}

void TrackBallCameraControl::yaw(float angle) {
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
    mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
    mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
}




