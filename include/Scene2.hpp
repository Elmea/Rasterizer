#pragma once 
#include <Scene.hpp>

class Scene2 : public Scene
{
private:
    void ShowImGuiControls();

    float sphereScale = 1.f;
    myMaths::Float3 spherePosition = {-1.f, 0.f, 0.f};
    myMaths::Float3 sphereRotation = {0.f, 0.f, 0.f};

    float cubeScale = 1.f;
    myMaths::Float3 cubePosition = {1.f, 0.f, 0.f};
    myMaths::Float3 cubeRotation = {0.f, 0.f, 0.f};

    myMaths::Float3 lightPos = {0.f, 0.f, -1.f};
    myMaths::Float4 lightColor = {1.f, 1.f, 1.f, 1.f};

    bool actRotSphere=true;
    bool actRotCube=true;
public:
    Scene2();
    ~Scene2();
    
    void Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos) override;
};