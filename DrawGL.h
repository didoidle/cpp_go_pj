#pragma once
#include <GL/glut.h>
#include <GL/GLU.h>
#include <cmath>

class DrawGL
{
private:
	float transX = -0.47;
	float transY = -0.47;
	float bR = (float)152 / 255;
	float bG = (float)102 / 255;
	float bB = (float)52 / 255;
	float radius = 0.03f;

public:
	DrawGL();
	~DrawGL();

	//  board scale fixed 
	void glDrawScale();

	void glDrawLine();

	void glDrawCircle(int color);

	// find stone color draw and p
	void glDrawStone(float matrix[15][15][3]);

	

};