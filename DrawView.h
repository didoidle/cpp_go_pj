#pragma once
#include <GL/glut.h>
#include <GL/GLU.h>
#include <cmath>
#include <iostream>

using namespace std;

class DrawView
{
private:
	float bR = (float)152 / 255;
	float bG = (float)102 / 255;
	float bB = (float)52 / 255;
	float radius = 0.03f;

public:
	
	// ������ ����
	DrawView();

	// �ٵ����� ���� ���� �׸��� 
	void drawLine();

	// �ٵϵ��� ���� �׸��� 
	void drawCircle(int color);

};

