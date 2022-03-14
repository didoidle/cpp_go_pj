#pragma once
#include <iostream>

using namespace std;

class rigidCircle
{
public:
	float x, y, R, G, B, vx, vy ,t;
	float radius;
public:
	float gravity = -0.0098;
	rigidCircle() {}
	rigidCircle(float px, float py, float originX, float originY, float circleRadius, int color, float tt)
	{
		x = px;
		y = py;
		t = tt;
		vx = (x-originX)*0.4;
		vy = (y-originY) * 0.5;
		radius = circleRadius;
		if (color == 1)
		{
			R = 0.0f;
			G = 0.0f;
			B = 0.0f;
		}
		else
		{
			R = 1.0f;
			G = 1.0f;
			B = 1.0f;
		}
	};
	//~rigidCircle() {
	//	cout << "¹ÝÈ¯\n" << endl;
	//	//delete this;
	//}
	void update()
	{
		
		x = x + vx;
		y = y + vy + gravity;
	}
};