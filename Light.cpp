#include "Light.h"

Light::Light(){
    position = Vector4();
    ambientIntensity = Color();
    diffuseIntensity = Color();
    specularIntensity = Color();
};

Light::Light(Vector4 pPosition, Color pAmbientIntensity, Color pDiffuseIntensity, Color pSpecularIntensity){
    position = pPosition;
    ambientIntensity = pAmbientIntensity;
    diffuseIntensity = pDiffuseIntensity;
    specularIntensity = pSpecularIntensity;
};