#pragma once
#include <iostream>
#include <GL/glut.h>
#include <GL/GLU.h>
#include "DrawGL.h"

using namespace std;

class CheckWinner {

private:
    int directX, directY;
    float ***mat;
    DrawGL dg;
    
public:

    CheckWinner();;
    ~CheckWinner();;

    void direct(int x, int y);

    bool checkOver(int xPos, int yPos, int color, float mat[15][15][3]);


};
