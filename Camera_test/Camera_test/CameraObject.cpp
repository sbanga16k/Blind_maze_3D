// File that contains definition for methods for CameraObject class defined in 
// the header file

#include <iostream>
#include "fssimplewindow.h"
#include "CameraObject.h"

using namespace std;

// Default constructor
CameraObject::CameraObject() {
	initialize();
}

// Initializes camera object
void CameraObject::initialize()
{
	// Initializing camera coord system to coincide with the global coord system
	camX = 0.; camY = 0.; camZ = 0.;
	heading = 0.; pitch = 0.; bank = 0.;
	// Setting increments for camera rotation & translation
	rotInc = 1.0, translInc = 0.2;

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

	// Executes the transformation
	glRotated(-bank, 0.0, 0.0, 1.0);
	glRotated(-pitch, 1.0, 0.0, 0.0);
	glRotated(-heading, 0.0, 1.0, 0.0);
	glTranslated(-camX, -camY, -camZ);
}


// Rotates & Moves the camera in accordance with the keypress
void CameraObject::moveCamera()
{
	// Stores components of unit vector in current North direction along each axis
	double compX, compY, compZ;
	this->getForwardComponents(compX, compY, compZ);

	// Stores components of unit vector in current East direction along each axis
	double compRightX, compRightZ;
	this->getRotComponents(compX, compZ, compRightX, compRightZ);

	//// Rotates camera acc. to arrow key press in 1 degree increments
	// Right-left rotation
	if (FsGetKeyState(FSKEY_RIGHT)) {
		heading -= rotInc;
	}
	else if (FsGetKeyState(FSKEY_LEFT)) {
		heading += rotInc;
	}

	// Camera angle clipped to be in the range of [-180,180] w/o affecting camera motion
	if (heading > 180)
		heading = -180 + (heading - 180);
	else if (heading < -180)
		heading = 180 + (heading + 180);
	
	// Up-down rotation
	// Upward rot capped at 10 deg, downward rot capped at -20 deg
	if (FsGetKeyState(FSKEY_UP)) {
		if (pitch < 10)
			pitch += rotInc;
	}
	else if (FsGetKeyState(FSKEY_DOWN)) {
		if (pitch > -20)
			pitch -= rotInc;
	}

	//// Translates camera acc. to WASD key press

	// Variable with scope limited to function which dictates increment of camera translation
	double newTranslInc;

	// Shift key used for sprinting
	if (FsGetKeyState(FSKEY_SHIFT))
		newTranslInc = translInc * 2;
	else
		newTranslInc = translInc;

	// Moves in North direction
	if (FsGetKeyState(FSKEY_W)) {
		camX += compX * newTranslInc;
		camZ += compZ * newTranslInc;
	}

	// Moves in East direction
	else if (FsGetKeyState(FSKEY_D)) {
		camX += compRightX * newTranslInc;
		camZ += compRightZ * newTranslInc;
	}

	// Moves in West direction
	else if (FsGetKeyState(FSKEY_A)) {
		camX -= compRightX * newTranslInc;
		camZ -= compRightZ * newTranslInc;
	}

	// Moves in South direction
	else if (FsGetKeyState(FSKEY_S)) {
		camX -= compX * newTranslInc;
		camZ -= compZ * newTranslInc;
	}
}


// Sets the input args to components of unit vector in current forward direction along each axis
void CameraObject::getForwardComponents(double &compX, double &compY, double &compZ)
{
	double p = pitch * PI / 180.;
	double h = heading * PI / 180.;
	compX = cos(p)*-sin(h);	// (Projection of end of FoV on XZ plane) x (component along X axis)
	compY = sin(p);					// Projection of end of FoV on Y axis
	compZ = cos(p)*-cos(h);	// (Projection of end of FoV on XZ plane) x (component along Z axis)
}


// Sets input args to components of vector along each axis rotated by specified angle (in degrees CCW)
void CameraObject::getRotComponents(double compX, double compZ, double & rotX, double & rotZ, double rotAngle)
{
	double theta = rotAngle * PI / 180.;
	rotX = compX * cos(theta) - compZ * sin(theta);
	rotZ = compX * sin(theta) + compZ * cos(theta);
}


// Prints values of camera's x,y,z coords & h,p,b angles (for debugging)
char* CameraObject::printVals()
{
	string dispText = "";		// String to display coords & angles on graphics window for debugging

	dispText = " x=" + to_string(camX);
	dispText += " y=" + to_string(camY);
	dispText += " z=" + to_string(camZ);
	dispText += " h=" + to_string(heading);
	dispText += " p=" + to_string(pitch);
	dispText += " b=" + to_string(bank);

	// Need to return char array for displaying font
	char* result = new char[dispText.size() + 1];
	strcpy_s(result, dispText.size() + 1, dispText.c_str());
	return result;
}