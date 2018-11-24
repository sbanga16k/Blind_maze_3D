#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "fssimplewindow.h"
#include "UI.h"
#include "ysglfontdata.h"
#include "Utils.h"
#include "maze.h"
#include "CameraObject.h"
#include "DisplayScreen.h"

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
	// and 30 slices.
	glScalef(1, 1, 1);
	glColor3ub(75, 0, 255);
	glutWireTorus(0.5, 3, 15, 30);

	std::string message3 = "(ESC)  CONTINUE";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-1.5, 1);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message3.c_str());

	std::string message1 = " (R)  RESTART";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-1.5, -1);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message1.c_str());

	std::string message2 = " (Q)  QUIT";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(-1.5, -4);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());

	glFlush();
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
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_USE_CURRENT_CONTEXT);
		glutLeaveMainLoop();
		glutDestroyMenu('Menu');
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
// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(80, 80);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("A Simple Torus");
//	glutDisplayFunc(display);
//	init();
//	glutMainLoop();
//}
void Menu(int argc, char** argv)
{

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(80, 80);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Menu");
		glutDisplayFunc(display);
		std::cout << "Before glutMainLoop()!" << std::endl;
		init();
		glutKeyboardFunc(NormalKeyHandler);
		glutMainLoop();

		std::cout << "Back in main()!" << std::endl;

}
//int main(int argc, char** argv)
//{
//	FsOpenWindow(16, 16, 800, 600, 1);
//
//	bool terminate = false;/*
//	bool terminate2 = false;*/
//
//	while (!terminate)
//	{
//		// Beginning of Script for Game
//		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		//DrawMessage3(300, 200);
//		//FsSwapBuffers();
//		Menu(argc, argv);
//	}
//	return 0;
//}



using namespace std;

int main(int argc, char** argv)
{
	bool debugMode = false;			// Flag for indicating whether to run program in debug or actual mode

	int wid = 800, hei = 600;		// Dimensions of graphics window

	// Specifications for ground grid
	int x, gridSpacing = 5;
	double gridSize = 1000;

	// Maze params
	mazeData mazeObj;
	int mazeLen = 35;

	// Initializing & setting up camera object
	CameraObject camera;
	camera.setCameraCoords(100.0, 5.0, 100.0);

	// Initializing the screen object for displaying relevant stuff on the graphics window
	Screen theScreen;

	// Initializing a char array for displaying text for debugging
	char *data;

	FsOpenWindow(16, 16, wid, hei, 1);		// Opens up graphics window of specified size
	glClearColor(0.0, 0.0, 0.0, 0.0);		// Set background color for graphics window to black

	// Flag for program termination
	bool terminate = false;
	bool terminateWhole = false;
	int key2;
	while (!terminateWhole)
	{
		while (!terminate)
		{
			std::cout << "Start" << std::endl;
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


			if (FsGetKeyState(FSKEY_W))
				terminate = true;
			glViewport(0, 0, wid, hei);

			// Set up 3D drawing
			camera.setCameraProjection();
			camera.setCameraTransform();

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1, 1);

			// 3D drawing from here
			FsPollDevice();
			camera.moveCamera();	// Moves camera acc. to the key press

			// Draws the 3D rectangular grid on the ground
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

			// Maze draw 

			for (int i = 0; i < mazeLen; i++) {
				for (int j = 0; j < mazeLen; j++) {
					if (mazeObj.getValMat(i, j) == 0)
					{
						mazeObj.drawCuboid(j, 1, i);
					}
				}
			}

			// Set up 2D drawing
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glDisable(GL_DEPTH_TEST);

			// Prints relevant text & draws some stuff on the graphics window
			theScreen.displayText(camera);

			// Prints camera coords & camera angles during debugging mode
			if (debugMode)
			{
				data = camera.printVals();

				glColor3ub(255, 255, 255);
				glRasterPos2i(650, 25);
				YsGlDrawFontBitmap8x12(data);
			}
			// Check for termination
			int key;
			FsPollDevice();
			key = FsInkey();
			if (key == FSKEY_ESC)
			{
				Menu(argc, argv);
				break;
				std::cout << "Back in main()!" << std::endl;
			}
			std::cout << "1..2..3!" << std::endl;
			FsSwapBuffers();
			FsSleep(10);
		}

		bool terminate2 = false;
		while (!terminate2)
		{
			std::cout << "Start" << std::endl;
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


			if (FsGetKeyState(FSKEY_W))
				terminate = true;
			glViewport(0, 0, wid, hei);

			// Set up 3D drawing
			camera.setCameraProjection();
			camera.setCameraTransform();

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1, 1);

			// 3D drawing from here
			FsPollDevice();
			camera.moveCamera();	// Moves camera acc. to the key press

			// Draws the 3D rectangular grid on the ground
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

			// Maze draw 

			for (int i = 0; i < mazeLen; i++) {
				for (int j = 0; j < mazeLen; j++) {
					if (mazeObj.getValMat(i, j) == 0)
					{
						mazeObj.drawCuboid(j, 1, i);
					}
				}
			}

			// Set up 2D drawing
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glDisable(GL_DEPTH_TEST);

			// Prints relevant text & draws some stuff on the graphics window
			theScreen.displayText(camera);

			// Prints camera coords & camera angles during debugging mode
			if (debugMode)
			{
				data = camera.printVals();

				glColor3ub(255, 255, 255);
				glRasterPos2i(650, 25);
				YsGlDrawFontBitmap8x12(data);
			}
			// Check for termination
			int key;
			FsPollDevice();
			key = FsInkey();
			if (key == FSKEY_ESC)
			{
				Menu(argc, argv);
				break;
				std::cout << "Back in main()!" << std::endl;
			}
			std::cout << "1..2..3!" << std::endl;
			FsSwapBuffers();
			FsSleep(10);
		}
	}
	return 0;
}

//terminate2 = false;
//while (!terminate2)
//{

//FsPollDevice();
//key2 = FsInkey();
////if (key2 == FSKEY_ESC)
////{
////	// Exit Menu Here.
////	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////	DrawMessage3(300, 200);
////	DrawMessage3(300, 275);*/
////	// FsSwapBuffers();

////	terminate2 = true;
////}
////else if (key2 == FSKEY_1)
////{
////	// Restart Here. Place Initial Conditions here (i.e player location, status, etc).
////}
//if (key2 == FSKEY_2)
//{
//	glutLeaveMainLoop();
//	terminate = true;
//	terminate2 = true;
//}
///*}*/

////#include "fssimplewindow.h"
////#include "UI.h"
////#include <iostream>
////#include "ysglfontdata.h"
////#include "Utils.h"
////#include <math.h>
////using namespace Utils;
////
//////void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
//////{
//////	float theta = 2 * 3.1415926 / float(num_segments);
//////	float c = cosf(theta);//precalculate the sine and cosine
//////	float s = sinf(theta);
//////	float t;
//////
//////	float x = 1;//we start at angle = 0 
//////	float y = 0;
//////
//////	glBegin(GL_LINE_LOOP);
//////	for (int ii = 0; ii < num_segments; ii++)
//////	{
//////		//apply radius and offset
//////		glVertex2f(x * rx + cx, y * ry + cy);//output vertex 
//////
//////		//apply the rotation matrix
//////		t = x;
//////		x = c * x - s * y;
//////		y = s * t + c * y;
//////	}
//////	glEnd();
//////}
////
//////void drawEllipsoid(float a, float b, float c, int lats, int longs)
//////{
//////	int i, j;
//////	double M_PI = 3.141592653;
//////	float lat0, z0, zr0, lat1, z1, zr1;
//////	for (i = 0; i <= lats; i++)
//////	{
//////		lat0 = M_PI * (-0.5f + (float)(i - 1) / lats);
//////		z0 = sin(lat0);
//////		zr0 = cos(lat0);
//////
//////		lat1 = M_PI * (-0.5f + (float)i / lats);
//////		z1 = sin(lat1);
//////		zr1 = cos(lat1);
//////
//////		glBegin(GL_LINE_LOOP);
//////		for (j = 0; j <= longs; j++)
//////		{
//////			float lng = 2 * M_PI * (float)(j - 1) / longs;
//////			float x = cos(lng);
//////			float y = sin(lng);
//////
//////			glNormal3f(x * zr0, y * zr0, z0);
//////			glVertex3f(x * zr0 * a, y * zr0 * b, z0 * c);
//////			glNormal3f(x * zr1, y * zr1, z1);
//////			glVertex3f(x * zr1 * a, y * zr1 * b, z1 * c);
//////		}
//////		glEnd();
//////	}
//////}
////
//////void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC)
//////{
//////	double Pi = 3.14159265359;
//////	float tStep = (Pi) / (float)uiSlices;
//////	float sStep = (Pi) / (float)uiStacks;
//////	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//////	for (float t = -Pi / 2; t <= (Pi / 2) + .0001; t += tStep)
//////	{
//////		glBegin(GL_TRIANGLE_STRIP);
//////		for (float s = -Pi; s <= Pi + .0001; s += sStep)
//////		{
//////			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
//////			glVertex3f(fA * cos(t + tStep) * cos(s), fB * cos(t + tStep) * sin(s), fC * sin(t + tStep));
//////		}
//////		glEnd();
//////	}
//////}
////
////int main()
////{
////
////	FsOpenWindow(16, 16, 800, 600, 1);
////	bool terminate = false;
////	int key;
////	while (!terminate)
////	{
////		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////		 // DrawEllipsoid(100, 100, 800, 300, 100);
////		 // DrawEllipse(300, 300, 100, 200, 100);
////		 // drawEllipsoid(200, 500, 300, 700, 100);
////		// drawCircle(400, 300, 50, 'b', 1, 2);
////		FsSwapBuffers();
////
////		FsPollDevice();
////		key = FsInkey();
////		if (key == FSKEY_ESC)
////		{
////			terminate = true;
////		}
////	}
////}

//#include "fssimplewindow.h"
//#include "UI.h"
//#include "ysglfontdata.h"
//#include "Utils.h"
//#include "yspng.h"
////#include <GL\glew.h>
//#include <GL\freeglut.h>
//#include <iostream>



//int main()
//{
//	FsOpenWindow(16, 16, 800, 600, 1);
//	/*loadPic();*/
//		//bool terminate = false;
//		//while (!terminate)
//		//{
//		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		//	 //drawEllipsoid(1, 1, 1, 100, 150);
//		//	 //DrawEllipse(0, 0, 2, 3, 10);
//		//	 //DrawEllipsoid(1, 1, 1, 1, 1);
//		//	 //drawCircle(400, 300, 50, 'b', 1, 2);
//		//	FsSwapBuffers();
//		//} 
//
//	bool terminate = false;
//	bool terminate2 = false;
//	int key, key2;
//	drawDisp();
//
//	while (!terminate)
//	{
//		// Beginning of Script for Game
//		FsPollDevice();
//		key = FsInkey();
//		if (key == FSKEY_ESC)
//		{
//			terminate2 = false;
//			while (!terminate2)
//			{
//				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//				DrawMessage1(225, 200);
//				DrawMessage2(225, 275);
//				DrawMessage4(225, 125);
//				FsSwapBuffers();
//
//				FsPollDevice();
//				key2 = FsInkey();
//				if (key2 == FSKEY_ESC)
//				{
//					// Exit Menu Here.
//					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//					DrawMessage3(300, 200);
//					DrawMessage3(300, 275);
//					FsSwapBuffers();
//					terminate2 = true;
//				}
//				//else if (key2 == FSKEY_1)
//				//{
//				//	// Restart Here. Place Initial Conditions here (i.e player location, status, etc).
//				//}
//				else if (key2 == FSKEY_2)
//				{
//					terminate = true;
//					terminate2 = true;
//				}
//			}
//		}
//	}
//	return 0;
//}