#pragma once 
#include <Scene.hpp>
#include <texture.hpp>

class Scene3 : public Scene
{
private:
    void ShowImGuiControls(Renderer& renderer);

    Texture crate;

    float cubeScale = 1.f;
    myMaths::Float3 cubePosition = {0.f, 0.f, 0.f};
    myMaths::Float3 cubeRotation = {0.f, 0.f, 0.f};

    bool doCubeRotation = true;

public:
    Scene3();
    ~Scene3();
    void Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos) override;
};