#include <texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Texture::loadTexture(const char* filename)
{
    int channel;
    stbi_set_flip_vertically_on_load(true);
    float* input = stbi_loadf(filename, &width, &height, &channel, STBI_rgb_alpha);
    colors = (myMaths::Float4*)input;
}

myMaths::Float4 Texture::getPixelColor(myMaths::Float2 uv, float alpha)
{
    float s = uv.x * width;
    float t = uv.y * height;
    int res = (int)s + (int)t * width;

    if (res > (int)(width * height))
        return {0.f, 0.f, 0.f, 1.f};

    myMaths::Float4 result = colors[res];
    result.w = alpha;

    return result;
}

