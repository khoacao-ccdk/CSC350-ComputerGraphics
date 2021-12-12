#ifndef Raster_H
#define Raster_H
#include "Color.h"
#include "Triangle.h"
#include "Model.h"
#include <fstream>
#include <math.h>
using namespace std;

class Raster
{
	private:
		int width;
		int height;
		Color *pixels;
    float *depthPixels;
 
	public:
		Raster();
		Raster(int pWidth, int pHeight, Color pFillColor);
		~Raster();
		int getHeight();
		int getWidth();
		Color getColorPixel(int x, int y);
		void setColorPixel(int x, int y, Color pFillColor);
    void clear(Color pFillColor);
    float getDepthPixel(int x, int y);
    void setDepthPixel(int x, int y, float depth);
    void clear(float depth);
		void writeToPPM();
		void drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor);
    void drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color fillColor1, Color fillColor2);
    void drawTriangle2D_DotProduct(Triangle2D &triangle);
    void drawTriangle3D_Barycentric(Triangle3D &T);
    void DrawModel(Model m);
};
#endif 


