#include <imgui.h>
#include <myMaths.hpp>
#include <cmath>
#include <Scene5.hpp>
#include <Data_TheNobleCraftsman.hpp>
#include <texture.hpp>

Scene5::Scene5()
{
    craftMan.loadTexture("assets/blacksmith.bmp");
    anvil.loadTexture("assets/anvil.bmp");
    spark.loadTexture("assets/spark.bmp");
    floor.loadTexture("assets/floor.bmp");
}

Scene5::~Scene5()
{
    vertices.clear();
}

void Scene5::Update(float deltaTime, Renderer& renderer, float near, float far, myMaths::Float3 cameraPos)
{
    if (ImGui::IsKeyPressed(GLFW_KEY_F1))
        renderer.toggleWireframe();

    renderer.lightEnable(false);
    renderer.setCameraPos(cameraPos);

    renderer.setFar(far);
    renderer.setNear(near);

    renderer.SetModel({0.f, 0.f, 0.f}, {0.f, 180.f, 0.f}, {1.f, 1.f, 1.f});

    renderer.setTexture(&craftMan);
    renderer.DrawTriangles(blacksmith_mesh, blacksmith_size, light.data(), light.size());

    renderer.setTexture(&anvil);
    renderer.DrawTriangles(anvil_mesh, anvil_size, light.data(), light.size());

    renderer.setTexture(&spark);
    renderer.DrawTriangles(spark_mesh, spark_size, light.data(), light.size());
    
    renderer.setTexture(&floor);
    renderer.DrawTriangles(floor_mesh, floor_size, light.data(), light.size());
    renderer.setTexture(nullptr);

    time += deltaTime;

    ShowImGuiControls(renderer);
    endFrame();
}

void Scene5::ShowImGuiControls(Renderer& renderer)
{
    if(ImGui::Button("Wireframe"))
            renderer.toggleWireframe();
}
