#include "Triangle.h"

Triangle2D::Triangle2D() {
    v1 = Vector2();
    v2 = Vector2();
    v3 = Vector2();
    c1 = c2 = c3 = Black;
}

Triangle2D::Triangle2D(Vector2 pV1, Vector2 pV2, Vector2 pV3, Color pC1, Color pC2, Color pC3) {
    v1 = pV1;
    v2 = pV2;
    v3 = pV3;
    c1 = pC1;
    c2 = pC2;
    c3 = pC3;   
}

Triangle2D::Triangle2D(Triangle3D triangle3D)
{
    v1 = Vector2(triangle3D.v1.x, triangle3D.v1.y);   
    v2 = Vector2(triangle3D.v2.x, triangle3D.v2.y);   
    v3 = Vector2(triangle3D.v3.x, triangle3D.v3.y);  
    c1 = triangle3D.c1; 
    c2 = triangle3D.c2; 
    c3 = triangle3D.c3; 
}

void Triangle2D::calculateBarycentricCoordinates(Vector2 P, float &lambda1, float &lambda2, float &lambda3){
    Vector2 V3V1 = v1 - v3;
    Vector2 V3V2 = v2 - v3;
    float triangleArea = determinant(V3V1, V3V2)/2.0f;

    Vector2 Pv1 = v1 - P;
    Vector2 Pv2 = v2 - P;
    Vector2 Pv3 = v3 - P;
    float area1 = determinant(Pv1, Pv2) / 2.0f;
    float area2 = determinant(Pv2, Pv3) / 2.0f;

    lambda1 = area1/triangleArea;
    lambda2 = area2/triangleArea;
    lambda3 = 1.0f - lambda1 - lambda2;
}

Triangle3D::Triangle3D(){
    v1 = Vector4(0, 0, 0, 1); 
    v2 = Vector4(0, 0, 0, 1); 
    v3 = Vector4(0, 0, 0, 1); 
    c1 = c2 = c3 = White;
    shouldDraw = true;
}

Triangle3D::Triangle3D(Vector4 pV1, Vector4 pV2, Vector4 pV3,
                      Color pC1, Color pC2, Color pC3)
{
    v1 = pV1; 
    v2 = pV2; 
    v3 = pV3; 
    c1 = pC1;
    c2 = pC2;
    c3 = pC3;
    shouldDraw = true;
}

void Triangle3D::Transform(Matrix4 transformMatrix)
{
    v1 = transformMatrix * v1;   
    v2 = transformMatrix * v2;   
    v3 = transformMatrix * v3;    
}

void Triangle3D::SetTriangleColor(Color pC1, Color pC2, Color pC3){
    c1 = pC1;
    c2 = pC2;
    c3 = pC3;
}