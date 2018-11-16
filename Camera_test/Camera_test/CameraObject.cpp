#include <iostream>
#include <string>
#include "fssimplewindow.h"
#include "CameraObject.h"

using namespace std;

// Default constructor
CameraObject::CameraObject() {
	Initialize();
}

// Initializes camera object
void CameraObject::initialize()
{
	// Initializing camera coord system to coincide with the global coord system
	camX = 0.; camY = 0.; camZ = 0.;
	heading = 0.; pitch = 0.; bank = 0.;

	fov = 30.0;			// FoV: 30 degrees
	nearZ = 0.1; farZ = 200.0;
}


// Sets camera origin in global coords for values which are not infinity (INF)
void CameraObject::setCameraCoords(double x, double y, double z) {
	if (x != INF)
		camX = x;
	if (y != INF)
		camY = y;
	if (y != INF)
		camZ = z;
}

// Sets camera angles for values which are not infinity (INF)
void CameraObject::setCameraAngles(double h, double p) {
	if (h != INF)
		heading = h;
	if (p != INF)
		pitch = p;
}

// Gets camera params
void CameraObject::getCameraParams(double & x, double & z, double & h, double & p) {
	x = camX; z = camZ;
	h = heading; p = pitch; 
}


// Sets projection mtx for calc. screen coords using camera's coord system
void CameraObject::setCameraProjection()
{
	int w, h;			// Dimensions of the graphics window
	double aspect;		// Aspect ratio of the graphics window

	FsGetWindowSize(w, h);
	aspect = double(w) / double(h);

	glMatrixMode(GL_PROJECTION);	// Indicates that program will set the projection matrix
	glLoadIdentity();				// Resets the projection matrix 
	gluPerspective(fov, aspect, nearZ, farZ);	// Sets the projection matrix in accordance w/ specified params
}


// Sets the matrix for transformation from global coord to camera's coord system
void CameraObject::setCameraTransform()
{
	glMatrixMode(GL_MODELVIEW);		// Indicates that program will set the transformation matrix
	glLoadIdentity();				// Resets the projection matrix

	glRotated(-b, 0.0, 0.0, 1.0);
	glRotated(-p, 1.0, 0.0, 0.0);
	glRotated(-h, 0.0, 1.0, 0.0);
	glTranslated(-x, -y, -z);
}


// Moves the camera in accordance with the keypress
void CameraObject::moveCamera(int rotInc, int translInc)
{
	double compX, compY, compZ;		// Stores components of unit vector in current direction along each axis
	this->getEndComponents(compX, compY, compZ);

	// Rotates camera acc. to arrow key press in 1 degree increments
	if (FsGetKeyState(FSKEY_RIGHT)) {
		heading += rotInc;
	}
	else if (FsGetKeyState(FSKEY_LEFT)) {
		heading -= rotInc;
	}
	else if (FsGetKeyState(FSKEY_UP)) {
		pitch += rotInc;
	}
	else if (FsGetKeyState(FSKEY_DOWN)) {
		pitch -= rotInc;
	}

	// Translates camera acc. to WASD key press
	else if (FsGetKeyState(FSKEY_W)) {
		camX += compX * translInc;
		camY += compY * translInc;
		camZ += compZ * translInc;
	}
	else if (FsGetKeyState(FSKEY_A)) {
		camX -= compX * translInc;
	}
	else if (FsGetKeyState(FSKEY_S)) {
		camX -= compX * translInc;
		camY -= compY * translInc;
		camZ -= compZ * translInc;
	}
	else if (FsGetKeyState(FSKEY_D)) {
		camX += compX * translInc;
	}
	else if (FsGetKeyState(FSKEY_A)) {
		camX +=  * 0.5;
	}
	else if (FsGetKeyState(FSKEY_D)) {
		camX -=  * 0.5;
	}
}


// Sets the input args to components of unit vector in current direction along each axis
void CameraObject::getComponents(double &compX, double &compY, double &compZ)
{
	compX = cos(pitch)*-sin(heading);		// (Projection of end of FoV on XZ plane) x (its component along X axis)
	compY = sin(pitch);					// Projection of end of FoV on Y axis
	compZ = cos(pitch)*-cos(heading);		// (Projection of end of FoV on XZ plane) x (its component along Z axis)
}


// Prints values of camera's x,y,z coords & h,p,b angles (for debugging)
char* CameraObject::printVals()
{
	string temp;

	temp = " x=" + to_string(x);
	temp += " y=" + to_string(y);
	temp += " z=" + to_string(z);
	temp += " h=" + to_string(h);
	temp += " p=" + to_string(p);
	temp += " b=" + to_string(b);

	char* result = new char[temp.size() + 1];
	strcpy_s(result, temp.size() + 1, temp.c_str());
	return result;
}