#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

Model::Model()
{
  triangles.resize(0);
}

int Model::numTriangles()
{
  return triangles.size();
}

Triangle3D Model::operator[](int i)
{
  return triangles[i];
}

void Model::transform(Matrix4 transformMatrix)
{
  for (int i = 0; i < triangles.size(); i++){
    if(triangles[i].shouldDraw)
      triangles[i].Transform(transformMatrix);
  }
}

void Model::readFromOBJFile(string filepath, Color pFillColor)
{
  vector<Vector4> vertices;
  vertices.push_back(Vector4(0, 0, 0, 0));
  
  ifstream myFile(filepath);
  if (myFile.is_open())
  {
    string line;
    while (getline(myFile, line))
    {
      vector<string> a;
      stringstream ss(line);
      string st;
      while (ss >> st){
        a.push_back(st);
      }
          

      switch (a[0][0])
      {
        case 'v':{
          float x = stof(a[1]);
          float y = stof(a[2]);
          float z = stof(a[3]);
          Vector4 vertex(x, y, z, 1.0);

          vertices.push_back(vertex);
          break;
        }

        case 'f':{
          if (a.size() == 4)
          {
            Vector4 vertex1 = vertices[stoi(a[1])];
            Vector4 vertex2 = vertices[stoi(a[2])];
            Vector4 vertex3 = vertices[stoi(a[3])];
            Triangle3D face(vertex1, vertex2, vertex3, pFillColor, pFillColor, pFillColor);
            triangles.push_back(face);
          } 
          else
          { 
            Vector4 vertex1 = vertices[stoi(a[1])];
            Vector4 vertex2 = vertices[stoi(a[2])];
            Vector4 vertex3 = vertices[stoi(a[3])];
            Vector4 vertex4 = vertices[stoi(a[4])];
            Triangle3D face1(vertex1, vertex2, vertex3, pFillColor, pFillColor, pFillColor);
            Triangle3D face2(vertex1, vertex3, vertex4, pFillColor, pFillColor, pFillColor);
          
            triangles.push_back(face1);
            triangles.push_back(face2);
          }         
          break;
        }
        default: 
          break;
      }
    }
    myFile.close();
  } 
}

void Model::homogenize(){
    for(int i = 0; i < triangles.size(); i++){
      float homogenous = triangles[i].v1.w;
      triangles[i].v1.x /= homogenous;
      triangles[i].v1.y /= homogenous;
      triangles[i].v1.z /= homogenous;
      triangles[i].v1.w = 1;
     
      homogenous = triangles[i].v2.w;
      triangles[i].v2.x /= homogenous;
      triangles[i].v2.y /= homogenous;
      triangles[i].v2.z /= homogenous;
      triangles[i].v2.w = 1;

      homogenous = triangles[i].v3.w;
      triangles[i].v3.x /= homogenous;
      triangles[i].v3.y /= homogenous;
      triangles[i].v3.z /= homogenous;
      triangles[i].v3.w = 1;
    } 
};

void Model::performBackfaceCulling(Vector4 eye, Vector4 spot){
    Vector4 look = (spot - eye).normalize();
    for(int i = 0; i<triangles.size(); i++){
      Triangle3D &triangle = triangles[i];
      Vector4 twoToOne = triangle.v1 - triangle.v2;
      Vector4 twoToThree = triangle.v3 - triangle.v2;
      Vector4 normal = (twoToOne.cross(twoToThree)).normalize();
      if(look.dot(normal) > 0){
        triangle.shouldDraw = false;
      } 
    }
};

void Model::setMaterial(Material pMaterial){
    myMaterial = pMaterial;
};

void Model::applyLighting(Light L, Vector4 V){
    //Get ambient color that applies to all points
    Color lAmbient = L.ambientIntensity * myMaterial.ambientReflectiveness;

    for(Triangle3D &triangle : triangles){
      Vector4 l = (L.position - triangle.v1).normalize();
      Vector4 h = (V - triangle.v1).normalize();
      Vector4 v2Tov1 = triangle.v1 - triangle.v2;
      Vector4 v2Tov3 = triangle.v3 - triangle.v2;
      Vector4 n = v2Tov3.cross(v2Tov1).normalize();
      Vector4 b = Bisector(l, h).normalize();

      Color lDiffuse = (L.diffuseIntensity / pow((l.magnitude()), 2) * myMaterial.diffuseReflectiveness) * fmax(0, l.dot(n));

      Color lSpecular = (L.specularIntensity / pow((l.magnitude()), 2) * myMaterial.specularReflectiveness) * fmax(0, n.dot(b));   
      
      Color lOverall = lAmbient + lDiffuse + lSpecular;

      triangle.SetTriangleColor(lOverall, lOverall, lOverall);
    }  
};
