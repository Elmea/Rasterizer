#include<cstring>

#include <Framebuffer.hpp>
#include <myMaths.hpp>

Framebuffer::Framebuffer(int p_width, int p_height)
    : width(p_width)
    , height(p_height)
    , colorBuffer(p_width* p_height)
    , depthBuffer(p_width* p_height)
    , colorDepthBuffer(p_width* p_height)
{
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Framebuffer::~Framebuffer()
{
    glDeleteTextures(1, &colorTexture);
}

void Framebuffer::Clear()
{
    // Sadly too slow...
    //std::fill(colorBuffer.begin(), colorBuffer.end(), clearColor);
    //std::fill(depthBuffer.begin(), depthBuffer.end(), 0.f);

    // Clear color buffer
    {
        myMaths::Float4* colors = colorBuffer.data();

        // Fill the first line with the clear color
        for (int i = 0; i < width; ++i)
            std::memcpy(&colors[i], &clearColor, sizeof(myMaths::Float4));

        // Copy the first line onto every line
        for (int i = 1; i < height; ++i)
            std::memcpy(&colors[i * width], &colors[0], width * sizeof(myMaths::Float4));
    }

    {
        myMaths::Float4* depth = colorDepthBuffer.data();
        myMaths::Float4 depthClearColor = { 0.f, 0.f, 0.f, 1.f };

        // Fill the first line with the clear color
        for (int i = 0; i < width; ++i)
            std::memcpy(&depth[i], &depthClearColor, sizeof(myMaths::Float4));

        // Copy the first line onto every line
        for (int i = 1; i < height; ++i)
            std::memcpy(&depth[i * width], &depth[0], width * sizeof(myMaths::Float4));
    }

    // Clear depth buffer
    {
        depthBuffer.assign(depthBuffer.size(), 2000000000);
    }
}

void Framebuffer::UpdateTexture()
{
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, colorBuffer.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, colorDepthBuffer.data());
    glBindTexture(GL_TEXTURE_2D, 0);
}
