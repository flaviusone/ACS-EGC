#pragma once
#include <vector>
#include "Point3D.h"
#include "Point2D.h"


using namespace std;

class Face
{
public:
	vector<int> contour;
	

public:
	Face(vector <int> list)
	{
		for (int i = 0; i < list.size(); i++)
			contour.push_back(list[i]);
		
	}
};

class Object3D
{
public:
	vector<Point3D*> vertices;
	vector<Point3D*> transf_vertices;
	vector<Face*> faces;
	Color color;
	bool fill;

public:
	Object3D(vector <Point3D*> listV,vector <Face*> listF)
	{
		int i;
		for (i = 0; i < listV.size(); i++)
		{
			vertices.push_back(new Point3D(listV[i]->x,listV[i]->y,listV[i]->z));
			transf_vertices.push_back(new Point3D(listV[i]->x,listV[i]->y,listV[i]->z));
		}
		for (i = 0; i < listF.size(); i++)
			faces.push_back(new Face(listF[i]->contour));
		
		color.r = 0;
		color.g = 0;
		color.b = 0;

		fill = false;
	}

	Object3D(vector <Point3D*> listV,vector <Face*> listF, Color _color,bool _fill)
	{
		int i;
		for (i = 0; i < listV.size(); i++)
		{
			vertices.push_back(new Point3D(listV[i]->x,listV[i]->y,listV[i]->z));
			transf_vertices.push_back(new Point3D(listV[i]->x,listV[i]->y,listV[i]->z));
		}
		for (i = 0; i < listF.size(); i++)
			faces.push_back(new Face(listF[i]->contour));
		
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;

		fill = _fill;
	}

	~Object3D()
	{}

};