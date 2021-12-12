#include "Matrix.h"
#include <iostream>
#include <math.h>
using namespace std;

Matrix4::Matrix4()
{
    //1st column
    ix = 1;
    iy = 0;
    iz = 0;
    iw = 0;

    //2nd column
    jx = 0;
    jy = 1;
    jz = 0;
    jw = 0;

    //3rd column
    kx = 0;
    ky = 0;
    kz = 1;
    kw = 0;

    //4th column
    ox = 0;
    oy = 0;
    oz = 0;
    ow = 1;
};

Matrix4::Matrix4( 
  float Ix, float Jx, float Kx, float Ox,
  float Iy, float Jy, float Ky, float Oy,
  float Iz, float Jz, float Kz, float Oz,
  float Iw, float Jw, float Kw, float Ow)
{
    //1st column
    ix = Ix;
    iy = Iy;
    iz = Iz;
    iw = Iw;

    //2nd column
    jx = Jx;
    jy = Jy;
    jz = Jz;
    jw = Jw;

    //3rd column
    kx = Kx;
    ky = Ky;
    kz = Kz;
    kw = Kw;

    //4th column
    ox = Ox;
    oy = Oy;
    oz = Oz;
    ow = Ow;
};

Vector4 Matrix4::operator*(Vector4 &other)
{
    Vector4 result;

    result.x = other.x * ix + other.y * jx + other.z * kx + other.w * ox;
    result.y = other.x * iy + other.y * jy + other.z * ky + other.w * oy;
    result.z = other.x * iz + other.y * jz + other.z * kz + other.w * oz;
    result.w = other.x * iw + other.y * jw + other.z * kw + other.w * ow;

    return result;
};

Matrix4 Matrix4::operator*(Matrix4 &other)
{
    Matrix4 result;
    Vector4 firstColumn = Vector4(other.ix, other.iy, other.iz, other.iw);
    Vector4 secondColumn = Vector4(other.jx, other.jy, other.jz, other.jw);
    Vector4 thirdColumn = Vector4(other.kx, other.ky, other.kz, other.kw);
    Vector4 fourthColumn = Vector4(other.ox, other.oy, other.oz, other.ow);

    //Perform matrix * vector multiplication for each column of the other matrix
    firstColumn =  (*this) * firstColumn;
    secondColumn = (*this) * secondColumn;
    thirdColumn = (*this) * thirdColumn;
    fourthColumn = (*this) * fourthColumn;

    //First column of the result matrix
    result.ix = firstColumn.x;
    result.iy = firstColumn.y;
    result.iz = firstColumn.z;
    result.iw = firstColumn.w;

    //Second column of the result matrix
    result.jx = secondColumn.x;
    result.jy = secondColumn.y;
    result.jz = secondColumn.z;
    result.jw = secondColumn.w;

    //Third column of the result matrix
    result.kx = thirdColumn.x;
    result.ky = thirdColumn.y;
    result.kz = thirdColumn.z;
    result.kw = thirdColumn.w;

    //Fourth column of the result matrix
    result.ox = fourthColumn.x;
    result.oy = fourthColumn.y;
    result.oz = fourthColumn.z;
    result.ow = fourthColumn.w;

    return result;
};

Matrix4 Translate3D(float tX, float tY, float tZ)
{
    Matrix4 result = Matrix4( 1, 0, 0, tX,
                              0, 1, 0, tY,
                              0, 0, 1, tZ,
                              0, 0, 0, 1);
    return result;
}

Matrix4 Scale3D(float tX, float tY, float tZ)
{
    Matrix4 result = Matrix4( tX, 0, 0, 0,
                              0, tY, 0, 0,
                              0, 0, tZ, 0,
                              0, 0, 0, 1);
    return result;
}

void Matrix4::print()
{
    cout << ix << " " << jx << " " << kx << " " << ox << endl;
    cout << iy << " " << jy << " " << ky << " " << oy << endl;
    cout << iz << " " << jz << " " << kz << " " << oz << endl;
    cout << iw << " " << jw << " " << kw << " " << ow << endl;
}

Matrix4 RotateX3D(float deg)
{
    float rad = deg * M_PI / 180.0f;
    Matrix4 result = Matrix4( 1, 0,         0,        0,
                              0, cos(rad),  sin(rad), 0,
                              0, -sin(rad), cos(rad), 0,
                              0, 0,         0,        1);
    return result;
}

Matrix4 RotateY3D(float deg)
{
    float rad = deg * M_PI / 180.0f;
    Matrix4 result = Matrix4( cos(rad), 0, -sin(rad),0,
                              0,        1, 0,        0,
                              sin(rad), 0, cos(rad), 0,
                              0,        0, 0,        1);
    return result;
}

Matrix4 RotateZ3D(float deg)
{
    float rad = deg * M_PI / 180.0f;
    Matrix4 result = Matrix4( cos(rad),  sin(rad), 0, 0,
                              -sin(rad), cos(rad), 0, 0,
                              0,         0,        1, 0,
                              0,         0,        0, 1);
    return result;
}

Matrix4 Rotate3D(float degX, float degY, float degZ)
{
    Matrix4 rotateX = RotateX3D(degX);
    Matrix4 rotateY = RotateX3D(degY);
    Matrix4 rotateZ = RotateX3D(degZ);
    Matrix4 result = (rotateX * rotateY) * rotateZ;

    return result;
}

Matrix4 Rotate3D(float deg, Vector4 vec)
{
    float alpha = atanf(vec.x / vec.z) * 180.0 / M_PI;
    float beta  = acosf(vec.y / vec.magnitude()) * 180.0 / M_PI;
    Matrix4 matrix1 = RotateY3D(alpha);
    Matrix4 matrix2 = RotateX3D(beta);
    Matrix4 matrix3 = RotateY3D(deg);
    Matrix4 matrix4 = RotateX3D(-beta);
    Matrix4 matrix5 = RotateY3D(-alpha);

    Matrix4 result = matrix5 * matrix4 * matrix3 * matrix2 * matrix1;

    return result;
}

Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up)
{
    Vector4 _look = (spot - eye).normalize();
    Vector4 _right = _look.cross(up).normalize();
    Vector4 _up = _right.cross(_look);

    Matrix4 result = Matrix4(_right.x, _right.y, _right.z, -eye.x,
                            _up.x,    _up.y,    _up.z,    -eye.y,
                            -_look.x, -_look.y, -_look.z, -eye.z,
                            0,        0,        0,        1);
   
    return result;
}

Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    Matrix4 step1 = Translate3D(-(minX + maxX) / 2.0, 
                                -(minY + maxY) / 2.0,
                                -(minZ + maxZ) / 2.0);
    Matrix4 step2 = Scale3D(2.0 / (maxX - minX),
                            2.0 / (maxY - minY), 
                            2.0 / (maxZ - minZ));
    Matrix4 result = step2 * step1;
    return result;
}

Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ){
    fovY = fovY * PI / 180.0;
    float F = 1.0 / (tan(fovY / 2.0));
    
    Matrix4 result = Matrix4(F/aspect, 0, 0,                             0,
                             0,        F, 0,                             0,
                             0,        0, (nearZ + farZ)/(nearZ - farZ), (2.0 * nearZ * farZ)/(nearZ - farZ),
                             0,        0, -1,                            0);
    return result;
}

Matrix4 Viewport(float x, float y, float width, float height)
{
    Matrix4 step1 = Translate3D(1, 1, -1);
    Matrix4 step2 = Scale3D(0.5, 0.5, 0.5);
    Matrix4 step3 = Scale3D(width, height, 1);
    Matrix4 step4 = Translate3D(x, y, 0);
    
    Matrix4 result = step4 * step3 * step2 * step1;
    return result;
}

