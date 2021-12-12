#include "Material.h"

Material::Material(){
    ambientReflectiveness = Color();
    diffuseReflectiveness = Color();
    specularReflectiveness = Color();
    shininess = 0.0f;
};

Material::Material(Color pAmbientReflectiveness, Color pDiffuseReflectiveness, Color pSpecularReflectiveness, float pShininess){
    ambientReflectiveness = pAmbientReflectiveness;
    diffuseReflectiveness = pDiffuseReflectiveness;
    specularReflectiveness = pSpecularReflectiveness;
    shininess = pShininess; 
};