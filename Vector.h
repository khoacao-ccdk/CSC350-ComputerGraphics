//
//  Vector2.h
//  Project1
//
//  Created by Hoang Pham on 9/27/21.
//

#ifndef Vector_h
#define Vector_h


struct Vector2
{
    float x, y;
    
    Vector2();
    Vector2(float X, float Y);
    Vector2 operator*(float other);
    Vector2 operator+(Vector2 &other);
    Vector2 operator-(Vector2 &other);
    float magnitude();
    float dot(Vector2 &other);
    Vector2 normalize();
    Vector2 perpendicular();
};

float determinant(Vector2 a, Vector2 b);

struct Vector4{
  float x, y, z, w;

  Vector4();
  Vector4(float X, float Y, float Z, float W);
  Vector4 operator*(float other);
  Vector4 operator+(Vector4 &other);
  Vector4 operator-(Vector4 &other);
  float magnitude();
  float dot(Vector4 &other);
  Vector4 normalize();
  Vector4 cross(Vector4 &other);
};

Vector4 Bisector(Vector4 a, Vector4 b);

#endif /* Vector_h */
