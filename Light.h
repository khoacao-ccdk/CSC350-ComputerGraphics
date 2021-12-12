#ifndef Light_H
#define Light_H
#include "Vector.h"
#include "Color.h"

struct Light{
    Vector4 position;
    Color ambientIntensity;
    Color diffuseIntensity;
    Color specularIntensity;

    Light();
    Light(Vector4 pPosition, Color pAmbientIntensity, Color pDiffuseIntensity, Color pSpecularIntensity);
};

#endif