#pragma once
#include <GL/glut.h>
#include <GL/GLU.h>
#include "DrawGL.h"
#include <cmath>
#include <iostream>


class OperateGL
{
private:
    float windowWidth = 800;
    float windowHeight = 800;
    float mouseD = 0, minDistance = 3.f, minDistanceX = 0, minDistanceY = 0;
    int pX, pY;
    DrawGL dg;
public:

    void initGame(int argc, char** argv, float matrix[15][15][3]);

    void resetGame(float matrix[15][15][3]);
  
};

