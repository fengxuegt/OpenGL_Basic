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
    return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}

void OrthographicCamera::scale(float deltaScale) {

}
