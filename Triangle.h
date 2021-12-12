#ifndef Triangle_h
#define Triangle_h

#include "Vector.h"
#include "Color.h"
#include "Matrix.h"

struct Triangle3D;

struct Triangle2D {
  Vector2 v1, v2, v3;
  Color c1, c2, c3;

  Triangle2D();
  Triangle2D(Triangle3D triangle3D);
  Triangle2D(Vector2 pV1, Vector2 pV2, Vector2 pV3, Color pC1, Color pC2, Color pC3);

  void calculateBarycentricCoordinates(Vector2 P, float &lambda1, float &lambda2, float &lambda3);
};

struct Triangle3D {
    Vector4 v1, v2, v3;
    Color c1, c2, c3;
    bool shouldDraw;

    Triangle3D();
    Triangle3D(Vector4 pV1, Vector4 pV2, Vector4 pV3, Color pC1, Color pC2, Color pC3);
    void Transform(Matrix4 transformMatrix);
    void SetTriangleColor(Color pC1, Color pC2, Color pC3);
};

#endif