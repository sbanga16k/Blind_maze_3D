#include "UI.h"
#include "ysglfontdata.h"
#include "fssimplewindow.h"

void DrawMessage1(int x1, int y1)
{
	glColor3ub(0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glRasterPos2i(x1, y1);
	YsGlDrawFontBitmap20x32(" (1)  Restart");
}

void DrawMessage2(int x1, int y1)
{
	glColor3ub(0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glRasterPos2i(x1, y1);
	YsGlDrawFontBitmap20x32(" (2)  Quit");
}

void DrawMessage3(int x1, int y1)
{
	glColor3ub(0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glRasterPos2i(x1, y1);
	YsGlDrawFontBitmap20x32("It Works.");
}

void DrawMessage4(int x1, int y1)
{
	glColor3ub(0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glRasterPos2i(x1, y1);
	YsGlDrawFontBitmap20x32("(Esc) Continue");
}

//void DrawMessageGameOver(int x1, int y1)
//{
//	glColor3ub(255, 0, 0);
//	glShadeModel(GL_SMOOTH);
//	glRasterPos2i(x1, y1);
//	YsGlDrawFontBitmap20x32("Game Over \n Wasted.");
//}



//void AudioPlayer()
//{
//
//}