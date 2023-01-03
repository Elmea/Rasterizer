#pragma once 
#include <Scene.hpp>

class Scene4 : public Scene
{
private:
    void ShowImGuiControls();

    float cube1Scale = 1.f;
    myMaths::Float3 cube1Position = {-1.f, 0.f, 0.f};
    myMaths::Float3 cube1Rotation = {0.f, 0.f, 0.f};
    float cube1Alpha = 0.5f;

    float cube2Scale = 1.f;
    myMaths::Float3 cube2Position = {1.f, 0.f, 0.f};
    myMaths::Float3 cube2Rotation = {150.f, 50.f, 150.f};
    float cube2Alpha = 0.5f;

    Texture crate;

    float crateScale = 1.f;
    myMaths::Float3 cratePosition = {0.f, 0.f, -1.f};
    myMaths::Float3 crateRotation = {0.f, 0.f, 0.f};
    float crateAlpha = 0.5f;

public:
    Scene4();
    ~Scene4();
    
    void Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos) override;
};