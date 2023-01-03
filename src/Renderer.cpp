
#include <cstdio>
#include <cstring>
#include <cassert>

#include <imgui.h>

#include <myMaths.hpp>

#include <Renderer.hpp>

#include <math.h>

#include <Light.hpp>

using namespace myMaths;

Renderer::Renderer(Framebuffer &_fb, uint p_width, uint p_height) : fb(_fb), viewport(0, 0, p_width, p_height)
{
    //fb.colorBuffer = reinterpret_cast<Float4*>(p_colorBuffer32Bits);
    //fb.depthBuffer = p_depthBuffer;
    selectedTexture = nullptr;
}

Renderer::~Renderer()
{
}

void Renderer::SetProjection(myMaths::Mat4 &p_projectionMatrix)
{
    projectionMatrix = p_projectionMatrix;
}

void Renderer::SetView(myMaths::Mat4 &p_viewMatrix)
{
    viewMatrix = p_viewMatrix;
}

void Renderer::SetModel(Float3 translation, Float3 rotation, Float3 scale)
{
    modelMatrix = Mat4::CreateTransformMatrix(translation, rotation, scale);
}

void DrawPixel(Float4 *p_colorBuffer, float* p_depthBuffer, Float4 *p_colorDepthBuffer, uint p_width, uint p_height, uint p_x, uint p_y, float p_z, float far, float near, Float4 p_color)
{
    if ((p_x >= 0 && p_x < p_width) && (p_y >= 0 && p_y < p_height))
    { 
        int id = p_x + p_y * p_width;
        if (p_z < p_depthBuffer[id] && p_z < far && p_z > near)
        {
            float ratio = 1 - p_z/far;

            if (1)
            {
                p_color.x = (p_color.x*p_color.w + p_colorBuffer[id].x*p_colorBuffer[id].w*(1 - p_color.w));
                p_color.y = (p_color.y*p_color.w + p_colorBuffer[id].y*p_colorBuffer[id].w*(1 - p_color.w));
                p_color.z = (p_color.z*p_color.w + p_colorBuffer[id].z*p_colorBuffer[id].w*(1 - p_color.w));

                p_color.w = p_color.w + p_colorBuffer[id].w*(1 - p_color.w);

                p_color.x /= p_color.w;
                p_color.y /= p_color.w;
                p_color.z /= p_color.w;

                p_colorBuffer[id] = p_color; 
                p_depthBuffer[id] = p_z;
            }
            else 
            {
                p_colorBuffer[id] = p_color; 
                p_depthBuffer[id] = p_z;
            }

            Float4 depthColor = {(Float3){1.f, 1.f, 1.f}*ratio, p_color.w};
            p_colorDepthBuffer[id] = depthColor;
        }
    }
}

void Renderer::DrawLine(const Float3 &p0, const Float3 &p1, const Float4 &color)
{
    int x0 = p0.x, y0 = p0.y, z0 = p0.z, x1 = p1.x, y1 = p1.y, z1 = p1.z;
    int dx = absoluteValue(x1 - x0), sx = (x0 < x1 ? 1 : -1);
    int dy = -absoluteValue(y1 - y0), sy = (y0 < y1 ? 1 : -1);
    int dz = -absoluteValue(z1 - z0), sz = (z0 < z1 ? 1 : -1);
    
    int err = dx + dy, e2;

    while (!(x0 == x1 && y0 == y1))
    {
        DrawPixel(reinterpret_cast<Float4 *>(fb.GetColorBuffer()), fb.GetDepthBuffer(), fb.GetDepthColorBuffer(), fb.GetWidth(), fb.GetHeight(), x0, y0, 2, 100, 0.1, color);

        e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void Renderer::DrawLine(const Float3 &p0, const Float3 &p1, const Float4 &color1, const Float4 &color2)
{
    int x0 = p0.x, y0 = p0.y, z0 = p0.z, x1 = p1.x, y1 = p1.y, z1 = p1.z;
    int dx = absoluteValue(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -absoluteValue(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int dz = -absoluteValue(z1 - z0), sz = z0 < z1 ? 1 : -1;
    int err = dx + dy, e2;
    myMaths::Float2 p = {p0.x, p1.y};
    float nbpix = sqrtf((p.y - p0.y) * (p.y - p0.y) + (p1.x - p.x) * (p1.x - p.x));

    float Tcolor1, Tcolor2, Tcolor3;

    float colorIntesity = 1 / nbpix;
    myMaths::Float4 color3;
    int i = 0;
    int j = nbpix;
    while (!(x0 == x1 && y0 == y1))
    {
        Tcolor1 = color2.x * i * colorIntesity + (color1.x * j * colorIntesity);
        Tcolor2 = color2.y * i * colorIntesity + (color1.y * j * colorIntesity);
        Tcolor3 = color2.z * i * colorIntesity + (color1.z * j * colorIntesity);

        color3 = {Tcolor1, Tcolor2, Tcolor3, color1.w};
        DrawPixel(reinterpret_cast<Float4 *>(fb.GetColorBuffer()), fb.GetDepthBuffer(), fb.GetDepthColorBuffer(), fb.GetWidth(), fb.GetHeight(), x0, y0, 2, 100, 0.1, color3);

        e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }

        i++;
        j--;
    }
}

Float3 ndcToScreenCoords(Float3 ndc, const Viewport &viewport)
{
    ndc.x = (ndc.x + 1) * viewport.width / 2;
    ndc.y = (ndc.y + 1) * viewport.height / 2;
    // ndc.z = (ndc.z + 1) / 2;
    return ndc;
}

float edgeFunc(int x, int y, Float3 p1, Float3 p2)
{
    return -((p1.y - p2.y) * x + (p2.x - p1.x) * y + (p1.x * p2.y - p1.y * p2.x));
}

void Renderer::fillTriangle(Float3 vertices[3], myMaths::Float4 worldCoord[3],Float4 colors[3], Float4 normal[3], Light* p_lights)
{

    float startX = 10000000.f;
    float startY = 10000000.f;
    float endX = -10000000.f;
    float endY = -10000000.f;

    //Get higher vertice, anf the one more on the left
    {
        for (int a = 0; a < 3; a++)
        {
            if (vertices[a].y < startY)
                startY = vertices[a].y;

            if (vertices[a].x < startX)
                startX = vertices[a].x;

            if (vertices[a].y > endY)
                endY = vertices[a].y;

            if (vertices[a].x > endX)
                endX = vertices[a].x;
        }
    }

    //Check if polygons is clockwise or counterclockwise
    float orientedArea = 0;
    for (int i = 0; i < 3; i++)
    {
        orientedArea += vertices[i%3].x * vertices[(i + 1)%3].y - vertices[(i + 1)%3].x * vertices[i%3].y;
    }

    //fill triangle
    for (int y = startY; y < endY; y++)
    {
        for (int x = startX; x < endX; x++)
        {
            myMaths::Float4 color;
            

            if (orientedArea > 0)
            {
                float cw0 = edgeFunc(x, y, vertices[1], vertices[2]);
                float cw1 = edgeFunc(x, y, vertices[2], vertices[0]);
                float cw2 = edgeFunc(x, y, vertices[0], vertices[1]);
                if (cw0 <= 0 && cw1 <= 0 && cw2 <= 0)
                {

                    float total = cw0 + cw1 + cw2; // normalize cw

                    float p0proximity = cw0/total;
                    float p1proximity = cw1/total;
                    float p2proximity = cw2/total;

                    float z = (vertices[0].z*p0proximity + vertices[1].z*p1proximity + vertices[2].z*p2proximity);


                    Float4 lineColor2;
                    if (isLightEnable)
                    {
                        Float3 colorLight = 0;
                        for (int id = 0; id < lightCount; id++)
                        {
                            myMaths::Float3 wC0 = worldCoord[0].getXYZF3() * p0proximity; myMaths::Float3 wC1 = worldCoord[1].getXYZF3() * p1proximity; myMaths::Float3 wC2 = worldCoord[2].getXYZF3() * p2proximity;
                            myMaths::Float3 pointWorldCoord = wC0 + wC1 + wC2;
                            myMaths::Float3 nC0 = normal[0].getXYZF3() * p0proximity; myMaths::Float3 nC1 = normal[1].getXYZF3() * p1proximity; myMaths::Float3 nC2 = normal[2].getXYZF3() * p2proximity;
                            myMaths::Float3 pointNormalCoord = nC0 + nC1 + nC2;
                            Float3 intensity = (p_lights[id].getColorLight2(pointNormalCoord, cameraPosition, pointWorldCoord, 100));
                            colorLight.x += intensity.x;
                            colorLight.y += intensity.y;
                            colorLight.z += intensity.z;
                        }
                        
                        color = {(colors[0].x * p0proximity + colors[1].x * p1proximity + colors[2].x * p2proximity) * colorLight.x,
                                 (colors[0].y * p0proximity + colors[1].y * p1proximity + colors[2].y * p2proximity) * colorLight.y, 
                                 (colors[0].z * p0proximity + colors[1].z * p1proximity + colors[2].z * p2proximity) * colorLight.z,
                                 (colors[0].w * p0proximity + colors[1].w * p1proximity + colors[2].w * p2proximity)};

                        lineColor2.x = lineColor.x * colorLight.x;
                        lineColor2.y = lineColor.y * colorLight.y;
                        lineColor2.z = lineColor.z * colorLight.z;
                        lineColor2.w = lineColor.w;
                    }
                    else 
                    {
                        color = {(colors[0].x * p0proximity + colors[1].x * p1proximity + colors[2].x * p2proximity),
                                 (colors[0].y * p0proximity + colors[1].y * p1proximity + colors[2].y * p2proximity), 
                                 (colors[0].z * p0proximity + colors[1].z * p1proximity + colors[2].z * p2proximity),
                                 (colors[0].w * p0proximity + colors[1].w * p1proximity + colors[2].w * p2proximity)};

                        lineColor2.x = lineColor.x;
                        lineColor2.y = lineColor.y;
                        lineColor2.z = lineColor.z;
                        lineColor2.w = lineColor.w;
                    }
                    
                    DrawPixel(reinterpret_cast<Float4 *>(fb.GetColorBuffer()), fb.GetDepthBuffer(), fb.GetDepthColorBuffer(), fb.GetWidth(), fb.GetHeight(), x, y, z, far, near, grandientColor ? color : lineColor2);
                }
            }

            if (orientedArea < 0)
            {
                float ccw0 = edgeFunc(x, y, vertices[2], vertices[1]);
                float ccw1 = edgeFunc(x, y, vertices[0], vertices[2]);
                float ccw2 = edgeFunc(x, y, vertices[1], vertices[0]);
                if (ccw0 <= 0 && ccw1 <= 0 && ccw2 <= 0)
                {
                    float total = ccw0 + ccw1 + ccw2; // normalize cw

                    float p0proximity = ccw0/total;
                    float p1proximity = ccw1/total;
                    float p2proximity = ccw2/total;

                    float z = (vertices[0].z*p0proximity + vertices[1].z*p1proximity + vertices[2].z*p2proximity);

                    Float4 lineColor2;
                    if (isLightEnable)
                    {
                        Float3 colorLight = 0;
                        for (int id = 0; id < lightCount; id++)
                        {
                            myMaths::Float3 wC0 = worldCoord[0].getXYZF3() * p0proximity; myMaths::Float3 wC1 = worldCoord[1].getXYZF3() * p1proximity; myMaths::Float3 wC2 = worldCoord[2].getXYZF3() * p2proximity;
                            myMaths::Float3 pointWorldCoord = wC0 + wC1 + wC2;
                            myMaths::Float3 nC0 = normal[0].getXYZF3() * p0proximity; myMaths::Float3 nC1 = normal[1].getXYZF3() * p1proximity; myMaths::Float3 nC2 = normal[2].getXYZF3() * p2proximity;
                            myMaths::Float3 pointNormalCoord = nC0 + nC1 + nC2;
                            Float3 intensity = (p_lights[id].getColorLight2(pointNormalCoord, cameraPosition, pointWorldCoord, 100));
                            colorLight.x += intensity.x;
                            colorLight.y += intensity.y;
                            colorLight.z += intensity.z;
                        }
                        
                        color = {(colors[0].x * p0proximity + colors[1].x * p1proximity + colors[2].x * p2proximity) * colorLight.x,
                                 (colors[0].y * p0proximity + colors[1].y * p1proximity + colors[2].y * p2proximity) * colorLight.y, 
                                 (colors[0].z * p0proximity + colors[1].z * p1proximity + colors[2].z * p2proximity) * colorLight.z,
                                 (colors[0].w * p0proximity + colors[1].w * p1proximity + colors[2].w * p2proximity)};

                        lineColor2.x = lineColor.x * colorLight.x;
                        lineColor2.y = lineColor.y * colorLight.y;
                        lineColor2.z = lineColor.z * colorLight.z;
                        lineColor2.w = lineColor.w;
                    }
                    else 
                    {
                        color = {(colors[0].x * p0proximity + colors[1].x * p1proximity + colors[2].x * p2proximity),
                                 (colors[0].y * p0proximity + colors[1].y * p1proximity + colors[2].y * p2proximity), 
                                 (colors[0].z * p0proximity + colors[1].z * p1proximity + colors[2].z * p2proximity),
                                 (colors[0].w * p0proximity + colors[1].w * p1proximity + colors[2].w * p2proximity)};

                        lineColor2.x = lineColor.x;
                        lineColor2.y = lineColor.y;
                        lineColor2.z = lineColor.z;
                        lineColor2.w = lineColor.w;
                    }
                    
                    DrawPixel(reinterpret_cast<Float4 *>(fb.GetColorBuffer()), fb.GetDepthBuffer(), fb.GetDepthColorBuffer(), fb.GetWidth(), fb.GetHeight(), x, y, z, far, near, grandientColor ? color : lineColor2);
                }
            }
        }
    }
}

void Renderer::fillTexturedTriangle(myMaths::Float3 vertices[3], myMaths::Float2 uv[3], Float4 normal[3], Light* p_lights, float alpha)
{
    float startX = 10000000.f;
    float startY = 10000000.f;
    float endX = -10000000.f;
    float endY = -10000000.f;

    //Get higher vertice, anf the one more on the left
    {
        for (int a = 0; a < 3; a++)
        {
            if (vertices[a].y < startY)
                startY = vertices[a].y;

            if (vertices[a].x < startX)
                startX = vertices[a].x;

            if (vertices[a].y > endY)
                endY = vertices[a].y;

            if (vertices[a].x > endX)
                endX = vertices[a].x;
        }
    }

    //Check if polygons is clockwise or counterclockwise
    float orientedArea = 0;
    for (int i = 0; i < 3; i++)
    {
        orientedArea += vertices[i%3].x * vertices[(i + 1)%3].y - vertices[(i + 1)%3].x * vertices[i%3].y;
    }

    //fill triangle
    for (int y = startY; y < endY; y++)
    {
        for (int x = startX; x < endX; x++)
        {
            myMaths::Float4 color;

            if (orientedArea > 0)
            {
                float cw0 = edgeFunc(x, y, vertices[1], vertices[2]);
                float cw1 = edgeFunc(x, y, vertices[2], vertices[0]);
                float cw2 = edgeFunc(x, y, vertices[0], vertices[1]);
                if (cw0 <= 0 && cw1 <= 0 && cw2 <= 0)
                {
                    float total = cw0 + cw1 + cw2; // normalize cw

                    float p0proximity = cw0/total;
                    float p1proximity = cw1/total;
                    float p2proximity = cw2/total;

                    float z = (vertices[0].z*p0proximity + vertices[1].z*p1proximity + vertices[2].z*p2proximity);
                    Float2 uv0 = uv[0] * p0proximity;
                    Float2 uv1 = uv[1] * p1proximity;
                    Float2 uv2 = uv[2] * p2proximity;  

                    if (isLightEnable)
                    {
                        float colorLight = 0;
                        for (int id = 0; id < lightCount; id++)
                        {
                            colorLight += p_lights[id].getColorLight(normal[0], cameraPosition, (myMaths::Float3){(float)x, (float)y, z}, 30);
                        }
                        
                        color = selectedTexture->getPixelColor((uv0 + uv1 + uv2), alpha);
                        color.x *= colorLight;
                        color.y *= colorLight;
                        color.z *= colorLight;
                    }
                    else 
                    {
                        color = selectedTexture->getPixelColor((uv0 + uv1 + uv2), alpha);
                    }

                    DrawPixel(reinterpret_cast<Float4 *>(fb.GetColorBuffer()), fb.GetDepthBuffer(), fb.GetDepthColorBuffer(), fb.GetWidth(), fb.GetHeight(), x, y, z, far, near, color);
                }
            }

            if (orientedArea < 0)
            {
                float ccw0 = edgeFunc(x, y, vertices[2], vertices[1]);
                float ccw1 = edgeFunc(x, y, vertices[0], vertices[2]);
                float ccw2 = edgeFunc(x, y, vertices[1], vertices[0]);
                if (ccw0 <= 0 && ccw1 <= 0 && ccw2 <= 0)
                {
                    float total = ccw0 + ccw1 + ccw2; // normalize cw

                    float p0proximity = ccw0/total;
                    float p1proximity = ccw1/total;
                    float p2proximity = ccw2/total;
                    
                    float z = (vertices[0].z*p0proximity + vertices[1].z*p1proximity + vertices[2].z*p2proximity);
                    Float2 uv0 = uv[0] * p0proximity;
                    Float2 uv1 = uv[1] * p1proximity;
                    Float2 uv2 = uv[2] * p2proximity;  

                    if (isLightEnable)
                    {
                        float colorLight = 0;
                        for (int id = 0; id < lightCount; id++)
                        {
                            colorLight += p_lights[id].getColorLight(normal[0], cameraPosition, (myMaths::Float3){(float)x, (float)y, z}, 30);
                        }
                        
                        color = selectedTexture->getPixelColor((uv0 + uv1 + uv2), alpha);
                        color.x *= colorLight;
                        color.y *= colorLight;
                        color.z *= colorLight;
                    }
                    else 
                    {
                        color = selectedTexture->getPixelColor((uv0 + uv1 + uv2), alpha);
                    }

                    DrawPixel(reinterpret_cast<Float4 *>(fb.GetColorBuffer()), fb.GetDepthBuffer(), fb.GetDepthColorBuffer(), fb.GetWidth(), fb.GetHeight(), x, y, z, far, near, color);
                }
            }
        }
    }
}

void Renderer::DrawTriangle(rdrVertex *vertices, Light* p_lights)
{
    // Store triangle vertices positions
    Float4 localCoords[3] = {
        {vertices[0].x, vertices[0].y, vertices[0].z, 1.f},
        {vertices[1].x, vertices[1].y, vertices[1].z, 1.f},
        {vertices[2].x, vertices[2].y, vertices[2].z, 1.f},
    };
    
    Float4 worldCoords[3] = {
        { modelMatrix * localCoords[0] },
        { modelMatrix * localCoords[1] },
        { modelMatrix * localCoords[2] },
    };

    Float4 localNormal[3] = {
        {vertices[0].nx, vertices[0].ny, vertices[0].nz, 0.f},
        {vertices[1].nx, vertices[1].ny, vertices[1].nz, 0.f},
        {vertices[2].nx, vertices[2].ny, vertices[2].nz, 0.f},
    };
    

    Float4 worldNormal[3] = {
        { modelMatrix * localNormal[0] },
        { modelMatrix * localNormal[1] },
        { modelMatrix * localNormal[2] },
    };

    Float4 viewCoords[3] = {
        { viewMatrix * worldCoords[0] },
        { viewMatrix * worldCoords[1] },
        { viewMatrix * worldCoords[2] },
    };

    // Local space (v3) -> Clip space (v4)
    Float4 clipCoords[3] = {
        { projectionMatrix * viewCoords[0] },
        { projectionMatrix * viewCoords[1] },
        { projectionMatrix * viewCoords[2] },
    };

    // Clip space (v4) to NDC (v3)
    Float3 ndcCoords[3] = {
        {clipCoords[0].getHomogenized().getXYZF3()},
        {clipCoords[1].getHomogenized().getXYZF3()},
        {clipCoords[2].getHomogenized().getXYZF3()},
    };

    // NDC (v3) to screen coords (v2)
    Float3 screenCoords[3] = {
        {ndcToScreenCoords(ndcCoords[0], viewport)},
        {ndcToScreenCoords(ndcCoords[1], viewport)},
        {ndcToScreenCoords(ndcCoords[2], viewport)},
    };

    for (int i = 0; i < 3; i++)
    {
        screenCoords[i].z = viewCoords[i].z;
    }

    if (selectedTexture == nullptr)
    {
        // Draw triangle wireframe
        if (grandientColor && wireFrame)
        {
            Float4 lineColor1 = {vertices[0].r * 1.f, vertices[0].g * 1.f, vertices[0].b * 1.f, 1.f};
            Float4 lineColor2 = {vertices[1].r * 1.f, vertices[1].g * 1.f, vertices[1].b * 1.f, 1.f};
            Float4 lineColor3 = {vertices[2].r * 1.f, vertices[2].g * 1.f, vertices[2].b * 1.f, 1.f};
            DrawLine(screenCoords[0], screenCoords[1], lineColor1, lineColor2);
            DrawLine(screenCoords[1], screenCoords[2], lineColor2, lineColor3);
            DrawLine(screenCoords[2], screenCoords[0], lineColor3, lineColor1);
        }
        else if (wireFrame)
        {
            DrawLine(screenCoords[0], screenCoords[1], lineColor);
            DrawLine(screenCoords[1], screenCoords[2], lineColor);
            DrawLine(screenCoords[2], screenCoords[0], lineColor);
        }

        Float4 colors[3] = {
            {vertices[0].r, vertices[0].g, vertices[0].b, vertices[0].a},
            {vertices[1].r, vertices[1].g, vertices[1].b, vertices[1].a},
            {vertices[2].r, vertices[2].g, vertices[2].b, vertices[2].a}};

        if (!wireFrame)
            fillTriangle(screenCoords, worldCoords, colors, worldNormal, p_lights);
    }
    else 
    {
        if (wireFrame)
        {
            Float4 lineColor1 = {vertices[0].r * 1.f, vertices[0].g * 1.f, vertices[0].b * 1.f, 1.f};
            Float4 lineColor2 = {vertices[1].r * 1.f, vertices[1].g * 1.f, vertices[1].b * 1.f, 1.f};
            Float4 lineColor3 = {vertices[2].r * 1.f, vertices[2].g * 1.f, vertices[2].b * 1.f, 1.f};
            DrawLine(screenCoords[0], screenCoords[1], lineColor1, lineColor2);
            DrawLine(screenCoords[1], screenCoords[2], lineColor2, lineColor3);
            DrawLine(screenCoords[2], screenCoords[0], lineColor3, lineColor1);
        }
        else 
        {
            Float2 uv[3] = {
                {vertices[0].u, vertices[0].v},
                {vertices[1].u, vertices[1].v},
                {vertices[2].u, vertices[2].v},
            };

            fillTexturedTriangle(screenCoords, uv, worldNormal, p_lights, vertices[0].a);
        }
    }
}

void Renderer::DrawTriangles(rdrVertex *p_vertices, const uint p_count, Light* p_lights, const uint p_lightCount)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    lightCount = p_lightCount;
    int count = p_count;
    for (int i = 0; i < count; i += 3)
    {
        DrawTriangle(&p_vertices[i], p_lights);
    }
}
/*
void rdrSetImGuiContext(rdrImpl* renderer, struct ImGuiContext* context)
{
    ImGui::SetCurrentContext(context);
}*/

void Renderer::ShowImGuiControls()
{
    if (ImGui::CollapsingHeader("Triangle color", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::ColorEdit4("lineColor", &lineColor.x);

        if(ImGui::Button("Wireframe"))
            toggleWireframe();
        
        if(ImGui::Button("Toggle color mode"))
            toggleGrandientColor();
    }
}

void Renderer::toggleWireframe()
{
    if (wireFrame)
        wireFrame = false;
    else
        wireFrame = true;
}

void Renderer::toggleGrandientColor()
{
    if (grandientColor)
        grandientColor = false;
    else
        grandientColor = true;
}

void Renderer::setTexture(Texture* texture)
{
    selectedTexture = texture;
}

void Renderer::setCameraPos(myMaths::Float3 pos)
{
    cameraPosition = pos;
}

void Renderer::lightEnable(bool enable)
{
    isLightEnable = enable;
}