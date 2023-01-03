#pragma once

#include <myMaths.hpp>


class Light
{
private:
    myMaths::Float3 vecLight;
    myMaths::Float4 colorLight;

    float iA;
    float iD;
    float iS;

    float getAmbiant();
    myMaths::Float3 getColorDiffuse(myMaths::Float4 normal, myMaths::Float3 posPixel);
    float getDiffuse(myMaths::Float4 normal, myMaths::Float3 posPixel);
    myMaths::Float3 getColorSpecular(myMaths::Float4 normal, myMaths::Float3 cameraPosition, myMaths::Float3 posPixel, int shine);
    float getSpecular(myMaths::Float4 normal, myMaths::Float3 cameraPosition, myMaths::Float3 posPixel, int shine);
public:

    void setPosition(myMaths::Float3 pos);
    void setColor(myMaths::Float4 color);
    void setParameters(float ambIntensity, float diffIntensity, float speIntensity);

    float getColorLight(myMaths::Float4 normal, myMaths::Float3 cameraPosition, myMaths::Float3 posPixel, int shine);
    myMaths::Float3 getColorLight2(myMaths::Float4 normal, myMaths::Float3 cameraPosition, myMaths::Float3 posPixel, int shine);
};

