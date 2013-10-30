#pragma once
#include "Framework\DrawingWindow.h"
#include "Framework\Rectangle2d.h"
#include "Framework\Polygon2D.h"
#include "Framework\Circle2D.h"
#include "Framework\Object2D.h"
#include "Framework\Transform2D.h"

class Laser
{
public:
	float directie;
	float centrux = 0, centruy = 0;
	Polygon2D *body;

public:
	Laser(float dir, float startX, float startY){
		body = new Polygon2D(Color(1, 0, 0), true);

		body->addPoint(Point2D(0, 0));
		body->addPoint(Point2D(25, 0));
		body->addPoint(Point2D(50, 0));
		body->addPoint(Point2D(50, 10));
		body->addPoint(Point2D(25, 10));
		body->addPoint(Point2D(0, 10));

		Transform2D::loadIdentityMatrix();
		Transform2D::rotateMatrix(dir);
		Transform2D::translateMatrix(startX, startY);
		Transform2D::applyTransform(body);


		directie = dir;

		//adaugam la view
		DrawingWindow::addObject2D(body);

	}

	void addLaser2D(){
		DrawingWindow::addObject2D(body);
	}
	void removeLaser2D(){
		DrawingWindow::removeObject2D(body);
	}

	void translate_with(float X, float Y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(X, Y);
		Transform2D::applyTransform_o(body);
	}

	void calc_centru(){
		

		//centrul inamicului este si centrul hitboxului
		centrux = (body->transf_points[0]->x +
			body->transf_points[2]->x +
			body->transf_points[3]->x +
			body->transf_points[5]->x) / 4;

		centruy = (body->transf_points[0]->y +
			body->transf_points[2]->y +
			body->transf_points[3]->y +
			body->transf_points[5]->y) / 4;
	}
	~Laser(){}



};