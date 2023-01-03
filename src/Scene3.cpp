#include <imgui.h>
#include <myMaths.hpp>
#include <cmath>
#include <Scene3.hpp>
#include <Data_TheNobleCraftsman.hpp>
#include <texture.hpp>

Scene3::Scene3()
{
    crate.loadTexture("assets/crate.png");
}

Scene3::~Scene3()
{
    vertices.clear();
}

void Scene3::Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos)
{
    // HERE: Update (if needed) and display the Scene3

    if (ImGui::IsKeyPressed(GLFW_KEY_F1))
        renderer.toggleWireframe();

    renderer.lightEnable(false);

    renderer.setCameraPos(cameraPos);

    addCube();
    renderer.setTexture(&crate);
    renderer.SetModel(cubePosition, cubeRotation, (myMaths::Float3){cubeScale, cubeScale, cubeScale});
    renderer.setFar(far);
    renderer.setNear(near);
    renderer.DrawTriangles(vertices.data(), (int)vertices.size(), light.data(), light.size());
    renderer.setTexture(nullptr);
    vertices.clear();

    time += deltaTime;

    if (doCubeRotation)
    {
        cubeRotation.y += deltaTime*20;
        if (cubeRotation.y > 360.f)
            cubeRotation.y = 0;
    }

    ShowImGuiControls(renderer);
    endFrame();
}

void Scene3::ShowImGuiControls(Renderer& renderer)
{
    ImGui::SliderFloat("Scale", &cubeScale, 0.f, 1.f);
    ImGui::SliderFloat3("Rotation", &cubeRotation.x, 0.f, 360.f);
    ImGui::SliderFloat3("Position", &cubePosition.x, -5.f, 5.f);


    if (ImGui::Button("Reset"))
    {
        cubeScale = 1.f;
        cubeRotation.x = 0.f;
        cubeRotation.y = 0.f;
        cubeRotation.z = 0.f;

        cubePosition.x = 0.f;
        cubePosition.y = 0.f;
        cubePosition.z = 0.f;
    }
    
    if(ImGui::Button("Wireframe"))
        renderer.toggleWireframe();
    if (ImGui::Button("Cube rotation"))
    {
        if (doCubeRotation)
            doCubeRotation = false;
        else 
            doCubeRotation = true;
    }
}
