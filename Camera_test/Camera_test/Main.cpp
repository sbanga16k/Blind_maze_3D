#include <iostream>
//#include <vector>
#include <GL\freeglut.h>
#include <string>
//#include <thread>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "CameraObject.h"
#include "maze.h"
#include "DisplayScreen.h"
#include "Flashlight.h"
#include "Audio.h"
#include "Utils.h"
#include "GlutUtils.h"

using namespace std;

YsSoundPlayer::SoundData wavData;
bool soundOK = false;
YsSoundPlayer soundPlayer;

int main(int argc, char** argv)
{
	bool debugMode = false;			// Flag for indicating whether to run program in debug or actual mode

	int wid = 800, hei = 600;		// Dimensions of graphics window

	// Specifications for ground grid
	int gridSpacing = 5, gridSize = 1000;

	// Initializing & setting up camera object
	CameraObject camera;
	camera.setCameraCoords(96.0, 5.0, 100.0);

	// Initializing flashlight
	double cameraX, cameraY, cameraZ, camDirX, camDirY, camDirZ;

	camera.getCameraPos(cameraX, cameraY, cameraZ);
	camera.getForwardComponents(camDirX, camDirY, camDirZ);

	Flashlight flashlight(cameraX, cameraY, cameraZ, camDirX, camDirY, camDirZ);

	// Initializing whole maze
	mazeData mazeObj;

	// Initializing the screen object for displaying relevant stuff on the graphics window
	Screen theScreen;
	
	//// Initializing vector for portions of the maze for multi-threading
	//const int numThreads = 4;	// Specifies number of threads to use
	//vector<mazeData> mazeQuadrant(numThreads);
	
	//// Initializing thread vector for drawing the maze using multiple threads
	//vector<thread>	threadVec(numThreads);

	// Initializing a char array for displaying text for debugging
	char *data;

	GLint Window1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	Window1 = glutCreateWindow("Start");
	glutDisplayFunc(GlutUtils::display);
	GlutUtils::init();
	glutKeyboardFunc(GlutUtils::NormalKeyHandler1);
	glutSwapBuffers();
	glutMainLoop();
	if (FsGetKeyState(FSKEY_ESC))
	{
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		glutLeaveMainLoop();
		glutCloseFunc(GlutUtils::display);
	}

	// Audio loading for the background sound, flashlight toggle, footsteps
	Sounds audio;
	audio.loadSound("Victory Fanfare.wav", 1);
	audio.loadSound("Flashlight.wav", 2);
	audio.loadSound("FootSteps2.wav", 3);
	audio.loadSound("Portal.wav", 4);

	// Initializes audio player
	audio.soundPlayer.Start();

	// Play background music
	YsSoundPlayer backgroundPlayer;
	YsSoundPlayer::SoundData wav;
	if (YSOK != wav.LoadWav("Background Theme.wav")) {
		cout << "Failed to read" << endl;
	}

	backgroundPlayer.Start();
	backgroundPlayer.PlayBackground(wav, false);

	// Initializing graphics window
	FsOpenWindow(16, 16, wid, hei, 1);		// Opens up graphics window of specified size
	glClearColor(0.0, 0.0, 0.0, 0.0);		// Set background color for graphics window to black

	// Flag for program termination
	bool terminate = false; 
	bool listenForEscape = true;

	while (!terminate)
	{
		FsPollDevice();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		//// Check for termination
		//if (FsGetKeyState(FSKEY_ESC))
		//	terminate = true;

		if (listenForEscape && FsGetKeyState(FSKEY_ESC))
		{
			listenForEscape = false;
			
			mazeObj.setLightInvisible();
			Utils::loadMenu(terminate, camera, mazeObj, 2, backgroundPlayer);	
		}
		listenForEscape = !FsGetKeyState(FSKEY_ESC);

		audio.playerSound();
		
		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.setCameraProjection();
		camera.setCameraTransform();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here
		camera.moveCamera(audio, mazeObj, terminate, backgroundPlayer);	// Moves camera acc. to the key press

		// Updates light position & angle
		camera.getCameraPos(cameraX, cameraY, cameraZ);
		camera.getForwardComponents(camDirX, camDirY, camDirZ);
		flashlight.updateLightPosition(cameraX, cameraY, cameraZ, camDirX, camDirY, camDirZ);
		
		// Maze draw 
		mazeObj.drawMaze(audio);

		// Draws portals in maze (Used for DEBUGGING)
		if (debugMode) {
			mazeObj.drawEllipsoid(100., 75., 10.0f, 6, 6, 4.0f/3, 12.0f/3, 3.0f/3, 'p');
			mazeObj.drawEllipsoid(100., 75., 10.0f, 10, 10, 4.0f/3 - 0.25f/3, 12.0f/3 - 1.0f/3, 3.0f/3 - 0.25f/3, 'v');
		}

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);

		// Draws the compass & prints relevant text on the graphics window
		theScreen.updateCompass(camera);
		theScreen.display(camera, mazeObj);

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
