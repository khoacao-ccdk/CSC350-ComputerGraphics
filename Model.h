#ifndef Model_h
#define Model_h

#include <vector>
#include <string>
#include "Triangle.h"
#include "Matrix.h"
#include "Color.h"
#include "Material.h"
#include "Light.h"

using namespace std;

class Model
{
  vector<Triangle3D> triangles;
  Material myMaterial;
  public: 
    Model();
    int numTriangles();
    Triangle3D operator[](int i);
    void transform(Matrix4 transformMatrix);
    void readFromOBJFile(string filepath, Color pFillColor);
    void homogenize();
    void performBackfaceCulling(Vector4 eye, Vector4 spot);
    void setMaterial(Material pMaterial);
    void applyLighting(Light L, Vector4 V);
};

#endif 
