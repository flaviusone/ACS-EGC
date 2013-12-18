//implementarea clasei Transform2D - trebuie sa fie treaba studentilor

#include "Transform2D.h"
#include <math.h>
#include <iostream>

using namespace std;

//initial matricea de transformare e matricea identitate
	// 1 0 0
	// 0 1 0
	// 0 0 1
	
float Transform2D::TransformMatrix[3][3] = {1,0,0,0,1,0,0,0,1};

Transform2D::Transform2D()
{
	
}


void Transform2D::loadIdentityMatrix()
{
	//matricea de transformare se intoarce la matricea identitate
	// 1 0 0
	// 0 1 0
	// 0 0 1
	TransformMatrix[0][0] = 1;	TransformMatrix[0][1] = 0;	TransformMatrix[0][2] = 0;
	TransformMatrix[1][0] = 0;	TransformMatrix[1][1] = 1;	TransformMatrix[1][2] = 0;
	TransformMatrix[2][0] = 0;	TransformMatrix[2][1] = 0;	TransformMatrix[2][2] = 1;
}


void Transform2D::multiplyMatrix(float matrix[3][3])
{//								m00   m01  m02     tm00  tm01  tm02
 // matrix * TransformMatrix =  m10   m11  m12  *  tm10  tm11  tm12
 //								m20   m21  m22     tm20  tm21  tm22
	int i,j,k;
	float aux_matrix[3][3];
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			aux_matrix[i][j] = 0;
			for (k = 0; k < 3; k++)
			{
				aux_matrix[i][j] = aux_matrix[i][j] + matrix[i][k] * TransformMatrix[k][j];
			}
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			
			TransformMatrix[i][j] = aux_matrix[i][j];
			
		}
		
	}
}


void Transform2D::translateMatrix(float tx, float ty)
{
	float TranslateMatrix[3][3];

	//se construieste matricea de translatie
	//1  0  tx 
	//0  1  ty
	//0  0  1

	TranslateMatrix[0][0] = 1;	TranslateMatrix[0][1] = 0;	TranslateMatrix[0][2] = tx;
	TranslateMatrix[1][0] = 0;	TranslateMatrix[1][1] = 1;	TranslateMatrix[1][2] = ty;
	TranslateMatrix[2][0] = 0;	TranslateMatrix[2][1] = 0;	TranslateMatrix[2][2] = 1;

	//se inmulteste matricea de translatie cu matricea curenta de transformari
	//folosim scrierea vectori coloana
	multiplyMatrix(TranslateMatrix);
}

void Transform2D::scaleMatrix(float sx, float sy)
{
	float ScaleMatrix[3][3];

	//se construieste matricea de scalare
	//sx  0   0 
	//0   sy  0
	//0   0   1

	ScaleMatrix[0][0] = sx;	ScaleMatrix[0][1] = 0;	ScaleMatrix[0][2] = 0;
	ScaleMatrix[1][0] = 0;	ScaleMatrix[1][1] = sy;	ScaleMatrix[1][2] = 0;
	ScaleMatrix[2][0] = 0;	ScaleMatrix[2][1] = 0;	ScaleMatrix[2][2] = 1;

	
	//se inmulteste matricea de scalare cu matricea curenta de transformari
	//folosim scrierea vectori coloana
	multiplyMatrix(ScaleMatrix);
}


void Transform2D::rotateMatrix(float u)
{
	float RotateMatrix[3][3];

	//se construieste matricea de rotatie
	//cos(u)  -sin(u)  0 
	//sin(u)  cos(u)   0
	//0        0       1

	RotateMatrix[0][0] = cos(u);	RotateMatrix[0][1] = - sin(u);	RotateMatrix[0][2] = 0;
	RotateMatrix[1][0] = sin(u);	RotateMatrix[1][1] = cos(u);	RotateMatrix[1][2] = 0;
	RotateMatrix[2][0] = 0;			RotateMatrix[2][1] = 0;			RotateMatrix[2][2] = 1;

	//se inmulteste matricea de rotatie cu matricea curenta de transformari
	//folosim scrierea vectori coloana
	multiplyMatrix(RotateMatrix);
}


void Transform2D::rotateMatrix(float cosu,float sinu)
{
	float RotateMatrix[3][3];

	//se construieste matricea de rotatie
	//cos(u)  -sin(u)  0 
	//sin(u)  cos(u)   0
	//0        0       1

	RotateMatrix[0][0] = cosu;	RotateMatrix[0][1] = - sinu;	RotateMatrix[0][2] = 0;
	RotateMatrix[1][0] = sinu;	RotateMatrix[1][1] = cosu;		RotateMatrix[1][2] = 0;
	RotateMatrix[2][0] = 0;		RotateMatrix[2][1] = 0;			RotateMatrix[2][2] = 1;

	//se inmulteste matricea de rotatie cu matricea curenta de transformari
	//folosim scrierea vectori coloana
	multiplyMatrix(RotateMatrix);
}


void Transform2D::applyTransform(Object2D *o)
{
	//se aplica transformarea pe toate punctele obiectului
	for (int i = 0; i < o->points.size(); i++)
		applyTransform(o->points[i],o->transf_points[i]);
	
}



void Transform2D::applyTransform(Point2D *p,Point2D *transf_p)
{
	//se inmulteste matricea curenta de transformari cu pozitia punctului
	// tm00  tm01  tm02    p.x
	// tm10  tm11  tm12  * p.y
	// tm20  tm21  tm22     1

	float aux_x = p->x;
	transf_p->x = TransformMatrix[0][0] * p->x + TransformMatrix[0][1] * p->y + TransformMatrix[0][2];
	transf_p->y = TransformMatrix[1][0] * aux_x + TransformMatrix[1][1] * p->y + TransformMatrix[1][2];
	
}


void Transform2D::applyTransform_o(Object2D *o)
{
	//se aplica transformarea pe toate punctele obiectului
	for (int i = 0; i < o->points.size(); i++)
		applyTransform(o->transf_points[i],o->transf_points[i]);
	
}