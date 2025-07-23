//
// Created by fengxuegt on 2025/7/22.
//

#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov, float aspect, float near, float far);

    PerspectiveCamera();

    ~PerspectiveCamera();
    glm::mat4 getProjectionMatrix() override;
    void scale(float deltaScale) override;
public:
    float mFov = 0.0f;
    float mAspect = 0.0f;
    float mNear = 0.0f;
    float mFar = 0.0f;

};



#endif //PERSPECTIVECAMERA_H
