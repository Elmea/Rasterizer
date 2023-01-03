
#include <imgui.h>
#include <cmath>
#include <myMaths.hpp>
#include <Camera.hpp>

Camera::Camera(const uint width, const uint height)
{
    aspect = (float)width/(float)height;
}

void Camera::Update(const float p_deltaTime, const CameraInputs& inputs)
{
    rotation.y -= inputs.deltaX/6; 
    rotation.x += inputs.deltaY/6;

    if (rotation.x < -90)
        rotation.x = -90;

    if (rotation.x > 90)
        rotation.x = 90;

    if (rotation.y > 360)
        rotation.y = -360;

    if (rotation.y < -360)
        rotation.y = 360;

    if(inputs.moveForward)
    {
        position.x -= speed*cosf(DEG2RAD*(rotation.y + 90));
        position.z += speed*sinf(DEG2RAD*(rotation.y + 90));
    }
    if(inputs.moveBackward)
    {
        position.x += speed*cosf(DEG2RAD*(rotation.y + 90));
        position.z -= speed*sinf(DEG2RAD*(rotation.y + 90));
    }

    if (inputs.moveLeft)
    {
        position.x += speed*cosf(DEG2RAD*(rotation.y));
        position.z -= speed*sinf(DEG2RAD*(rotation.y));
    }
    if (inputs.moveRight)
    {
        position.x -= speed*cosf(DEG2RAD*(rotation.y));
        position.z += speed*sinf(DEG2RAD*(rotation.y));
    }

    if (inputs.moveUp)
        position.y += speed;

    if (inputs.moveDown)
        position.y -= speed;
}

void Camera::setSpeed(float input)
{
    speed = input;
}

myMaths::Mat4 Camera::GetViewMatrix()
{
    return myMaths::Mat4::getRotationX(-DEG2RAD*rotation.x) * myMaths::Mat4::getRotationY(-DEG2RAD*rotation.y) * myMaths::Mat4::getTranslation(-position);
}

myMaths::Mat4 Camera::GetOrtho()
{
    myMaths::Mat4 ortho;
    float temp[4][4] = {
        {-2.f/(right-left), 0.f, 0.f, -(right+left)/(right-left)},
        {0.f, -2.f/(top-bottom), 0.f, -(top+bottom)/(top-bottom)},
        {0.f, 0.f, -2.f/(far-near), -(far+near)/(far-near)},
        {0.f, 0.f, 0.f, 1.f}
    };
    ortho = temp;

    return ortho;
}

myMaths::Mat4 Camera::GetPerspectiveProjection()
{
    float a = 1.f / tanf(DEG2RAD*FOV/2.f);

    myMaths::Mat4 prespective;
    float temp[4][4] = {
        {a/aspect, 0.f, 0.f, 0.f},
        {0.f, a, 0.f, 0.f},
        {0.f, 0.f, -(far+near)/(far-near), -(2*far*near)/(far-near)},
        {0.f, 0.f, -1.f, 0.f}
    };

    prespective = temp;

    return prespective;
}

void Camera::setFov(float _fov)
{
    FOV = _fov;
}

void Camera::setRenderDistance(float n, float f)
{
    far = f;
    near = n;
}

void Camera::ShowImGuiControls()
{
    if (ImGui::Button("Reset"))
    {
        position.x = 0; position.y = 0; position.z = -2.f;
        rotation.x = 0; rotation.y = 0; rotation.z = 0;
    }

    ImGui::SliderFloat3("Position", &position.x, -10.f, 10.f);
    ImGui::SliderFloat3("Rotation", &rotation.x, 0.f, 360.f);
}

void Camera::setParameters(float l, float r, float b, float t, float n, float f)
{
    far = f;
    near = n;
    right = r;
    left = l;
    top = t;
    bottom = b;
}

void Camera::setPosRot(myMaths::Float3 pos, myMaths::Float3 rot)
{
    position = pos;
    rotation = rot;
}