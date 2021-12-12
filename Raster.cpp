#include "Raster.h"
#include "Vector.h"
#include "Triangle.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <limits>

using namespace std;

Raster::Raster() {
	width = 0;
	height = 0;
	pixels = nullptr;
  depthPixels = nullptr;
};

Raster::Raster(int pWidth, int pHeight, Color pFillColor) {
	width = pWidth;
	height = pHeight;
	pixels = new Color[width * height];
  depthPixels = new float[width * height];
	for (int i = 0; i < (width * height); i++) {
		pixels[i] = pFillColor;
	};
  for (int i = 0; i < (width * height); i++) {
		depthPixels[i] = numeric_limits<float>::max();
	};
};

Raster::~Raster() {
	delete[] pixels;
  delete[] depthPixels;
};

int Raster::getHeight() {
	return height;
};

int Raster::getWidth() {
	return width;
};

Color Raster::getColorPixel(int x, int y) {
	int index = (height - 1 - y) * width + x;
	return pixels[index];
};

void Raster::setColorPixel(int x, int y, Color pFillColor) {
	int index = (height - 1 - y) * width + x;
	pixels[index] = pFillColor;
};

float Raster::getDepthPixel(int x, int y)
{
  int index = (height - 1 - y) * width + x;
	return depthPixels[index];
}

void Raster::setDepthPixel(int x, int y, float depth)
{
  int index = (height - 1 - y) * width + x;
	depthPixels[index] = depth;
}

void Raster::clear(Color pFillColor) {
	for (int i = 0; i < height * width; i++)
		pixels[i] = pFillColor;

};

void Raster::clear(float depth)
{
  for (int i = 0; i < (width * height); i++)
		depthPixels[i] = depth;
}


void Raster::writeToPPM() {
	ofstream myFile;
	myFile.open("FRAME_BUFFER.ppm");

	myFile
		<< "P3 \n"
		<< width << " " << height << "\n"
		<< "255 \n";

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
      Color temp = getColorPixel(j, height - i - 1);

			myFile
				<< (int)round(temp.red * 255) << " "
				<< (int)round(temp.green * 255) << " "
				<< (int)round(temp.blue * 255) << " ";
		}
		myFile << "\n";
	}
	myFile.close();
};

void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor) {
    x1 = round(x1);
    x2 = round(x2);
    y1 = round(y1);
    y2 = round(y2);
    
    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    float m1 = (y2 - y1) / (x2 - x1);
    float y = y1;
    for (int x = x1; x <= x2; x++)
    {
      if((x >= 0 && x < width) && (y >= 0 && y < height)){
        setColorPixel(x, y, fillColor);
      }
        y += m1;
    }
    
    if (y1 > y2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    float m2 = (x2 - x1) / (y2 - y1);
    float x = x1;
    for (int y = y1; y <= y2; y++)
    {
      if((x >= 0 && x < width) && (y >= 0 && y < height)){
        setColorPixel(x, y, fillColor);
      }
        x += m2;
    }
};

void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color fillColor1, Color fillColor2) {
    x1 = round(x1);
    x2 = round(x2);
    y1 = round(y1);
    y2 = round(y2);
    Vector2 P1(x1, y1);
    Vector2 P2(x2, y2);
    float lineMagnitude = (P1 - P2).magnitude();

    // cout << x1 << " " << x2 << endl;
    if (x1 > x2)
    {
      swap(x1, x2);
      swap(y1, y2);  
      swap(P1, P2);    
      swap(fillColor1, fillColor2);
    }
    float m1 = (y2 - y1) / (x2 - x1);
    float y = y1;
    for (int x = x1; x <= x2; x++)
    {
      if((x >= 0 && x < width) && (y >= 0 && y < height)){
        Vector2 P(x, y);
        float x1P_mag = (P - P1).magnitude();
        float ratio = x1P_mag / lineMagnitude;
        Color colorValue = Color(
          ratio * fillColor2.red + (1.0 - ratio) * fillColor1.red, 
          ratio * fillColor2.green + (1.0 - ratio) * fillColor1.green,
          ratio * fillColor2.blue + (1.0 - ratio) * fillColor1.blue,
          ratio * fillColor2.alpha + (1.0 - ratio) * fillColor1.alpha
        );
        setColorPixel(x, y, colorValue);
      }
      y += m1;
    }

    if (y1 > y2)
    {
      swap(x1, x2);
      swap(y1, y2);
      swap(P1, P2);
      swap(fillColor1, fillColor2);
    }

    float m2 = (x2 - x1) / (y2 - y1);
    float x = x1;
    for (int y = y1; y <= y2; y++)
    {
      if((x >= 0 && x < width) && (y >= 0 && y < height)){
        Vector2 P(x, y);
        float y1P_mag = (P - P1).magnitude();
        float ratio = y1P_mag / lineMagnitude;
        Color colorValue = Color(
          ratio * fillColor2.red + (1.0 - ratio) * fillColor1.red, 
          ratio * fillColor2.green + (1.0 - ratio) * fillColor1.green,
          ratio * fillColor2.blue + (1.0 - ratio) * fillColor1.blue,
          ratio * fillColor2.alpha + (1.0 - ratio) * fillColor1.alpha
        );
        setColorPixel(x, y, colorValue);
      }
      x += m2;
    }
}

void Raster::drawTriangle2D_DotProduct(Triangle2D &triangle)
{
    int lowerX = round(min(triangle.v1.x, min(triangle.v2.x, triangle.v3.x)));
    int upperX = round(max(triangle.v1.x, max(triangle.v2.x, triangle.v3.x)));
    int lowerY = round(min(triangle.v1.y, min(triangle.v2.y, triangle.v3.y)));
    int upperY = round(max(triangle.v1.y, max(triangle.v2.y, triangle.v3.y)));

    for (int x = lowerX; x <= upperX; x++)
    {
      if(x >= 0 && x < width){
        for (int y = lowerY; y <= upperY; y++)
        {
          if(y >= 0 && y < height){
            Vector2 P = Vector2(x, y);
            
            Vector2 edge1 = triangle.v2 - triangle.v1;
            Vector2 edge1_perp = edge1.perpendicular();
            Vector2 g1 = P - triangle.v1;
            float result1 = edge1_perp.dot(g1);

            Vector2 edge2 = triangle.v3 - triangle.v2;
            Vector2 edge2_perp = edge2.perpendicular();
            Vector2 g2 = P - triangle.v2;
            float result2 = edge2_perp.dot(g2);

            Vector2 edge3 = triangle.v1 - triangle.v3;
            Vector2 edge3_perp = edge3.perpendicular();
            Vector2 g3 = P - triangle.v3;
            float result3 = edge3_perp.dot(g3);

            if (result1 < 0 || result2 < 0 || result3 < 0)
                continue;

            setColorPixel(x, y, triangle.c1);
          }
        }         
      }
    }
}

void Raster::drawTriangle3D_Barycentric(Triangle3D &T)
{   
    if(T.shouldDraw){
      Triangle2D myTri(T);
      int lowerX = round(min(T.v1.x, min(T.v2.x, T.v3.x)));
      int upperX = round(max(T.v1.x, max(T.v2.x, T.v3.x)));
      int lowerY = round(min(T.v1.y, min(T.v2.y, T.v3.y)));
      int upperY = round(max(T.v1.y, max(T.v2.y, T.v3.y)));
      
      for (int x = lowerX; x <= upperX; x++)
      {
        if(x >= 0 && x < width){
          for (int y = lowerY; y <= upperY; y++){
            if(y >= 0 && y < height){
              Vector2 P = Vector2(x, y);
              float lambda1, lambda2, lambda3;
              myTri.calculateBarycentricCoordinates(P, lambda1, lambda2, lambda3);
          
              if(lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0){
                float depth = lambda1 * T.v1.z + lambda2 * T.v2.z + lambda3 * T.v3.z;

                if (depth < getDepthPixel(x, y))
                {
                  setDepthPixel(x, y, depth);
                  Color pFillColor = Color(
                    lambda1 * T.c3.red + lambda2 * T.c1.red + lambda3 * T.c2.red,
                    lambda1 * T.c3.green + lambda2 * T.c1.green + lambda3 * T.c2.green,
                    lambda1 * T.c3.blue + lambda2 * T.c1.blue + lambda3 * T.c2.blue,
                    lambda1 * T.c3.alpha + lambda2 * T.c1.alpha + lambda3 * T.c2.alpha
                  );
                  setColorPixel(x, y, pFillColor);
                }
              }
            }
          }
        }
      }
    }
}

void Raster::DrawModel(Model m)
{
    for(int i = 0 ; i < m.numTriangles(); i++){
      Triangle3D temp = m[i];
      drawTriangle3D_Barycentric(temp);
    }
};
