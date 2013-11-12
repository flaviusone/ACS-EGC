#include "Visual2D.h"
#include "DrawingWindow.h"
#include "Rectangle2D.h"
#include <iostream>

using namespace std;
void Visual2D::calcTran()
{
	
	if (XFM>XFm && YFM>YFm)
	{
		sx=(float)(XPM-XPm)/(XFM-XFm);
		sy=(float)(YPM-YPm)/(YFM-YFm);
		if (tip_tran) //scalare uniforma
		{
			sx=sy=(sx<sy)?sx:sy;
		}
		tx=(float)XPm-sx*XFm+((float)XPM-(float)XPm-sx*(XFM-XFm))/2;
		ty=(float)YPm-sy*YFm+((float)YPM-(float)YPm-sy*(YFM-YFm))/2;
    }
    else
      sx=sy=tx=ty=0;
	
}



Visual2D::Visual2D()
{
	XPm=YPm=XPM=YPM=0;
	XFm=YFm=XFM=YFM=0;
	tip_tran=false;
	decup=false;
	sx=sy=tx=ty=0;

}

Visual2D::Visual2D(float xf1,float yf1,float xf2,float yf2,int xp1,int yp1,int xp2,int yp2)
{
	XPm=xp1; YPm=yp1; XPM=xp2; YPM=yp2;
	XFm=xf1; XFM=xf2; YFm=yf1; YFM=yf2;
	tip_tran=false;
	decup=false;
	calcTran();

}

Visual2D::~Visual2D()
{
	
}
void Visual2D::tipTran(bool tip)
{
	if (tip!=tip_tran)
	{
		tip_tran=tip;
		calcTran();
	}
}

void Visual2D::decupare(bool dec)
{
	
	//cere decuparea din DrawingWindow
	DrawingWindow::clip(XFm, XFM, YFm, YFM, XPm, XPM, YPm, YPM);
	decup = dec;
}

void Visual2D::fereastra(float x1,float y1,float x2,float y2)
{
	XFm=x1; XFM=x2; YFm=y1; YFM=y2;
	
	calcTran();
	if (decup)
		DrawingWindow::fereastra(XFm, XFM, YFm, YFM);
	
}

void Visual2D::poarta(int x1,int y1,int x2,int y2)
{
	XPm=x1; XPM=x2; YPm=y1; YPM=y2;
	
	calcTran();

	if (tip_tran)
	{
		XPm = XFm * sx + tx;
		YPm = YFm * sy + ty;
		XPM = XFM * sx + tx;
		YPM = YFM * sy + ty;
	}
	if (decup)
		DrawingWindow::poarta(XPm, XPM, YPm, YPM);
}

int Visual2D::xDisp(float xf)
{
	return (int)(xf*sx+tx);
}

int Visual2D::yDisp(float yf)
{
	return (int)(YPM+YPm-(yf*sy+ty));
}

void Visual2D::cadruFereastra(Color color)
{

	Rectangle2D *rectangle = new Rectangle2D(Point2D(XFm,YFm),XFM-XFm,YFM-YFm,color,false);
	DrawingWindow::addObject2D_to_Visual2D(rectangle,this);
	
}

void Visual2D::cadruPoarta(Color color)
{
	Rectangle2D *rectangle = new Rectangle2D(Point2D(xLog(XPm),yLog(YPm)),xLog(XPM)-xLog(XPm),yLog(YPM)-yLog(YPm),color,false);
	DrawingWindow::addObject2D_to_Visual2D(rectangle,this);
}

float Visual2D::xLog(int xp)
{
	return (xp-tx)/sx;
}

float Visual2D::yLog(int yp)
{
	#ifdef GLUT_Y_AXIS_BUG
	// GLUT BUG - pentru a se tine cont de dimensiunea marginilor ferestrei pe Y se scade dimensiunea marginii pe Y
	return (-DrawingWindow::actualBorderOffset+YPM+YPm-yp-ty)/sy;
	#else
	return (YPM+YPm-yp-ty)/sy;
	#endif
}