#include <imgui.h>
#include <myMaths.hpp>
#include <cmath>
#include <Scene.hpp>

void Scene::addTriangle()
{
        //                     pos                  normal                  color                     uv
    vertices.push_back({-0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, 1.f,    0.0f, 0.0f });
}

void Scene::addCube()
{
        //                        pos                     normal                  color              uv
    vertices.push_back({-0.5f,-0.5f,-0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, 1.f,     0.0f, 0.0f });
    vertices.push_back({ 0.5f,-0.5f, 0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, 1.f,     1.0f, 1.0f });
    vertices.push_back({ 0.5f,-0.5f,-0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, 1.f,     1.0f, 0.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, 1.f,     0.0f, 0.0f });
    vertices.push_back({-0.5f,-0.5f, 0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, 1.f,     0.0f, 1.0f });
    vertices.push_back({ 0.5f,-0.5f, 0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, 1.f,     1.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({-0.5f, 0.5f,-0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.f,    0.0f, 1.0f });
    vertices.push_back({-0.5f, 0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.f,    1.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({-0.5f, 0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.f,    1.0f, 1.0f });
    vertices.push_back({-0.5f,-0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.f,    1.0f, 0.0f });

    vertices.push_back({-0.5f,-0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 1.f,    1.0f, 1.0f });
    vertices.push_back({-0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 1.f,    0.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f,-0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 1.f,    1.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 1.f,    1.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, 1.f,    1.0f, 1.0f });
    vertices.push_back({-0.5f, 0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, 1.f,    0.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, 1.f,    1.0f, 1.0f });
    vertices.push_back({ 0.5f,-0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, 1.f,    1.0f, 0.0f });

    vertices.push_back({ 0.5f,-0.5f, 0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f,-0.5f,-0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, 1.f,    1.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, 1.f,    1.0f, 1.0f });

    vertices.push_back({ 0.5f,-0.5f, 0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, 1.f,    1.0f, 1.0f });
    vertices.push_back({ 0.5f, 0.5f, 0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, 1.f,    0.0f, 1.0f });

    vertices.push_back({-0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.f,    0.0f, 1.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.f,    1.0f, 1.0f });

    vertices.push_back({-0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.f,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.f,    1.0f, 1.0f });
    vertices.push_back({-0.5f, 0.5f,-0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.f,    1.0f, 0.0f });
}

void Scene::addCube(float alpha)
{
        //                        pos                     normal                  color              uv
    vertices.push_back({-0.5f,-0.5f,-0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, alpha,     0.0f, 0.0f });
    vertices.push_back({ 0.5f,-0.5f, 0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, alpha,     1.0f, 1.0f });
    vertices.push_back({ 0.5f,-0.5f,-0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, alpha,     1.0f, 0.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, alpha,     0.0f, 0.0f });
    vertices.push_back({-0.5f,-0.5f, 0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, alpha,     0.0f, 1.0f });
    vertices.push_back({ 0.5f,-0.5f, 0.5f,      0.0f,-1.0f, 0.0f,      1.0f, 0.0f, 0.0f, alpha,     1.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({-0.5f, 0.5f,-0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, alpha,    0.0f, 1.0f });
    vertices.push_back({-0.5f, 0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, alpha,    1.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({-0.5f, 0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, alpha,    1.0f, 1.0f });
    vertices.push_back({-0.5f,-0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, alpha,    1.0f, 0.0f });

    vertices.push_back({-0.5f,-0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, alpha,    1.0f, 1.0f });
    vertices.push_back({-0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, alpha,    0.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({ 0.5f,-0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, alpha,    1.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, alpha,    1.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, alpha,    1.0f, 1.0f });
    vertices.push_back({-0.5f, 0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, alpha,    0.0f, 1.0f });

    vertices.push_back({-0.5f,-0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, alpha,    1.0f, 1.0f });
    vertices.push_back({ 0.5f,-0.5f,-0.5f,      0.0f, 0.0f,-1.0f,      0.0f, 1.0f, 1.0f, alpha,    1.0f, 0.0f });

    vertices.push_back({ 0.5f,-0.5f, 0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({ 0.5f,-0.5f,-0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, alpha,    1.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, alpha,    1.0f, 1.0f });

    vertices.push_back({ 0.5f,-0.5f, 0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, alpha,    1.0f, 1.0f });
    vertices.push_back({ 0.5f, 0.5f, 0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, alpha,    0.0f, 1.0f });

    vertices.push_back({-0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, alpha,    0.0f, 1.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, alpha,    1.0f, 1.0f });

    vertices.push_back({-0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, alpha,    0.0f, 0.0f });
    vertices.push_back({ 0.5f, 0.5f,-0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, alpha,    1.0f, 1.0f });
    vertices.push_back({-0.5f, 0.5f,-0.5f,      0.0f, 1.0f, 0.0f,      1.0f, 0.0f, 1.0f, alpha,    1.0f, 0.0f });
}

static myMaths::Float3 getSphericalCoords(float r, float theta, float phi)
{
    return {r * sinf(theta) * cosf(phi),
            r * cosf(theta),
            r * sinf(theta) * sinf(phi)};
}

void Scene::addSphere(int lon, int lat)
{
    float r = 0.5f;

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j + 0) / (float)lat) * M_PI; //lat
        float theta1 = ((j + 1) / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i + 0) / (float)lon) * 2.f * M_PI;
            float phi1 = ((i + 1) / (float)lon) * 2.f * M_PI;

            myMaths::Float3 c0 = getSphericalCoords(r, theta0, phi0);
            myMaths::Float3 c1 = getSphericalCoords(r, theta0, phi1);
            myMaths::Float3 c2 = getSphericalCoords(r, theta1, phi1);
            myMaths::Float3 c3 = getSphericalCoords(r, theta1, phi0);

            myMaths::Float3 normal1 = myMaths::calcNormal(c0, c1, c2);
            myMaths::Float3 normal2 = myMaths::calcNormal(c0, c2, c3);

            vertices.push_back({c0.x, c0.y, c0.z,      normal1.x,normal1.y, normal1.z,      1.0f, 0.0f, 0.0f, 1.f,    0.0f, 0.0f });
            vertices.push_back({c1.x, c1.y, c1.z,      normal1.x,normal1.y, normal1.z,      1.0f, 0.0f, 0.0f, 1.f,    0.0f, 0.0f });
            vertices.push_back({c2.x, c2.y, c2.z,      normal1.x,normal1.y, normal1.z,      1.0f, 0.0f, 0.0f, 1.f,    0.0f, 0.0f });

            vertices.push_back({c0.x, c0.y, c0.z,      normal2.x,normal2.y, normal2.z,      0.0f, 0.0f, 1.0f, 1.f,    0.0f, 0.0f });
            vertices.push_back({c2.x, c2.y, c2.z,      normal2.x,normal2.y, normal2.z,      0.0f, 0.0f, 1.0f, 1.f,    0.0f, 0.0f });
            vertices.push_back({c3.x, c3.y, c3.z,      normal2.x,normal2.y, normal2.z,      0.0f, 0.0f, 1.0f, 1.f,    0.0f, 0.0f });
        }
    }
}


void Scene::addLight(Light _light)
{
    light.push_back(_light);
}

void Scene::endFrame()
{
    light.clear();
    vertices.clear();
}