#pragma once
#include <iostream>

using namespace std;

class RigidCircle
{
public:
	float x, y, vx, vy, t;
	int clr;
	float radius;
	float gravity = -0.0098;

	RigidCircle() {}

	// 오버로딩?
	RigidCircle(float px, float py, float originX, float originY, float circleRadius, int color, float tt)
	{
		x = px;
		y = py;
		t = tt;
		vx = (x - originX) * 0.4;
		vy = (y - originY) * 0.5;
		radius = circleRadius;
		clr = color;
		
	};

	void update()
	{
		gravity = gravity * 1.23;
		x = x + vx;
		y = y + vy + gravity;
	}
};