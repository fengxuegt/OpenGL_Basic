//
// Created by fengxuegt on 2025/7/22.
//

#include "orthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) {
    mLeft = left;
    mRight = right;
    mBottom = bottom;
    mTop = top;
    mNear = near;
    mFar = far;
}

OrthographicCamera::~OrthographicCamera() {
}

glm::mat4 OrthographicCamera::getProjectionMatrix() {
    float deltaScale = std::pow(2.0f, mScale);
    return glm::ortho(mLeft * deltaScale, mRight * deltaScale, mBottom * deltaScale, mTop * deltaScale, mNear, mFar);
}

void OrthographicCamera::scale(float deltaScale) {
    mScale += deltaScale;
}
