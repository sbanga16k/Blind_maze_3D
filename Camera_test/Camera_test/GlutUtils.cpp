#include <GL\freeglut.h>
#include <string>
#include "CameraObject.h"
#include "GlutUtils.h"


// Sets up global attributes like clear color and drawing color, and sets up
// the desired projection and modelview matrices.
void GlutUtils::init() {

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


// Screen display function
void GlutUtils::display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
	// and 30 slices for the background of the start screen
	glScalef(1, 1, 1);
	glColor3ub(75, 0, 255);
	glutWireTorus(0.5, 3, 15, 30);

	std::string message1 = " WELCOME TO BLIND MAZE! ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -175, 250, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message1.c_str());

	std::string message2 = "GOAL: SEARCH AND RESCUE. FIND THE ROBOT! ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -275, 180, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());

	std::string message3 = " Instructions: ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -75, 125, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message3.c_str());

	std::string message4 = " Press 'F' to toggle the flashlight. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -180, 70, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message4.c_str());

	std::string message5 = " Battery life: 120 seconds. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -130, 20, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message5.c_str());

	std::string message6 = " Press 'W,A,S,D' to move player. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -180, -30, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message6.c_str());

	std::string message7 = " Use ARROW keys to rotate camera. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -200, -80, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message7.c_str());

	std::string message8 = " Press 'SHIFT' to sprint. ";
	glColor3f(1.0, 0.2, -1); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -120, -130, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message8.c_str());

	std::string message9 = " Press 'C' to Continue. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -110, -180, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message9.c_str());

	std::string message10 = " Press 'Q' to Quit. ";
	glColor3f(1.0, 0.2, 0.2); //a great red
	glRasterPos2f(0, 0);
	glBitmap(0, 0, 0, 0, -85, -230, NULL);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message10.c_str());

	glFlush();
	glutSwapBuffers();
}


// Function for displaying the start window
void GlutUtils::Menu(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Start");
	glutDisplayFunc(GlutUtils::display);
	GlutUtils::init();
	glutKeyboardFunc(GlutUtils::NormalKeyHandler);
	glutMainLoop();
}


// Key handler function for start window
void GlutUtils::NormalKeyHandler1(unsigned char key, int xmouse, int ymouse)
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


// Key handler function for game (Pause) menu
void GlutUtils::NormalKeyHandler(unsigned char key, int xmouse, int ymouse)
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


//// Display winning screen if user manages to rescue the robot (Unused)
//void GlutUtils::displayWin() 
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glutSwapBuffers();
//	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
//	// and 30 slices.
//	glScalef(1, 1, 1);
//	glColor3ub(75, 0, 255);
//	glutWireTorus(0.5, 3, 15, 30);
//
//	std::string message3 = "";
//	glColor3f(1.0, 0.2, 0.2); //a great red
//	glRasterPos2f(-3.5, 0.4);
//	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message3.c_str());
//
//	std::string message2 = "";
//	glColor3f(1.0, 0.2, 0.2); //a great red
//	glRasterPos2f(-7.5, -4.5);
//	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());
//
//	glFlush();
//	glutSwapBuffers();
//}


//// Display lose screen (Unused)
//void GlutUtils::displayLose() 
// {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glutSwapBuffers();
//	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
//	// and 30 slices.
//	glScalef(1, 1, 1);
//	glColor3ub(75, 0, 255);
//	glutWireTorus(0.5, 3, 15, 30);
//
//	std::string message3 = "YOU LOSE!";
//	glColor3f(1.0, 0.2, 0.2); //a great red
//	glRasterPos2f(-3.5, 0.4);
//	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message3.c_str());
//
//	std::string message1 = " PRESS 'C' TO TRY AGAIN. ";
//	glColor3f(1.0, 0.2, 0.2); //a great red
//	glRasterPos2f(-5, -1.5);
//	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message1.c_str());
//
//	std::string message2 = " PRESS 'Q' TO QUIT. ";
//	glColor3f(1.0, 0.2, 0.2); //a great red
//	glRasterPos2f(-7.5, -4.5);
//	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)message2.c_str());
//
//	glFlush();
//	glutSwapBuffers();
//}
