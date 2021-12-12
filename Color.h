#ifndef Color_h
#define Color_h

#define Red Color(1.0f, 0.0f, 0.0f, 1.0f)
#define Green Color(0.0f, 1.0f, 0.0f, 1.0f)
#define Blue Color(0.0f, 0.0f, 1.0f, 1.0f)
#define White Color(1.0f, 1.0f, 1.0f, 1.0f)
#define Black Color(0.0f, 0.0f, 0.0f, 1.0f)

struct Color
{
    float red, green, blue, alpha;
    
    Color();
    
    Color(float pRed, float pGreen, float pBlue, float pAlpha);
    
    void clamp();
    
    Color operator+(Color &other);
    Color operator-(Color &other);
    Color operator*(float other);
    Color operator*(Color other);
    Color operator/(float other);
    
};

#endif /* Color_h */
