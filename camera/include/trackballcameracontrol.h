//
// Created by fengxuegt on 2025/7/23.
//

#ifndef TRACKBALLCAMERACONTROL_H
#define TRACKBALLCAMERACONTROL_H
#include <cameracontrol.h>


class TrackBallCameraControl : public CameraControl{
public:
    TrackBallCameraControl();
    ~TrackBallCameraControl();
    void onCursor(float xPos, float yPos) override;

private:
    void pitch(float angle);
    void yaw(float angle);
    float mMoveSpeed = 0.01f;
};



#endif //TRACKBALLCAMERACONTROL_H
