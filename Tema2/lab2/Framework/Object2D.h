#pragma once
#include "Point2D.h"
#include <vector>

using namespace std;

//obiect generic 2D ajutator - ca sa pun toate obiectele (puncte, linii, dreptunghi, circle, polygon)
//in sistemul de coordonate, pentru a fi desenate
class Object2D
{
public:
	vector <Point2D*> points;
	vector <Point2D*> transf_points;
	int type; //1 = linie; 2 = dreptunghi; 3=cerc; 4=poligon
	Color color;
	bool fill;

public:
	Object2D() {}

	Object2D(vector <Point2D*> _points,int _type,Color _color,bool _fill)
	{
		for (int i = 0; i < _points.size(); i++)
		{
			points.push_back(new Point2D(_points[i]->x,_points[i]->y));
			transf_points.push_back(new Point2D(_points[i]->x,_points[i]->y));
		}
		type = _type;
		color = _color;
		fill = _fill;
	}


	~Object2D() {}
};