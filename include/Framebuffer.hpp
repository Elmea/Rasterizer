#pragma once

#include <vector>
#include <glad/gl.h>
#include <types.hpp>

#include <myMaths.hpp>

class Framebuffer
{
private:
    int width = 0;
    int height = 0;

    // In-RAM buffers
    std::vector<myMaths::Float4> colorBuffer;
    std::vector<float> depthBuffer;
    std::vector<myMaths::Float4> colorDepthBuffer;

    // OpenGL texture (in VRAM)
    GLuint colorTexture = 0;
    GLuint depthTexture = 1;

public:
    myMaths::Float4 clearColor = { 0.f, 0.f, 0.f, 0.3f };

    Framebuffer(int width, int height);
    ~Framebuffer();

    void Clear();
    void UpdateTexture();

    float* GetColorBuffer() { return reinterpret_cast<float*>(colorBuffer.data()); }
    float* GetDepthBuffer() { return depthBuffer.data(); }
    myMaths::Float4* GetDepthColorBuffer() { return colorDepthBuffer.data(); }
    
    int GetWidth()  const   { return width; }
    int GetHeight() const   { return height; }

    GLuint GetColorTexture() const { return colorTexture; }
    GLuint GetDepthTexture() const { return depthTexture; }


};