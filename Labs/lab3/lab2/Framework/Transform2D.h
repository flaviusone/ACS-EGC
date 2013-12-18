#pragma once
#include "Object2D.h"

class Transform2D
{
public:
	static float TransformMatrix[3][3];

	Transform2D();
	
	static void loadIdentityMatrix(); //matricea curenta de transformari devine matricea identitate
	static void multiplyMatrix(float matrix[3][3]); //inmulteste matricea matrix cu matricea curenta de transformari
	static void translateMatrix(float tx, float ty); 
	static void scaleMatrix(float sx,float sy);
	static void rotateMatrix(float u);
	static void rotateMatrix(float cosu,float sinu);
	static void applyTransform(Object2D *o);
	static void applyTransform_o(Object2D *o);
	static void applyTransform(Point2D *p,Point2D *transf_p);

};