#include <iostream>
#include "Color.h"
#include "Raster.h"
#include "Vector.h"
#include "Matrix.h"
#include "Triangle.h"

#define WIDTH 100
#define HEIGHT 100

using namespace std;

int main() {
    /* ===== PART 1 ====== */

    // Color c1 = Color(0.2, 0.4, 0.2, 0.5);
    // Color c2 = Color(0.2, 0.4, 0.9, 0.6);

    // Color c3 = c2 + c1;
    // cout << c3.red << " " << c3.green << " " << c3.blue << " " << c3.alpha << endl;
    
    // Color c4 = c2 * 2.0;
    // cout << c4.red << " " << c4.green << " " << c4.blue << " " << c4.alpha << endl;

    // Color c5 = c1 - c2;
    // cout << c5.red << " " << c5.green << " " << c5.blue << " " << c5.alpha << endl;
    
    // int width = 10, height = 10;

    // Raster r1 = Raster(width, height, White);
    // r1.drawLine_DDA(2, 8.7, 9, 2, Green);
    // r1.setColorPixel(2, 9, Red);
    // r1.setColorPixel(9, 2, Red);
    // r1.writeToPPM();

//    r1.clear(Black);
//    r1.writeToPPM();
    
    /* ===== PART 2 ====== */

    // Vector2 v1 = Vector2(4.5, 2);
    // Vector2 v2 = Vector2(3, 6);

    // Vector2 v3 = v1 + v2;
    // cout << v3.x << " " << v3.y << endl;

    // Vector2 v4 = v2 - v1;
    // cout << v4.x << " " << v4.y << endl;

    // Vector2 v5 = v3 * 5;
    // cout << v5.x << " " << v5.y << endl;

    // cout << v3.magnitude() << endl;

    // cout << v3.dot(v4) << endl;

    // Vector2 v6 = v3.normalize();
    // cout << v6.x << " " << v6.y << endl;

    // Vector2 v7 = v6.perpendicular();
    // cout << v7.x << " " << v7.y << endl;

    // cout << determinant(v7, v6) << endl;

    // int width = 100, height = 100;
    // Raster r1 = Raster(width, height, White);

    // r1.drawLine_DDA_Interpolated(-1, 49, 120, 49, Black, Red);
    // r1.writeToPPM();

    // Triangle2D myTriangle1(Vector2(-2, -15), Vector2(120, 10), Vector2(45, 80), Red, Red, Red);
    // r1.drawTriangle2D_DotProduct(myTriangle1);
    // r1.writeToPPM();
    // Triangle2D myTriangle2(Vector2(45, 80), Vector2(72, 10), Vector2(2, 15),  Red, Green, Blue);
    // r1.drawTriangle_Barycentric(myTriangle2);
    // r1.writeToPPM();
    
    /* ===== PART 3 ====== */

    // Raster myRaster(100, 100, White);
    // Triangle3D t = Triangle3D(Vector4(0, 0, 0, 1), Vector4(40, 0, 0, 1), Vector4(40, 40, 0, 1), Red, Blue, Green);
    // // myRaster.drawtri
    // Matrix4 m = RotateX3D(30.0);
    // //t.Transform(m);
    // myRaster.drawTriangle3D_Barycentric(t);
    // myRaster.writeToPPM();


    /* ===== PART 4 ====== */
    
    // Raster myRaster(WIDTH, HEIGHT, White);
    // Model teapot, bunny;

    // teapot.readFromOBJFile("./teapot.obj", Red);
    // bunny.readFromOBJFile("./bunny.obj", Blue);

    // Matrix4 translateTeapot = Translate3D(50, 50, -60);
    // Matrix4 rotateTeapot = RotateZ3D(45.0);
    // Matrix4 scaleTeapot = Scale3D(0.5, 0.5, 0.5);
    // Matrix4 modelMatrixTeapot = translateTeapot * rotateTeapot * scaleTeapot;

    // Matrix4 translateBunny = Translate3D(70, 30, -60);
    // Matrix4 rotateBunny = RotateZ3D(-20.0);
    // Matrix4 scaleBunny = Scale3D(500, 500, 500);
    // Matrix4 modelMatrixBunny = translateBunny * rotateBunny * scaleBunny;


    // Matrix4 viewMatrix = LookAt(Vector4(50, 50, 30, 1), Vector4(50, 50, -40, 1), Vector4(0, 1, 0, 0));
    // Matrix4 perspectiveMatrix = Perspective(70.0, (float)(myRaster.getWidth() / myRaster.getHeight()), 0.01f, 1000.0f);
    // Matrix4 viewportMatrix = Viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());
    
    // teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);
    // bunny.transform(perspectiveMatrix * viewMatrix * modelMatrixBunny);

    // teapot.homogenize();
    // bunny.homogenize();

    // teapot.transform(viewportMatrix);
    // bunny.transform(viewportMatrix);

    // myRaster.DrawModel(teapot);
    // myRaster.DrawModel(bunny);
    // myRaster.writeToPPM();

    /* ===== PART 5 ====== */
    Raster myRaster(WIDTH, HEIGHT, White);

    Model teapot;
    teapot.readFromOBJFile("./teapot.obj", Red);
    Material modelMaterial(Color(0.0, 0.0, 0.0, 1.0), Color(1.0, 0.0, 0.0, 1.0), Color(1.0, 1.0, 1.0, 1.0), 150.0f);
    teapot.setMaterial(modelMaterial);

    Matrix4 trans = Translate3D(50, 50, -30);
    //Matrix4 rot = RotateZ3D(45.0);
    Matrix4 sca = Scale3D(0.3, 0.3, 0.3);
    Matrix4 modelMatrixTeapot = trans * sca;

    Vector4 eye(50, 50, 30, 1);
    Vector4 spot(50, 50, -30, 1);
    teapot.performBackfaceCulling(eye, spot);

    teapot.transform(modelMatrixTeapot);

    Light myLight(Vector4(60, 25, -20, 1.0), Red, White, Blue);
    teapot.applyLighting(myLight, eye);

    Matrix4 viewMatrix = LookAt(eye, spot, Vector4(0, 1, 0, 0));

    Matrix4 perspectiveMatrix = Perspective(70.0, myRaster.getWidth() / myRaster.getHeight(), 0.01, 88.5);

    Matrix4 viewportMatrix = Viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());

    teapot.transform(perspectiveMatrix * viewMatrix);

    teapot.homogenize();

    teapot.transform(viewportMatrix);
    
    myRaster.DrawModel(teapot);

    myRaster.writeToPPM();

    return 0;    
}
