//
// Created by fengxuegt on 2025/7/22.
//

#include "perspectiveCamera.h"

#include <iostream>
#include <ostream>

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far) {
    mFov = fov;
    mAspect = aspect;
    mNear = near;
    mFar = far;
}

PerspectiveCamera::PerspectiveCamera() {
}

PerspectiveCamera::~PerspectiveCamera() {
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(mFov), mAspect, mNear, mFar);
}

void PerspectiveCamera::scale(float deltaScale) {
    std::cout << "PerspectiveCamera::scale" << std::endl;
    glm::vec3 front = glm::cross(mUp, mRight);
    mPosition += front * deltaScale;
}
