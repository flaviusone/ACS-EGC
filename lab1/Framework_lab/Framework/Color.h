//Culorile se definesc prin cele 3 componente, r(red), g(green), b(blue), cu valori cuprinse intre 0 si 1 
// 0,0,0 = negru; 1,1,1 = alb; 1,0,0 = rosu; 0,1,0 = verde; 0,0,1 = albastru, etc

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