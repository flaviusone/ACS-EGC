#pragma once
#include "Color.h"
#include "Point2D.h"
#include "..\dependente\freeglut.h"
#include <string>

using namespace std;

#define BITMAP_8_BY_13 GLUT_BITMAP_8_BY_13
#define BITMAP_9_BY_15 GLUT_BITMAP_9_BY_15
#define BITMAP_TIMES_ROMAN_10 GLUT_BITMAP_TIMES_ROMAN_10
#define BITMAP_TIMES_ROMAN_24 GLUT_BITMAP_TIMES_ROMAN_24
#define BITMAP_HELVETICA_10 GLUT_BITMAP_HELVETICA_10
#define BITMAP_HELVETICA_12 GLUT_BITMAP_HELVETICA_12
#define BITMAP_HELVETICA_18 GLUT_BITMAP_HELVETICA_18


class Text
{
public:
	Point2D pos;
	Color color;
	void* font;
	string text;

	Text(string _text)
	{
		text = _text;
		pos = Point2D(0,0);
		color = Color(0,0,0);
		font = BITMAP_8_BY_13;
	}

	Text(string _text, Point2D _pos, Color _color,  void* _font)
	{
		text = _text;
		pos = _pos;
		color = _color;
		font = _font;
	}

	~Text();
};