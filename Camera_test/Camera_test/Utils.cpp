// Contains definitions of the helper functions used across different 
// classes defined in the heaeder file

#include <iostream>
#include "fssimplewindow.h"
#include "Utils.h"
#include "CameraObject.h"
#include "yssimplesound.h"
#include "yspng.h"

using namespace std;

// Returns absolute value of number
double Utils::absVal(double & num) {
	return ((num > 0) ? num : -num);
}


// Sets input args to components of vector along each axis rotated by specified angle (in degrees CCW)
void Utils::getRotComponents(double compA, double compB, double &rotA, double &rotB, double rotAngle)
{
	double theta = rotAngle * PI / 180.;
	rotA = compA * cos(theta) - compB * sin(theta);
	rotB = compA * sin(theta) + compB * cos(theta);
}


// Draws circle at specified location with specified radius
void Utils::drawCircle(double centerX, double centerY, double rad, char color, bool fill, double thickness) {

	if (color == 'w')
		glColor3ub(255, 255, 255);	// Sets color of circle as white
	else if (color == 'b')
		glColor3ub(0, 0, 0);		// Sets color of circle as black

	// Draws filled circle or just line loop depending on specification
	if (fill)
		glBegin(GL_POLYGON);
	else {
		glLineWidth((GLfloat)thickness);
		glBegin(GL_LINE_LOOP);
	}

	// Drawing an approximate circle using the below coordinates
	for (int i = 0; i < 120; i++) {
		double angle = (double)i * PI / 15.0;
		double x = centerX + cos(angle)*rad;
		double y = centerY + sin(angle)*rad;
		glVertex2d(x, y);
	}

	glEnd();
}


// Loads game menu & provides functionality for resume, restart & quitting the game
void Utils::loadMenu(bool &terminate, CameraObject &camera, int index, YsSoundPlayer &backgroundPlayer)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);
	if (index == 1)
	{
		YsRawPngDecoder png;						// For a PNG that is the same size as your window
		if (YSOK == png.Decode("Start.png"))
		{
			png.Flip();
		}
		else
		{
			printf("Read Error!\n");
		}
		int key;
		bool terminatePic = false;

		while (!terminatePic)
		{
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			int winWid, winHei;
			FsGetWindowSize(winWid, winHei);
			//FsOpenWindow(16, 16, png.wid, png.hei, 1);
			glRasterPos2d(0.0, (double)(winHei - 1));
			glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
			glEnd();
			FsSwapBuffers();
			//glFlush();

			FsPollDevice();
			key = FsInkey();
			if (key == FSKEY_ESC)
			{
				terminatePic = true;
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			}
			else if (FsGetKeyState(FSKEY_R))
			{
				camera.setCameraCoords(96.0, 5.0, 100.0);
				camera.setCameraAngles(0.0, 0.0);
				terminatePic = true;
			}
			else if (FsGetKeyState(FSKEY_Q))
			{
				terminate = true;
				break;
			}
		}
	}

	if (index == 2)
	{
		YsRawPngDecoder png;					// For a PNG that is the same size as your window
		if (YSOK == png.Decode("Menu.png"))
		{
			png.Flip();
		}
		else
		{
			printf("Read Error!\n");
		}
		int key;
		bool terminatePic = false;

		while (!terminatePic)
		{
			FsPollDevice();
			key = FsInkey();
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			int winWid, winHei;
			FsGetWindowSize(winWid, winHei);
			//FsOpenWindow(16, 16, png.wid, png.hei, 1);
			glRasterPos2d(0.0, (double)(winHei - 1));
			glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
			glEnd();
			FsSwapBuffers();
			//glFlush();

			if (FsGetKeyState(FSKEY_ESC))
			{
				terminatePic = true;
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			}
			else if (FsGetKeyState(FSKEY_R))
			{
				camera.setCameraCoords(96.0, 5.0, 100.0);
				camera.setCameraAngles(0.0, 0.0);
				terminatePic = true;
			}
			else if (FsGetKeyState(FSKEY_Q))
			{
				terminate = true;
				break;
			}
		}
	}
	if (index == 3)
	{
		backgroundPlayer.End();
		YsRawPngDecoder png;					// For a PNG that is the same size as your window
		if (YSOK == png.Decode("Win.png"))
		//if (YSOK == png.Decode("Menu.png"))
		{
			png.Flip();
		}
		else
		{
			printf("Read Error!\n");
		}
		int key;
		bool terminatePic = false;

		while (!terminatePic)
		{
			// Set up 2D drawing
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glDisable(GL_DEPTH_TEST);

			FsPollDevice();
			key = FsInkey();
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			int winWid, winHei;
			FsGetWindowSize(winWid, winHei);
			//FsOpenWindow(16, 16, png.wid, png.hei, 1);
			glRasterPos2d(0.0, (double)(winHei - 1));
			glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
			//glEnd();
			FsSwapBuffers();
			// glFlush();

			if (FsGetKeyState(FSKEY_ESC))
			{
				terminatePic = true;
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			}
			else if (FsGetKeyState(FSKEY_R))
			{
				camera.setCameraCoords(96.0, 5.0, 100.0);
				camera.setCameraAngles(0.0, 0.0);
				terminatePic = true;
			}
			else if (FsGetKeyState(FSKEY_Q))
			{
				terminate = true;
				break;
			}
		}
	}
}