#pragma once
#include <vector>
#include <Light.hpp>
#include <Renderer.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Scene
{
private:
    void ShowImGuiControls();

protected:
    double time = 0.0;
    std::vector<rdrVertex> vertices;
    std::vector<Light> light;

    void addCube();
    void addCube(float alpha);
    void addSphere(int lon, int lat);
    void addLight(Light light);
    void bindLight();
    void addTriangle();
    void endFrame();

public:
    Scene() {};
    virtual ~Scene() { vertices.clear(); };
    virtual void Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos) = 0;
};
