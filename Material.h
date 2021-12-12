#ifndef Material_H
#define Material_H

#include "Color.h"

struct Material{
    Color ambientReflectiveness;
    Color diffuseReflectiveness; 
    Color specularReflectiveness;
    float shininess;

    Material();
    Material(Color pAmbientReflectiveness, Color pDiffuseReflectiveness, Color pSpecularReflectiveness, float pShininess);
};

#endif