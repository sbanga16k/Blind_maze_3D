#include <iostream>
//#include <GL\glew.h>
//#include <GL\freeglut.h>
#include <string>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "CameraObject.h"
#include "maze.h"
#include "DisplayScreen.h"
#include "Flashlight.h"
#include "Audio.h"
#include "Utils.h"	// Temporarily included for drawing portals

using namespace std;

//void display() {
//
//	glClear(GL_COLOR_BUFFER_BIT);
//	glutSwapBuffers();
//	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
//	// and 30 slices.
//	glScalef(1, 1, 1);
//	glColor3ub(75, 0, 255);
//	glutWireTorus(0.5, 3, 15, 30);
//
//	std::string message3 = "(ESC)  CONTINUE";
//	glColor3f(1.0, 0.2, 0.2); //a great red
//	glRasterPos2f(-1.5, 1);
//	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message3.c_str());
//
//	std::string message1 = " (R)  RESTART";
//	glColor3f(1.0, 0.2, 0.2); //a great red
//	glRasterPos2f(-1.5, -1);
//	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message1.c_str());
//
//	std::string message2 = " (Q)  QUIT";
//	glColor3f(1.0, 0.2, 0.2); //a great red
//	glRasterPos2f(-1.5, -4);
//	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());
//
//	glFlush();
//}
//
//// Sets up global attributes like clear color and drawing color, and sets up
//// the desired projection and modelview matrices.
//void init() {
//
//	// Set the current clear color to black and the current drawing color to
//	// white.
//	//glClearColor(255.0, 255.0, 255.0, 255.0);
//	//glColor3f(255.0, 1.0, 1.0);
//
//	// Set the camera lens to have a 60 degree (vertical) field of view, an
//	// aspect ratio of 4/3, and have everything closer than 1 unit to the
//	// camera and greater than 40 units distant clipped away.
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0, 4.0 / 3.0, 1, 40);
//
//	// Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
//	// <0, 1, 0> pointing upward.
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
//}
//
//void NormalKeyHandler(unsigned char key, int xmouse, int ymouse)
//{
//	if (key == 27)
//	{
//		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_USE_CURRENT_CONTEXT);
//		glutLeaveMainLoop();
//		glutDestroyMenu('Menu');
//	}
//	else if (key == 'Q' || key == 'q')
//	{
//		glutExit();
//	}
//	else if (key == 'R' || key == 'r')
//	{
//		CameraObject camera;
//		camera.setCameraCoords(100.0, 5.0, 100.0);
//	}
//}
//
//void Menu(int argc, char** argv)
//{
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(80, 80);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("Menu");
//	glutDisplayFunc(display);
//	std::cout << "Before glutMainLoop()!" << std::endl;
//	init();
//	glutKeyboardFunc(NormalKeyHandler);
//	glutMainLoop();
//
//	std::cout << "Back in main()!" << std::endl;
//
//}


YsSoundPlayer::SoundData wavData;
bool soundOK = false;
YsSoundPlayer soundPlayer;

int main(int argc, char** argv)
{
	bool debugMode = false;			// Flag for indicating whether to run program in debug or actual mode

	int wid = 800, hei = 600;		// Dimensions of graphics window

	// Specifications for ground grid
	int gridSpacing = 5, gridSize = 1000;

	// Maze params
	mazeData mazeObj;

	// Initializing & setting up camera object
	CameraObject camera;
	camera.setCameraCoords(100.0, 5.0, 100.0);

	// Initializing the screen object for displaying relevant stuff on the graphics window
	Screen theScreen;

	// Light setup
	std::vector<float>diffuseMatParams{ 0.1f, 0.5f, 0.8f, 1.0f },
		disableParams{ 0.0f,0.0f,0.0f,1.0f }, gridMatParams{ 1.0f,1.0f,1.0f,1.0f };
	double cameraX, cameraY, cameraZ, camDirX, camDirY, camDirZ;
	camera.getCameraPos(cameraX, cameraY, cameraZ);
	camera.getForwardComponents(camDirX, camDirY, camDirZ);
	Flashlight flashlight(cameraX, cameraY, cameraZ, camDirX, camDirY, camDirZ);

	// Initializing a char array for displaying text for debugging
	char *data;

	// Audio loading for the background sound, flashlight toggle, footsteps
	Sounds audio;
	audio.loadSound("Victory Fanfare.wav", 1);
	audio.loadSound("Flashlight.wav", 2);
	audio.loadSound("FootSteps2.wav", 3);
	//audio.loadSound("Portal.wav", 4);

	// Initializes audio player
	audio.soundPlayer.Start();

	// Play background music
	YsSoundPlayer soundPlayer;
	YsSoundPlayer::SoundData wav;
	if (YSOK != wav.LoadWav("Background Theme.wav"))
	{
		printf("Failed to read \n");
	}

	soundPlayer.Start();
	soundPlayer.PlayBackground(wav, false);

	// Initializing graphics window
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

		audio.movementSound();

		FsPollDevice();
		if (FsGetKeyState(FSKEY_SPACE))
			audio.playSound(2);

		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.setCameraProjection();
		camera.setCameraTransform();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here
		camera.moveCamera();	// Moves camera acc. to the key press

		// Updates light position & angle
		camera.getCameraPos(cameraX, cameraY, cameraZ);
		camera.getForwardComponents(camDirX, camDirY, camDirZ);
		flashlight.updateLightPosition(cameraX, cameraY, cameraZ, camDirX, camDirY, camDirZ);
		
		// Draws the 3D rectangular grid on the ground
		glDisable(GL_LIGHTING);
		glLineWidth(1);
		glBegin(GL_LINES);
		for (int x = -gridSize; x <= gridSize; x += gridSpacing)
		{
			glColor3ub(16, 16, x % 16);
			glVertex3i(x, 0, -gridSize);
			glVertex3i(x, 0, gridSize);
			glVertex3i(-gridSize, 0, x);
			glVertex3i(gridSize, 0, x);
		}
		glEnd();
		glEnable(GL_LIGHTING);

		// Maze draw 
		mazeObj.drawMaze();

		//// Draws portals in maze (Used for DEBUGGING)
		//Utils::drawEllipsoid(0., -50., 6, 6, 4.0f, 10.0f, 3.0f, 'p');
		//Utils::drawEllipsoid(0., -50., 10, 10, 4.0f - 0.25f, 10.0f - 1.0f, 3.0f - 0.25f, 'v');

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);

		// Draws the compass & prints relevant text on the graphics window
		theScreen.updateCompass(camera);
		theScreen.display(camera);

		// Prints camera coords & camera angles during debugging mode
		if (debugMode) 
		{
			data = camera.printVals();

			glColor3ub(255, 255, 255);
			glRasterPos2i(650, 25);
			YsGlDrawFontBitmap8x12(data);
		}

		//// Menu
		//int key;
		//FsPollDevice();
		//key = FsInkey();
		//if (key == FSKEY_ESC)
		//{
		//	Menu(argc, argv);
		//	break;
		//	std::cout << "Back in main()!" << std::endl;
		//}
		//std::cout << "1..2..3!" << std::endl;

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;
}