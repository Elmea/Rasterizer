#include <imgui.h>
#include <myMaths.hpp>
#include <cmath>
#include <Scene1.hpp>

Scene1::Scene1()
{
    addTriangle();
}

Scene1::~Scene1()
{

}

void Scene1::Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos)
{
    // HERE: Update (if needed) and display the Scene1

    if (ImGui::IsKeyPressed(GLFW_KEY_F1))
        renderer.toggleWireframe();

    renderer.lightEnable(false);

    renderer.SetModel(position, rotation, (myMaths::Float3){scale, scale, scale});

    renderer.setFar(far);
    renderer.setNear(near);

    // Draw
    renderer.setCameraPos(cameraPos);
    renderer.DrawTriangles(vertices.data(), (int)vertices.size(), light.data(), light.size());

    time += deltaTime;

    ShowImGuiControls();
    renderer.ShowImGuiControls();
}

void Scene1::ShowImGuiControls()
{
    if (ImGui::CollapsingHeader("Triangle info", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::SliderFloat("scale", &scale, 0.f, 1.f);
        ImGui::SliderFloat3("rotation", &rotation.x, 0.f, 360.f);
        ImGui::SliderFloat3("position", &position.x, -1.0f, 1.0f);

        if (ImGui::Button("Reset"))
        {
            scale = 1.f;
            position.x = 0.f;
            position.y = 0.f;
            position.z = 0.f;

            rotation.x = 0.f;
            rotation.y = 0.f;
            rotation.z = 0.f;
        }
    }
}