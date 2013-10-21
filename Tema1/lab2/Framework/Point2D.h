#pragma once
#include "Color.h"


class Point2D
{
public:
	float x,y;

public:
	Point2D()
	{
		x = 0;
		y = 0;
	}

	Point2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	~Point2D()
	{}

};