#pragma once 
#include <Scene.hpp>
#include <texture.hpp>

class Scene5 : public Scene
{
private:
    void ShowImGuiControls(Renderer& renderer);

    Texture craftMan;
    Texture anvil;
    Texture spark;
    Texture floor;

public:
    Scene5();
    ~Scene5();
    void Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos) override;
};