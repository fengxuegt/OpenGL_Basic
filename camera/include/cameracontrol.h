//
// Created by fengxuegt on 2025/7/23.
//

#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <map>
#include "core.h"
#include "camera.h"

class CameraControl {
public:
    CameraControl();
    CameraControl(Camera *camera);

    virtual ~CameraControl();

    // 下面提供的这些函数需要在main.cpp的回调函数中使用；从而将回调的信息传入camera control类中

    virtual void update();
    virtual void onMouse(int button, int action, float xPos, float yPos);
    virtual void onCursor(float xPos, float yPos);
    virtual void onKey(int key, int scancode, int action, int mods);
    virtual void onScroll(double yOffset);

    void setCamera(Camera *camera);
    void setSensitivity(float sensitivity);



protected:
    bool mLeftMouseDown = false;
    bool mRightMouseDown = false;
    bool mMiddleMouseDown = false;

    float mCurrentX = 0.0f;
    float mCurrentY = 0.0f;

    std::map<int, bool> mKeyMap;
    float mSensitivity = 0.1f;
    Camera * mCamera = nullptr;

};



#endif //CAMERACONTROL_H
