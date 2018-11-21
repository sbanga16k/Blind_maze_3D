#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "CameraObject.h"
#include "DisplayScreen.h"

using namespace std;

int main(void)
{
	bool debugMode = false;			// Flag for indicating whether to run program in debug or actual mode

	int wid = 800, hei = 600;		// Dimensions of graphics window

	// Specifications for ground grid
	int x, gridSpacing = 5;
	double gridSize = 1000;

	// Initializing & setting up camera object
	CameraObject camera;
	camera.setCameraCoords(INF, 10.0, 10.0);

	// Initializing the screen object for displaying relevant stuff on the graphics window
	Screen theScreen;

	// Initializing a char array for displaying text for debugging
	char *data;

	FsOpenWindow(16, 16, wid, hei, 1);		// Opens up graphics window of specified size
	glClearColor(0.0, 0.0, 0.0, 0.0);		// Set background color for graphics window to black

	// Flag for program termination
	bool terminate = false; 

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
		camera.moveCamera();	// Moves camera acc. to the key press
		
		// Draws the 3D rectangular grid on the ground
		glLineWidth(1);
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

		// Prints relevant text & draws some stuff on the graphics window
		theScreen.display(camera);

		// Prints camera coords & camera angles during debugging mode
		if (debugMode) 
		{
			data = camera.printVals();

			glColor3ub(255, 255, 255);
			glRasterPos2i(650, 25);
			YsGlDrawFontBitmap8x12(data);
		}

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;
}