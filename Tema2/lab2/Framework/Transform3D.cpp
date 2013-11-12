//implementarea clasei Transform3D - trebuie sa fie treaba studentilor

#include "Transform3D.h"
#include <math.h>
#include <iostream>

using namespace std;

float ZC; //folosit pentru impartirea perspectiva

//initial matricea de transformare este egala cu matricea identitate
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1
	
float Transform3D::ModelMatrix[4][4] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
float Transform3D::ProjectionMatrix[4][4] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
float Transform3D::MVPMatrix[4][4] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
bool Transform3D::proj_type(false);


Transform3D::Transform3D()
{
	
}


void Transform3D::loadIdentityModelMatrix()
{
	//matricea de modelare se intoarce la matricea identitate
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1
	ModelMatrix[0][0] = 1;	ModelMatrix[0][1] = 0;	ModelMatrix[0][2] = 0;	ModelMatrix[0][3] = 0;
	ModelMatrix[1][0] = 0;	ModelMatrix[1][1] = 1;	ModelMatrix[1][2] = 0;	ModelMatrix[1][3] = 0;
	ModelMatrix[2][0] = 0;	ModelMatrix[2][1] = 0;	ModelMatrix[2][2] = 1;	ModelMatrix[2][3] = 0;
	ModelMatrix[3][0] = 0;	ModelMatrix[3][1] = 0;	ModelMatrix[3][2] = 0;	ModelMatrix[3][3] = 1;
}


void Transform3D::loadIdentityProjectionMatrix()
{
	//matricea de proiectie se intoarce la matricea identitate
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1
	ProjectionMatrix[0][0] = 1;	ProjectionMatrix[0][1] = 0;	ProjectionMatrix[0][2] = 0;	ProjectionMatrix[0][3] = 0;
	ProjectionMatrix[1][0] = 0;	ProjectionMatrix[1][1] = 1;	ProjectionMatrix[1][2] = 0;	ProjectionMatrix[1][3] = 0;
	ProjectionMatrix[2][0] = 0;	ProjectionMatrix[2][1] = 0;	ProjectionMatrix[2][2] = 1;	ProjectionMatrix[2][3] = 0;
	ProjectionMatrix[3][0] = 0;	ProjectionMatrix[3][1] = 0;	ProjectionMatrix[3][2] = 0;	ProjectionMatrix[3][3] = 1;
}



void Transform3D::multiplyModelMatrix(float matrix[4][4])
{//								m00   m01  m02  m03     tm00  tm01  tm02  tm03
 // matrix * ModelMatrix =      m10   m11  m12  m13  *  tm10  tm11  tm12  tm13
 //								m20   m21  m22  m23     tm20  tm21  tm22  tm23
 //                             m30   m31  m32  m33     tm30  tm31  tm32  tm33

	int i,j,k;
	float aux_matrix[4][4];

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			aux_matrix[i][j] = 0;
			for (k = 0; k < 4; k++)
			{
				aux_matrix[i][j] = aux_matrix[i][j] + matrix[i][k] * ModelMatrix[k][j];
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			
			ModelMatrix[i][j] = aux_matrix[i][j];	
		}
	}
	
}




void Transform3D::multiplyProjectionMatrix(float matrix[4][4])
{//								m00   m01  m02  m03     tm00  tm01  tm02  tm03
 // matrix * ProjectionMatrix = m10   m11  m12  m13  *  tm10  tm11  tm12  tm13
 //								m20   m21  m22  m23     tm20  tm21  tm22  tm23
 //                             m30   m31  m32  m33     tm30  tm31  tm32  tm33

	int i,j,k;
	float aux_matrix[4][4];


	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			aux_matrix[i][j] = 0;
			for (k = 0; k < 4; k++)
			{
				aux_matrix[i][j] += matrix[i][k] * ProjectionMatrix[k][j];
			}
		}
	}
	
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			
			ProjectionMatrix[i][j] = aux_matrix[i][j];
		}
	}
	
}




void Transform3D::translateMatrix(float tx, float ty, float tz)
{
	float TranslateMatrix[4][4];

	//se construieste matricea de translatie
	//1  0  0  tx 
	//0  1  0  ty
	//0  0  1  tz
	//0  0  0  1

	TranslateMatrix[0][0] = 1; TranslateMatrix[0][1] = 0; TranslateMatrix[0][2] = 0; TranslateMatrix[0][3] = tx;
	TranslateMatrix[1][0] = 0; TranslateMatrix[1][1] = 1; TranslateMatrix[1][2] = 0; TranslateMatrix[1][3] = ty;
	TranslateMatrix[2][0] = 0; TranslateMatrix[2][1] = 0; TranslateMatrix[2][2] = 1; TranslateMatrix[2][3] = tz;
	TranslateMatrix[3][0] = 0; TranslateMatrix[3][1] = 0; TranslateMatrix[3][2] = 0; TranslateMatrix[3][3] = 1;
	
	//se inmulteste matricea de translatie cu matricea curenta de modelare
	//folosim scrierea vectori coloana
	multiplyModelMatrix(TranslateMatrix);
}

void Transform3D::scaleMatrix(float sx, float sy, float sz)
{
	float ScaleMatrix[4][4];

	//se construieste matricea de scalare
	//sx  0   0  0
	//0   sy  0  0 
	//0   0   sz 0
	//0   0   0  1

	ScaleMatrix[0][0] = sx; ScaleMatrix[0][1] = 0;  ScaleMatrix[0][2] = 0;  ScaleMatrix[0][3] = 0;
	ScaleMatrix[1][0] = 0;  ScaleMatrix[1][1] = sy; ScaleMatrix[1][2] = 0;  ScaleMatrix[1][3] = 0;
	ScaleMatrix[2][0] = 0;  ScaleMatrix[2][1] = 0;  ScaleMatrix[2][2] = sz; ScaleMatrix[2][3] = 0;
	ScaleMatrix[3][0] = 0;  ScaleMatrix[3][1] = 0;  ScaleMatrix[3][2] = 0;  ScaleMatrix[3][3] = 1;

	//se inmulteste matricea de scalare cu matricea curenta de modelare
	//folosim scrierea vectori coloana
	multiplyModelMatrix(ScaleMatrix);
}


void Transform3D::rotateMatrixOz(float u)
{
	float RotateMatrix[4][4];

	//se construieste matricea de rotatie Oz
	//cos(u)  -sin(u)  0  0
	//sin(u)  cos(u)   0  0
	//0        0       1  0
	//0        0       0  1

	RotateMatrix[0][0] = cos(u);  RotateMatrix[0][1] = - sin(u); RotateMatrix[0][2] = 0;   RotateMatrix[0][3] = 0;
	RotateMatrix[1][0] = sin(u);  RotateMatrix[1][1] = cos(u);   RotateMatrix[1][2] = 0;   RotateMatrix[1][3] = 0;
	RotateMatrix[2][0] = 0;       RotateMatrix[2][1] = 0;		 RotateMatrix[2][2] = 1;   RotateMatrix[2][3] = 0;
	RotateMatrix[3][0] = 0;       RotateMatrix[3][1] = 0;        RotateMatrix[3][2] = 0;   RotateMatrix[3][3] = 1;
	
	//se inmulteste matricea de rotatie cu matricea curenta de modelare
	//folosim scrierea vectori coloana
	multiplyModelMatrix(RotateMatrix);
}

void Transform3D::rotateMatrixOy(float u)
{
	float RotateMatrix[4][4];

	//se construieste matricea de rotatie fata de Oy
	//cos(u)   0      -sin(u)  0
	//0		   1       0       0
	//sin(u)   0       cos(u)  0
	//0        0       0       1

	RotateMatrix[0][0] = cos(u);  RotateMatrix[0][1] = 0;  RotateMatrix[0][2] = - sin(u);  RotateMatrix[0][3] = 0;
	RotateMatrix[1][0] = 0;		  RotateMatrix[1][1] = 1;  RotateMatrix[1][2] = 0;         RotateMatrix[1][3] = 0;
	RotateMatrix[2][0] = sin(u);  RotateMatrix[2][1] = 0;  RotateMatrix[2][2] = cos(u);    RotateMatrix[2][3] = 0;
	RotateMatrix[3][0] = 0;       RotateMatrix[3][1] = 0;  RotateMatrix[3][2] = 0;         RotateMatrix[3][3] = 1;
	
	//se inmulteste matricea de rotatie cu matricea curenta de modelare
	//folosim scrierea vectori coloana
	multiplyModelMatrix(RotateMatrix);
}

void Transform3D::rotateMatrixOx(float u)
{
	float RotateMatrix[4][4];

	//se construieste matricea de rotatie fata de Ox
	//1        0       0        0
	//0       cos(u)   -sin(u)  0
	//0       sin(u)   cos(u)   0
	//0        0       0        1

	RotateMatrix[0][0] = 1;    RotateMatrix[0][1] = 0;       RotateMatrix[0][2] = 0;        RotateMatrix[0][3] = 0;
	RotateMatrix[1][0] = 0;    RotateMatrix[1][1] = cos(u);  RotateMatrix[1][2] = -sin(u);  RotateMatrix[1][3] = 0;
	RotateMatrix[2][0] = 0;    RotateMatrix[2][1] = sin(u);  RotateMatrix[2][2] = cos(u);   RotateMatrix[2][3] = 0;
	RotateMatrix[3][0] = 0;	   RotateMatrix[3][1] = 0;       RotateMatrix[3][2] = 0;        RotateMatrix[3][3] = 1;
	
	//se inmulteste matricea de rotatie cu matricea curenta de modelare
	//folosim scrierea vectori coloana
	multiplyModelMatrix(RotateMatrix);
}


void Transform3D::parallelProjectionMatrix(float a, float b, float c)
{
	float ParallProjectionMatrix[4][4];

	proj_type=false;

	//TODO
	
	//se inmulteste matricea de proiectie ParallProjectionMatrix  cu matricea curenta de proiectie
	//folosim scrierea vectori coloana
	
	//multiplyProjectionMatrix(ParallProjectionMatrix);

}



void Transform3D::perspectiveProjectionMatrix(float xc, float yc, float zc)
{
	float PerspProjectionMatrix[4][4];

	proj_type=true;

	//TODO	
	
	
	//se inmulteste matricea de proiectie PerspProjectionMatrix  cu matricea curenta de proiectie
	//folosim scrierea vectori coloana

	//multiplyProjectionMatrix(PerspProjectionMatrix);
	
	
	//salvam coordonata z a centrului de proie
	ZC = zc;

}



void Transform3D::applyTransform(Point3D *p, Point3D* transf_p)
{

	transf_p->x = MVPMatrix[0][0] * p->x + MVPMatrix[0][1] * p->y + MVPMatrix[0][2] * p->z + MVPMatrix[0][3];
	transf_p->y = MVPMatrix[1][0] * p->x + MVPMatrix[1][1] * p->y + MVPMatrix[1][2] * p->z + MVPMatrix[1][3];
	transf_p->z = MVPMatrix[2][0] * p->x + MVPMatrix[2][1] * p->y + MVPMatrix[2][2] * p->z + MVPMatrix[2][3];
	
	//impartirea perspectiva w = -(z - zc)/zc
	if (proj_type)
	{
		transf_p->x /= -(transf_p->z - ZC) / ZC;
		transf_p->y /= -(transf_p->z - ZC) / ZC;
	}

}

void Transform3D::applyTransform(Object3D* o)
{
	//calculez matricea MVP = ProjectionMatrix * ModelMatrix

	int i,j,k;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			MVPMatrix[i][j] = 0;
			for (k = 0; k < 4; k++)
			{
				MVPMatrix[i][j] += ProjectionMatrix[i][k] * ModelMatrix[k][j];
			}
		}
	}

	for (i = 0; i < o->vertices.size(); i++)
		applyTransform(o->vertices[i],o->transf_vertices[i]);
}



