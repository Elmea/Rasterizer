#include <imgui.h>
#include <myMaths.hpp>
#include <cmath>
#include <Scene4.hpp>

Scene4::Scene4()
{
    crate.loadTexture("assets/crate.png");
}

Scene4::~Scene4()
{
    // HERE: Unload the Scene4
    vertices.clear();
}

void Scene4::Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos)
{
    if (ImGui::IsKeyPressed(GLFW_KEY_F1))
        renderer.toggleWireframe();
        
    renderer.lightEnable(false);

    renderer.setFar(far);
    renderer.setNear(near);

    renderer.setCameraPos(cameraPos);

    addCube(cube1Alpha);
    renderer.SetModel(cube1Position, cube1Rotation, (myMaths::Float3){cube1Scale, cube1Scale, cube1Scale});
    renderer.DrawTriangles(vertices.data(), (int)vertices.size(), light.data(), light.size());
    vertices.clear();

    addCube(cube2Alpha);
    renderer.SetModel(cube2Position, cube2Rotation, (myMaths::Float3){cube2Scale, cube2Scale, cube2Scale});
    renderer.DrawTriangles(vertices.data(), (int)vertices.size(), light.data(), light.size());
    vertices.clear();

    addCube(crateAlpha);
    renderer.setTexture(&crate);
    renderer.SetModel(cratePosition, crateRotation, (myMaths::Float3){crateScale, crateScale, crateScale});
    renderer.DrawTriangles(vertices.data(), (int)vertices.size(), light.data(), light.size());
    renderer.setTexture(nullptr);
    vertices.clear();

    time += deltaTime;

    ShowImGuiControls();
    renderer.ShowImGuiControls();
    endFrame();
}

void Scene4::ShowImGuiControls()
{
    if (ImGui::CollapsingHeader("Scene info", ImGuiTreeNodeFlags_DefaultOpen))
    {

        if (ImGui::CollapsingHeader("cube 1 info", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::SliderFloat("Scale", &cube1Scale, 0.f, 1.f);
            ImGui::SliderFloat3("Rotation", &cube1Rotation.x, 0.f, 360.f);
            ImGui::SliderFloat3("Position", &cube1Position.x, -5.f, 5.f);
            ImGui::SliderFloat("Alpha", &cube1Alpha, 0.f, 1.f);


            if (ImGui::Button("Reset1"))
            {
                cube1Scale = 1.f;
                cube1Rotation.x = 0.f;
                cube1Rotation.y = 0.f;
                cube1Rotation.z = 0.f;

                cube1Position.x = -1.f;
                cube1Position.y = 0.f;
                cube1Position.z = 0.f;

                cube1Alpha = 0.5f;
            }
        }

        if (ImGui::CollapsingHeader("cube 2 info", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::SliderFloat("scale", &cube2Scale, 0.f, 1.f);
            ImGui::SliderFloat3("rotation", &cube2Rotation.x, 0.f, 360.f);
            ImGui::SliderFloat3("position", &cube2Position.x, -5.f, 5.f);
            ImGui::SliderFloat("alpha", &cube2Alpha, 0.f, 1.f);

            if (ImGui::Button("Reset2"))
            {
                cube2Scale = 1.f;
                cube2Rotation.x = 150.f;
                cube2Rotation.y = 50.f;
                cube2Rotation.z = 150.f;

                cube2Position.x = 1.f;
                cube2Position.y = 0.f;
                cube2Position.z = 0.f;

                cube2Alpha = 0.5f;
            }
        }

        if (ImGui::CollapsingHeader("crate info", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::SliderFloat("crate scale", &crateScale, 0.f, 1.f);
            ImGui::SliderFloat3("crate rotation", &cube1Rotation.x, 0.f, 360.f);
            ImGui::SliderFloat3("crate position", &cratePosition.x, -5.f, 5.f);
            ImGui::SliderFloat("crate alpha", &crateAlpha, 0.f, 1.f);

            if (ImGui::Button("Reset crate"))
            {
                crateScale = 1.f;
                crateRotation.x = 0.f;
                crateRotation.y = 0.f;
                crateRotation.z = 0.f;

                cratePosition.x = 0.f;
                cratePosition.y = 0.f;
                cratePosition.z = -1.f;

                crateAlpha = 0.5f;
            }
        }
    }
}