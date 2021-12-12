#include <stdio.h>
#include <algorithm>
#include "Color.h"

using namespace std;

Color::Color()
{
    red = green = blue = alpha = 0.0f;
}
    
Color::Color(float pRed, float pGreen, float pBlue, float pAlpha)
{
    red = pRed;
    green = pGreen;
    blue = pBlue;
    alpha = pAlpha;
    clamp();
}

void Color::clamp()
{
    red = min(red, 1.0f);
    red = max(red, 0.0f);
    green = min(green, 1.0f);
    green = max(green, 0.0f);
    blue = min(blue, 1.0f);
    blue = max(blue, 0.0f);
    alpha = min(alpha, 1.0f);
    alpha = max(alpha, 0.0f);
}

Color Color::operator+(Color &other)
{
    Color ans;
    ans.red = red + other.red;
    ans.green = green + other.green;
    ans.blue = blue + other.blue;
    ans.alpha = alpha + other.alpha;
    
    ans.clamp();
    
    return ans;
}

Color Color::operator-(Color &other)
{
    Color ans;
    ans.red = red - other.red;
    ans.green = green - other.green;
    ans.blue = blue - other.blue;
    ans.alpha = alpha - other.alpha;
    
    ans.clamp();
    
    return ans;
}

Color Color::operator*(float other)
{
    Color ans;
    ans.red = red * other;
    ans.green = green * other;
    ans.blue = blue * other;
    ans.alpha = alpha * other;
    
    ans.clamp();
    
    return ans;
}

Color Color::operator*(Color other){
    Color ans;
    ans.red = red * other.red;
    ans.green = green * other.green;
    ans.blue = blue * other.blue;
    ans.alpha = alpha * other.alpha;

    ans.clamp();
    return ans;
}

Color Color::operator/(float other){
    Color ans;
    ans.red = red / other;
    ans.green = green / other;
    ans.blue = blue / other;
    ans.alpha = alpha / other;
    
    ans.clamp();
    
    return ans;
}
