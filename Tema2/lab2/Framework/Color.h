#pragma once

class Color
{
public:
	float r;
	float g;
	float b;
public:
	Color()
	{
		r = g = b = 0;
	}

	Color(float _r,float _g,float _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}

	~Color(){}
};