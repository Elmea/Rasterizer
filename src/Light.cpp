#include <Light.hpp>
#include <math.h>
#include <cstdio>

float Light::getAmbiant()
{
    return iA;
}

float Light::getDiffuse(myMaths::Float4 normal, myMaths::Float3 posPixel)// N = Normal, L = vecteur Lumiere
{   
    myMaths::Float3 posLight = vecLight - posPixel;
    myMaths::Float3 vecNormal = normal.getXYZF3() - posPixel;

    float angleTheta = posLight.dotProduct(vecNormal) / (posLight.magnitude() * vecNormal.magnitude());
    return angleTheta * iD;
}

myMaths::Float3 Light::getColorDiffuse(myMaths::Float4 normal, myMaths::Float3 posPixel)// N = Normal, L = vecteur Lumiere
{   
    myMaths::Float3 posLight = vecLight - posPixel;
    myMaths::Float3 vecNormal = normal.getXYZF3() - posPixel;
    float angleTheta = posLight.dotProduct(vecNormal) / (posLight.magnitude() * vecNormal.magnitude());

    myMaths::Float3 intensiyDiffuse = {angleTheta * iD * colorLight.x, angleTheta * iD * colorLight.y, angleTheta * iD * colorLight.z};

    return intensiyDiffuse;
}

myMaths::Float3 Light::getColorSpecular(myMaths::Float4 normal, myMaths::Float3 cameraPosition, myMaths::Float3 posPixel, int shine)// R = direction dans laquelle serait réfléchie la lumière, V = la direction de vue de l'observateur
{
    myMaths::Float3 posLight = vecLight - posPixel;
    myMaths::Float3 vecNormal = normal.getXYZF3() - posPixel;
    float angleTheta = posLight.dotProduct(vecNormal) / (posLight.magnitude() * vecNormal.magnitude());
    
    myMaths::Float3 vecView = cameraPosition - posPixel;
    float multiplier2 = 2.f;
    myMaths::Float3 vecReflection = normal.getXYZF3() * multiplier2 * angleTheta - posLight;
    myMaths::Float3 vecHalfway = posLight + vecView;
    vecHalfway.normalize(); 
    float angleOmega = vecView.dotProduct(vecReflection) / (vecView.magnitude() * vecReflection.magnitude());
    
    myMaths::Float3 intensiySpecular {iS * pow(angleOmega, shine)*colorLight.x, iS * pow(angleOmega, shine)*colorLight.y, iS * pow(angleOmega, shine)*colorLight.z};
    return intensiySpecular;
}

float Light::getSpecular(myMaths::Float4 normal, myMaths::Float3 cameraPosition, myMaths::Float3 posPixel, int shine)// R = direction dans laquelle serait réfléchie la lumière, V = la direction de vue de l'observateur
{
    myMaths::Float3 posLight = vecLight - posPixel;
    myMaths::Float3 vecNormal = normal.getXYZF3() - posPixel;
    float angleTheta = posLight.dotProduct(vecNormal) / (posLight.magnitude() * vecNormal.magnitude());
    
    myMaths::Float3 vecView = cameraPosition - posPixel;
    float multiplier2 = 2.f;
    myMaths::Float3 vecReflection = normal.getXYZF3() * multiplier2 * angleTheta - posLight;
    myMaths::Float3 vecHalfway = posLight + vecView;
    vecHalfway.normalize(); 
    float angleOmega = vecView.dotProduct(vecReflection) / (vecView.magnitude() * vecReflection.magnitude());
    
    float intensiySpecular  = iS * pow(angleOmega, shine);
    return intensiySpecular;
}

float Light::getColorLight(myMaths::Float4 normal, myMaths::Float3 cameraPosition, myMaths::Float3 posPixel, int shine)
{
    return getAmbiant() + getDiffuse(normal, posPixel) + getSpecular(normal, cameraPosition, posPixel, shine);
}

myMaths::Float3 Light::getColorLight2(myMaths::Float4 normal, myMaths::Float3 cameraPosition, myMaths::Float3 posPixel, int shine)
{
    myMaths::Float3 ColorSpecular = getColorSpecular(normal, cameraPosition, posPixel, shine);
    myMaths::Float3 ColorDiffuse = getColorDiffuse(normal, posPixel);
    float intensity = getAmbiant();
    myMaths::Float3 lightIntensity = {intensity + ColorSpecular.x + ColorDiffuse.x, intensity + ColorSpecular.y + ColorDiffuse.y, intensity + ColorSpecular.z + ColorDiffuse.z};
    return lightIntensity;
}

void Light::setParameters(float ambIntensity, float diffIntensity, float speIntensity)
{
    iA = ambIntensity;
    iD = diffIntensity;
    iS = speIntensity;
}


void Light::setPosition(myMaths::Float3 pos)
{
    vecLight = pos;
}

void Light::setColor(myMaths::Float4 color)
{
    colorLight = color;
}

