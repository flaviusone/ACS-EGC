#pragma once;
#include "Color.h"
#include "Object2D.h"
#include "Object3D.h"
#include "Text.h"

class Visual2D
{
private:	
	float XFm, XFM, YFm, YFM;
	int XPm, XPM, YPm, YPM;
	bool tip_tran, decup;
	float sx,sy,tx,ty;

	//functii
	void calcTran();

public:
	//container obiecte 2D
	vector <Object2D*> visual2D_objects2D;

	//container obiecte3D
	vector <Object3D*> visual2D_objects3D;

	//contatiner text
	vector <Text*> visual2D_texts;

	Visual2D();

	Visual2D(float xf1,float yf1,float xf2,float yf2,int xp1,int yp1,int xp2,int yp2);

	~Visual2D();

	void tipTran(bool tip);

	void decupare(bool dec);

	void fereastra(float x1,float y1,float x2,float y2);

	void poarta(int x1,int y1,int x2,int y2);

	int xDisp(float xf);

	int yDisp(float yf);

	void cadruFereastra(Color color);

	void cadruPoarta(Color color);

	float xLog(int xp);

	float yLog(int yp);

};
