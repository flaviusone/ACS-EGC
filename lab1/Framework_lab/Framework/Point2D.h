//Clasa Point2D - defineste un punct, prin coordonatele x si y

#pragma once


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