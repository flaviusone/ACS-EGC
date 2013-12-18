#pragma once
#include "Object3D.h"

class Transform3D
{
public:
	static float ModelMatrix[4][4];
	static float ProjectionMatrix[4][4];
	static float MVPMatrix[4][4];
	static bool proj_type; //false=proiectie paralele, true=proiectie perspectiva
	
	
	Transform3D();
	
	static void loadIdentityModelMatrix(); //matricea curenta de modelare devine matricea identitate
	static void loadIdentityProjectionMatrix(); //matricea curenta de proiectie devine matricea identitate
	static void multiplyModelMatrix(float matrix[4][4]); //inmulteste matricea matrix cu matricea curenta de modelare
	static void multiplyProjectionMatrix(float matrix[4][4]); //inmulteste matricea matrix cu matricea curenta de proiectie
	static void translateMatrix(float tx, float ty, float tz); 
	static void scaleMatrix(float sx,float sy,float sz);
	static void rotateMatrixOx(float u);
	static void rotateMatrixOy(float u);
	static void rotateMatrixOz(float u);
	static void applyTransform(Object3D *o);
	static void applyTransform(Point3D *p,Point3D *transf_p);
	
	static void parallelProjectionMatrix(float a, float b, float c);
	static void perspectiveProjectionMatrix(float xc, float yc, float zc);
	
};