#pragma once 

#include <myMaths.hpp>
#include <cstdlib>

class Texture
{
private:
    int width;
    int height;
    myMaths::Float4* colors;
public:
    void loadTexture(const char* filename);
    myMaths::Float4 getPixelColor(myMaths::Float2 uv, float alpha);

    ~Texture() { free(colors); };
};