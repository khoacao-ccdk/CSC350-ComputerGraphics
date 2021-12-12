#ifndef Matrix_h
#define Matrix_h
#define PI 3.14159265
#include "Vector.h"

struct Matrix4
{
    float ix, jx, kx, ox,
          iy, jy, ky, oy,
          iz, jz, kz, oz,
          iw, jw, kw, ow;

    Matrix4();
    Matrix4(
      float Ix, float Jx, float Kx, float Ox,
      float Iy, float Jy, float Ky, float Oy,
      float Iz, float Jz, float Kz, float Oz,
      float Iw, float Jw, float Kw, float Ow
    );
    
    Vector4 operator*(Vector4 &other);
    Matrix4 operator*(Matrix4 &other);
    
    void print();
};
Matrix4 Translate3D(float tX, float tY, float tZ);
Matrix4 Scale3D(float sX, float sY, float sZ);
Matrix4 RotateX3D(float deg);
Matrix4 RotateY3D(float deg);
Matrix4 RotateZ3D(float deg);
Matrix4 Rotate3D(float degX, float degY, float degZ);
Matrix4 Rotate3D(float deg, Vector4 vec);
Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up);
Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ);
Matrix4 Viewport(float x, float y, float width, float height);


#endif
