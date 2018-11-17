#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "CameraObject.h"

using namespace std;

int main(void)
{
	cout << "\u0398" << endl;
	bool debugMode = false;			// Flag for indicating whether to run program in debug or actual mode

	int wid = 800, hei = 600;		// Dimensions of graphics window

	// Specifications for ground grid
	int x, gridSpacing = 20;
	double gridSize = 1000;

	char* data;
	CameraObject camera;
	camera.setCameraCoords(INF, 10.0, 10.0);

	FsOpenWindow(16, 16, wid, hei, 1);		// Opens up graphics window of specified size
	glClearColor(0.0, 0.0, 0.0, 0.0);		// Set background color for graphics window to black

	bool terminate = false; // Flag for program termination

	while (!terminate)
	{
		FsPollDevice();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// Check for termination
		if (FsGetKeyState(FSKEY_ESC))
			terminate = true;

		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.setCameraProjection();
		camera.setCameraTransform();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here
		camera.moveCamera();
		
		glBegin(GL_LINES);
		for (x = -gridSize; x <= gridSize; x += gridSpacing)
		{
			glColor3ub(255, 255, x % 256);
			glVertex3i(x, 0, -gridSize);
			glVertex3i(x, 0, gridSize);
			glVertex3i(-gridSize, 0, x);
			glVertex3i(gridSize, 0, x);
		}
		glEnd();

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);

		data = camera.printVals(debugMode);

		glColor3ub(255, 255, 255);
		glRasterPos2i(500, 25);
		YsGlDrawFontBitmap12x16(data);

		glColor3ub(255, 0, 0);
		glRasterPos2i(25, 25);
		YsGlDrawFontBitmap12x16("Press ESC to quit game");

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;
}
