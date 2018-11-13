#include <iostream>
#include "fssimplewindow.h"
#include "CameraObject.h"

using namespace std;

int main(void)
{
	CameraObject camera;
	camera.setCameraCoords(INF, INF, 10.0);

	FsOpenWindow(16, 16, 800, 600, 1);

	bool terminate = false; // Flag for program termination

	while (!terminate)
	{
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		int wid, hei;
		FsGetWindowSize(wid, hei);

		// Check for termination
		if (FsGetKeyState(FSKEY_ESC)):
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

		//// Set up 2D drawing
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		//glDisable(GL_DEPTH_TEST);

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;
}
