#include <iostream>
#include <vector>
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
#include "Utils.h"	// Temporarily included for drawing portals

using namespace std;

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
	// and 30 slices.
	glScalef(1, 1, 1);
	glColor3ub(75, 0, 255);
	glutWireTorus(0.5, 3, 15, 30);

	std::string message3 = "WELCOME TO OUR BLIND MAZE!";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-3.5, 0.1);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message3.c_str());

	//std::string message2 = " PRESS 'SHIFT' TO TOGGLE SPRINT. ";
	//glColor3f(1.0, 0.2, 0.2); //a great red
	//glRasterPos2f(-7.5, -4.5);
	//glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());

	//std::string message2 = " PRESS 'W,A,S,D' TO MOVE MENU. ";
	//glColor3f(1.0, 0.2, 0.2); //a great red
	//glRasterPos2f(-7.5, -4.5);
	//glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());

	std::string message1 = " PLEASE PRESS 'C' TO CONTINUE. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-5, -1.5);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message1.c_str());

	std::string message2 = " PRESS 'Q' TO QUIT. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-7.5, -4.5);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());
	// F to flashlight
	// Esc to pause game and pull menu
	// Shift to sprint
	// arrow keys to move camera
	// WASD to move player
	// Goal: Rescue the robot.

	glFlush();
	glutSwapBuffers();
}

void displayLose() {

	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
	// and 30 slices.
	glScalef(1, 1, 1);
	glColor3ub(75, 0, 255);
	glutWireTorus(0.5, 3, 15, 30);

	std::string message3 = "YOU LOSE!";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-3.5, 0.4);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message3.c_str());

	std::string message1 = " PRESS 'C' TO TRY AGAIN. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-5, -1.5);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message1.c_str());

	std::string message2 = " PRESS 'Q' IF YOU WOULD LIKE TO QUIT. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-7.5, -4.5);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());

	glFlush();
	glutSwapBuffers();
}

void displayWin() {

	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
	// and 30 slices.
	glScalef(1, 1, 1);
	glColor3ub(75, 0, 255);
	glutWireTorus(0.5, 3, 15, 30);

	std::string message3 = "";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-3.5, 0.4);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message3.c_str());

	std::string message2 = "";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-7.5, -4.5);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());

	glFlush();
	glutSwapBuffers();
}

// Sets up global attributes like clear color and drawing color, and sets up
// the desired projection and modelview matrices.
void init() {

	// Set the current clear color to black and the current drawing color to
	// white.
	//glClearColor(255.0, 255.0, 255.0, 255.0);
	//glColor3f(255.0, 1.0, 1.0);

	// Set the camera lens to have a 60 degree (vertical) field of view, an
	// aspect ratio of 4/3, and have everything closer than 1 unit to the
	// camera and greater than 40 units distant clipped away.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 4.0 / 3.0, 1, 40);

	// Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
	// <0, 1, 0> pointing upward.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
}

void NormalKeyHandler(unsigned char key, int xmouse, int ymouse)
{
	if (key == 27)
	{
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		glutLeaveMainLoop();
		glutDestroyWindow('Menu');
	}
	else if (key == 'Q' || key == 'q')
	{
		glutExit();
	}
	else if (key == 'R' || key == 'r')
	{
		CameraObject camera;
		camera.setCameraCoords(100.0, 5.0, 100.0);
	}
}
void NormalKeyHandler1(unsigned char key, int xmouse, int ymouse)
{
	if (key == 'C' || key == 'c')
	{
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		glutLeaveMainLoop();
	}
	else if (key == 'Q' || key == 'q')
	{
		glutExit();
	}
}

void Menu(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Start");
	glutDisplayFunc(display);
	init();
	glutKeyboardFunc(NormalKeyHandler);
	glutMainLoop();
}


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

	// Initializing the screen object for displaying relevant stuff on the graphics window
	Screen theScreen;

	// Initializing flashlight
	double cameraX, cameraY, cameraZ, camDirX, camDirY, camDirZ;

	camera.getCameraPos(cameraX, cameraY, cameraZ);
	camera.getForwardComponents(camDirX, camDirY, camDirZ);

	Flashlight flashlight(cameraX, cameraY, cameraZ, camDirX, camDirY, camDirZ);

	// Initializing whole maze
	mazeData mazeObj;

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
	glutDisplayFunc(display);
	init();
	glutKeyboardFunc(NormalKeyHandler1);
	glutSwapBuffers();
	glutMainLoop();
	if (FsGetKeyState(FSKEY_ESC))
	{
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		glutLeaveMainLoop();
		glutCloseFunc(display);
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
	bool terminate2, listenForEscape = true;
	int key, key2;

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
			terminate2 = false;
			
			FsPollDevice();
			key2 = FsInkey();
			Utils::loadMenu(terminate, camera, 2, backgroundPlayer);
		}
		listenForEscape = !FsGetKeyState(FSKEY_ESC);

		audio.playerSound();

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
		camera.moveCamera(audio, terminate, backgroundPlayer);	// Moves camera acc. to the key press

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
		theScreen.display(camera);

		// Prints camera coords & camera angles during debugging mode
		if (debugMode) 
		{
			data = camera.printVals();

			glColor3ub(255, 255, 255);
			glRasterPos2i(650, 25);
			YsGlDrawFontBitmap8x12(data);
		}

		// Menu
		//if (FsGetKeyState(FSKEY_T)) // WINNING CONDITION
		//{
		//	glutInit(&argc, argv);
		//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		//	glutInitWindowPosition(80, 80);
		//	glutInitWindowSize(800, 600);
		//	glutCreateWindow("WINNER!!");
		//	glutDisplayFunc(displayWin);
		//	init();
		//	glutKeyboardFunc(NormalKeyHandler);
		//	glutSwapBuffers();
		//	glutMainLoop();
		//}
		//else if (FsGetKeyState(FSKEY_T)) // Game Over CONDITION
		//{
		//	glutInit(&argc, argv);
		//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		//	glutInitWindowPosition(80, 80);
		//	glutInitWindowSize(800, 600);
		//	glutCreateWindow("LOSER!!");
		//	glutDisplayFunc(displayLose);
		//	init();
		//	glutKeyboardFunc(NormalKeyHandler);
		//	glutSwapBuffers();
		//	glutMainLoop();
		//}

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;
}