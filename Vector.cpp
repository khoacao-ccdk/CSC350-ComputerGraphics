//
//  Vector.cpp
//  Project1
//
//  Created by Hoang Pham on 9/27/21.
//

#include "Vector.h"
#include <math.h>

Vector2::Vector2()
{
    x = y = 0.0f;
}

Vector2::Vector2(float X, float Y)
{
    x = X;
    y = Y;
}

Vector2 Vector2::operator*(float other)
{
    Vector2 result;
    
    result.x = x * other;
    result.y = y * other;
    
    return result;
}

Vector2 Vector2::operator-(Vector2 &other)
{
    Vector2 result;
    
    result.x = x - other.x;
    result.y = y - other.y;
    
    return result;
}

Vector2 Vector2::operator+(Vector2 &other)
{
    Vector2 result;
    
    result.x = x + other.x;
    result.y = y + other.y;
    
    return result;
}

float Vector2::magnitude()
{
    float result = sqrt((x * x + y * y));
    
    return result;
}

float Vector2::dot(Vector2 &other)
{
    float result = x * other.x + y * other.y;

    return result;
}

Vector2 Vector2::normalize()
{
    Vector2 result;
    
    float mag = magnitude();

    result.x = (float) (x / mag);
    result.y = (float) (y / mag);

    return result;
}

Vector2 Vector2::perpendicular()
{
    Vector2 result;
    
    result.x = -y;
    result.y = x;

    return result;
}

float determinant(Vector2 a, Vector2 b)
{
    float result = b.x * a.y - a.x * b.y;

    return result;
}

Vector4::Vector4()
{
    x = y = z = w = 0;
}

Vector4::Vector4(float X, float Y, float Z, float W)
{
    x = X;
    y = Y;
    z = Z;
    w = W; 
}

Vector4 Vector4::operator*(float other)
{
    Vector4 result;

    result.x = x * other;
    result.y = y * other;
    result.z = z * other;
    result.w = w * other;

    return result;
}

Vector4 Vector4::operator+(Vector4 &other)
{
    Vector4 result;

    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;
    result.w = w + other.w;

    return result;
}

Vector4 Vector4::operator-(Vector4 &other)
{
    Vector4 result;

    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;
    result.w = w - other.w;

    return result;
}

float Vector4::magnitude()
{
    return sqrt((x * x) + (y * y) + (z * z));
}

Vector4 Vector4::normalize()
{
    Vector4 result;

    result.x = x / magnitude();
    result.y = y / magnitude();
    result.z = z / magnitude();
    result.w = w / magnitude();

    return result;
}

float Vector4::dot(Vector4 &other)
{
    return x * other.x + y * other.y + z * other.z + w * other.w;  
}

/*

aybz
- azby
azbx
- axbz
axby
- aybx
*/
Vector4 Vector4::cross(Vector4 &other)
{
    Vector4 result;
    
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
    
    return result;
}

Vector4 Bisector(Vector4 a, Vector4 b){
    return (a + b).normalize();
}