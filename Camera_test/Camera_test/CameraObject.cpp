// File that contains definition for methods for CameraObject class defined in 
// the header file

#include <iostream>
#include <sstream>			// ostringstream
#include <iomanip>			// setprecision
#include <stdlib.h>			// abs
#include <math.h>			// round
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
void CameraObject::moveCamera(double rotInc, double translInc)
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

	// Shift key used for sprinting
	if (FsGetKeyState(FSKEY_SHIFT))
		translInc *= 2;

	// Moves in North direction
	if (FsGetKeyState(FSKEY_W)) {
		camX += compX * translInc;
		camZ += compZ * translInc;
	}

	// Moves in East direction
	else if (FsGetKeyState(FSKEY_D)) {
		camX += compRightX * translInc;
		camZ += compRightZ * translInc;
	}

	// Moves in West direction
	else if (FsGetKeyState(FSKEY_A)) {
		camX -= compRightX * translInc;
		camZ -= compRightZ * translInc;
	}

	// Moves in South direction
	else if (FsGetKeyState(FSKEY_S)) {
		camX -= compX * translInc;
		camZ -= compZ * translInc;
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


// Computes compass direction in accordance with the heading angle & adds it to the display text
void CameraObject::getDirText(string &dispText)
{
	// Adds char 'E' or 'W' to start of string if angle b/w NE-SE or NW-SW
	if (abs(heading) > 56.25 && abs(heading) < 123.75)
		dispText += (-heading > 0) ? " E" : " W";

	// Adds appropriate chars depending on heading angle
	if (abs(heading) <= 11.25)
		dispText += " N";
	else if (abs(heading) > 11.25 && abs(heading) <= 33.75)
		dispText += " NN";
	else if (abs(heading) > 33.75 && abs(heading) <= 56.25)
		dispText += " N";
	else if (abs(heading) > 56.25 && abs(heading) < 78.75)
		dispText += "N";
	else if (abs(heading) > 101.25 && abs(heading) <= 123.75)
		dispText += "S";
	else if (abs(heading) > 123.75 && abs(heading) <= 146.25)
		dispText += " S";
	else if (abs(heading) > 146.25 && abs(heading) < 168.75)
		dispText += " SS";
	else if (abs(heading) >= 168.75)
		dispText += " S";

	// Adds char 'E' or 'W' to end of string except for when it is not in N, E, W, S direction categories
	if ((abs(heading) > 11.25 && abs(heading) < 78.75) || (abs(heading) > 101.25 && abs(heading) < 168.75))
		dispText += (-heading > 0) ? "E" : "W";
	
}


// Prints values of camera's x,y,z coords & h,p,b angles (for debugging)
char* CameraObject::printVals(bool debug)
{
	string dispText;				// String to store relevant text to display on graphics window

	if (debug) {
		dispText = " x=" + to_string(camX);
		dispText += " y=" + to_string(camY);
		dispText += " z=" + to_string(camZ);
	}
	
	// Limits precision of heading angle to 2
	std::ostringstream oss;
	oss << std::fixed << std::setfill('0') << std::setprecision(2) << abs(heading);

	// Displays text in terms of compass direction depending on the current heading angle
	dispText = oss.str();
	getDirText(dispText);
	
	if (debug) {
		dispText += " h=" + to_string(heading);
		dispText += " p=" + to_string(pitch);
		dispText += " b=" + to_string(bank);
	}

	char* result = new char[dispText.size() + 1];
	strcpy_s(result, dispText.size() + 1, dispText.c_str());
	return result;
}