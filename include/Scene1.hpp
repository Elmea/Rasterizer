#pragma once 
#include <Scene.hpp>

class Scene1 : public Scene
{
private:
    void ShowImGuiControls();
    float scale = 1.f;
    myMaths::Float3 position = {0.f, 0.f, 0.f};
    myMaths::Float3 rotation = {0.f, 0.f, 0.f};
    
public:
    Scene1();
    ~Scene1();
    void Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos) override;
};