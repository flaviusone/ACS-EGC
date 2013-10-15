#pragma once
#include "Object3D.h"

class Transform3D
{
public:
	static float ModelMatrix[4][4];
	
	Transform3D();
	
	static void loadIdentityModelMatrix(); //matricea curenta de transformari devine matricea identitate
	static void multiplyModelMatrix(float matrix[4][4]); //inmulteste matricea matrix cu matricea curenta de transformari
	static void translateMatrix(float tx, float ty, float tz); 
	static void scaleMatrix(float sx,float sy,float sz);
	static void rotateMatrixOx(float u);
	static void rotateMatrixOy(float u);
	static void rotateMatrixOz(float u);
	static void applyTransform(Object3D *o);
	static void applyTransform(Point3D *p,Point3D *transf_p);

};