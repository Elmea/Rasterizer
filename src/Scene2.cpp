#include <imgui.h>
#include <myMaths.hpp>
#include <cmath>
#include <Scene2.hpp>

Scene2::Scene2()
{
}

Scene2::~Scene2()
{
    // HERE: Unload the Scene2
    vertices.clear();
}

void Scene2::Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos)
{
    if (ImGui::IsKeyPressed(GLFW_KEY_F1))
        renderer.toggleWireframe();
        
    // HERE: Update (if needed) and display the Scene2
    renderer.lightEnable(true);

    renderer.setFar(far);
    renderer.setNear(near);

    Light light1;
    light1.setParameters(0.2f, 0.4f, 0.7f);
    light1.setPosition(lightPos);
    light1.setColor(lightColor);
    addLight(light1);

    renderer.setCameraPos(cameraPos);

    addCube();
    renderer.SetModel(cubePosition, cubeRotation, (myMaths::Float3){cubeScale, cubeScale, cubeScale});
    renderer.DrawTriangles(vertices.data(), (int)vertices.size(), light.data(), light.size());
    vertices.clear();

    addSphere(20, 20);
    renderer.SetModel(spherePosition, sphereRotation, (myMaths::Float3){sphereScale, sphereScale, sphereScale});
    renderer.DrawTriangles(vertices.data(), (int)vertices.size(), light.data(), light.size());
    vertices.clear();

    time += deltaTime;

    ShowImGuiControls();
    renderer.ShowImGuiControls();
    endFrame();
}

void Scene2::ShowImGuiControls()
{
    if (ImGui::CollapsingHeader("Scene info", ImGuiTreeNodeFlags_DefaultOpen))
    {

        if (ImGui::CollapsingHeader("cube info", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::SliderFloat("Scale", &cubeScale, 0.f, 1.f);
            ImGui::SliderFloat3("Rotation", &cubeRotation.x, 0.f, 360.f);
            ImGui::SliderFloat3("Position", &cubePosition.x, -5.f, 5.f);


            if (ImGui::Button("Reset cube"))
            {
                cubeScale = 1.f;
                cubeRotation.x = 0.f;
                cubeRotation.y = 0.f;
                cubeRotation.z = 0.f;

                cubePosition.x = 0.f;
                cubePosition.y = 0.f;
                cubePosition.z = 0.f;
            }
            if(ImGui::Button("cube rotation"))
            {
                
                if(actRotCube)
                    actRotCube = false;
                else
                    actRotCube = true;
            }
            if(actRotCube)
            {
                if(cubeRotation.y >= 360)
                    cubeRotation.y = 0;
                cubeRotation.y += 0.4;
            }
        }

        if (ImGui::CollapsingHeader("sphere info", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::SliderFloat("scale", &sphereScale, 0.f, 1.f);
            ImGui::SliderFloat3("rotation", &sphereRotation.x, 0.f, 360.f);
            ImGui::SliderFloat3("position", &spherePosition.x, -5.f, 5.f);


            if (ImGui::Button("Reset sphere"))
            {
                sphereScale = 1.f;
                sphereRotation.x = 0.f;
                sphereRotation.y = 0.f;
                sphereRotation.z = 0.f;

                spherePosition.x = 0.f;
                spherePosition.y = 0.f;
                spherePosition.z = 0.f;
            }
            if(ImGui::Button("sphere rotation"))
            {
                if(actRotSphere)
                    actRotSphere = false;
                else
                    actRotSphere = true;
            }
            if(actRotSphere)
            {
                if(sphereRotation.y >= 360)
                    sphereRotation.y = 0;
                sphereRotation.y += 0.4;
            }
        }
        if (ImGui::CollapsingHeader("light info", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::SliderFloat3("light position", &lightPos.x, -5.f, 5.f);
            ImGui::ColorEdit4("lightColor", &lightColor.x);

            if (ImGui::Button("Reset light"))
            {
                lightPos.x = 0.f;
                lightPos.y = 0.f;
                lightPos.z = 0.f;
            }
        }
    }
}