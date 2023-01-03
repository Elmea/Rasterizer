#pragma once

#include <types.hpp>
#include <myMaths.hpp>

struct CameraInputs
{
    float deltaX;
    float deltaY;
    bool moveForward;
    bool moveBackward;
    bool moveRight;
    bool moveLeft;
    bool moveUp;
    bool moveDown;
};

class Camera
{
private:
    myMaths::Float3 position = {0.f, 0.f, -2.f};
    myMaths::Float3 rotation = {0.f, 0.f, 0.f};
    float far;
    float near;
    float right;
    float left;
    float top;
    float bottom;

    float FOV = 60.f;
    float speed = 0.1f;
    float aspect;
public:
    Camera(const uint p_width, const uint p_height);

    void Update(const float p_deltaTime, const CameraInputs& p_inputs);
    myMaths::Mat4 GetViewMatrix();
    myMaths::Mat4 GetPerspectiveProjection();
    myMaths::Mat4 GetOrtho();

    myMaths::Float3 getPosition() { return position; };

    void setFov(float _fov);
    void setRenderDistance(float near, float far);
    float getFar() { return far; };
    float getNear() { return near; };

    void setPosRot(myMaths::Float3 pos, myMaths::Float3 rot);

    void setParameters(float l = -1.f, float r = 1.f, float b = -1.f, float t = 1.f, float n = 0.1f, float f = 10.f);
    void setSpeed(float input);

    void ShowImGuiControls();
};