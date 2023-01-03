#pragma once

#include <types.hpp>
#include <Framebuffer.hpp>
#include <myMaths.hpp>
#include <Light.hpp>
#include <texture.hpp>

// Vertex format (only one supported for now)
struct rdrVertex
{
    float x, y, z;    // Pos
    float nx, ny, nz; // Normal
    float r, g, b, a; // Color
    float u, v;       // Texture coordinates
};


struct Viewport
{

    Viewport(const int p_x, const int p_y, uint p_width, uint p_height):
    x(p_x),y(p_y),width(p_width),height(p_height){}

    const int x;
    const int y;
    uint width; 
    uint height;
};


class Renderer
{
private:
    Framebuffer& fb;
    Viewport viewport;

    myMaths::Float4 lineColor = { 1.f, 1.f, 1.f, 1.f };
    myMaths::Float3 cameraPosition;

    myMaths::Mat4 viewMatrix;
    myMaths::Mat4 projectionMatrix;
    myMaths::Mat4 modelMatrix;

    int lightCount;
    bool isLightEnable = false;

    void fillTriangle(myMaths::Float3 vertices[3], myMaths::Float4 worldCoord[3], myMaths::Float4 colors[3], myMaths::Float4 normal[3], Light* p_lights);
    void fillTexturedTriangle(myMaths::Float3 vertices[3], myMaths::Float2 uv[3], myMaths::Float4 normal[3], Light* p_lights, float alpha);

    bool wireFrame = false;
    bool grandientColor = true;

    void DrawTriangle(rdrVertex* p_vertices, Light* p_lights);
    float far; 
    float near; 

    Texture* selectedTexture;

public:
// Color and depth buffer have to be valid until the shutdown of the renderer
// Color buffer is RGBA, each component is a 32 bits float
// Depth buffer is a buffer of 32bits floats
    Renderer(Framebuffer& _fb, uint p_width, uint p_height);
    ~Renderer();

    void SetProjection(myMaths::Mat4& p_projectionMatrix);
    void SetView(myMaths::Mat4& p_viewMatrix);
    void SetModel(myMaths::Float3 translation, myMaths::Float3 rotation, myMaths::Float3 scale);
    void DrawLine(const myMaths::Float3& p_0, const myMaths::Float3& p_1, const myMaths::Float4& p_color);
    void DrawLine(const myMaths::Float3& p_0, const myMaths::Float3& p_1, const myMaths::Float4& p_color1,const myMaths::Float4& p_color2);
    void DrawTriangles(rdrVertex* p_vertices, const uint p_count, Light* p_lights, const uint p_lightCount);
    void toggleWireframe();
    void toggleGrandientColor();
    void ShowImGuiControls();

    void setTexture(Texture* texture);

    void setCameraPos(myMaths::Float3 pos);
    
    void setFar(float in) { far = in; };
    void setNear(float in) { near = in; };

    void lightEnable(bool enable);
};


