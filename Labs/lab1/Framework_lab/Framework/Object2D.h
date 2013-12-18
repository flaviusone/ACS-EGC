//clasa generala Object2D - toate celelalte clase de obiecte (Line2D,Rectangle2D,Circle2D,Polygon2D) sunt derivate din aceasta clasa

#pragma once
#include "Point2D.h"
#include "Color.h"
#include <vector>

using namespace std;

//obiect generic 2D ajutator - ca sa pun toate obiectele (puncte, linii, dreptunghi, circle, polygon) in contatinerul de obiecte de desenat
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

	~Object2D() {}
};