// File that contains definition for methods for CameraObject class defined in 
// the header file

#include <iostream>
#include "fssimplewindow.h"
#include "Utils.h"
#include "CameraObject.h"
#include "maze.h"

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
	rotInc = 5.0, translInc = 0.5;

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


// Gets camera position
void CameraObject::getCameraPos(double & x, double & y, double & z) {
	x = camX; y = camY; z = camZ;
}

// Gets camera position
void CameraObject::getCameraAngles(double & h, double & p, double & b) {
	h = heading; p = pitch; b = bank;
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


// Sets the input args to components of unit vector in current forward direction along each axis
void CameraObject::getForwardComponents(double &compX, double &compY, double &compZ)
{
	double p = pitch * PI / 180.;
	double h = heading * PI / 180.;
	compX = cos(p)*-sin(h);	// (Projection of end of FoV on XZ plane) x (component along X axis)
	compY = sin(p);					// Projection of end of FoV on Y axis
	compZ = cos(p)*-cos(h);	// (Projection of end of FoV on XZ plane) x (component along Z axis)
}


// Rotates & Moves the camera in accordance with the keypress
void CameraObject::moveCamera()
{
	//cout << "X " << camX << " Y " << camY << " Z " << camZ << endl;

	// Stores components of unit vector in current North direction along each axis
	double compX, compY, compZ;
	this->getForwardComponents(compX, compY, compZ);

	// Stores components of unit vector in current East direction along each axis
	double compRightX, compRightZ;
	Utils::getRotComponents(compX, compZ, compRightX, compRightZ);

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
	double camX_temp, camZ_temp;

	// Shift key used for sprinting
	if (FsGetKeyState(FSKEY_SHIFT))
		newTranslInc = translInc * 2;
	else
		newTranslInc = translInc;

	// Moves in North direction
	if (FsGetKeyState(FSKEY_W)) {
		camX_temp = camX + compX * newTranslInc;
		camZ_temp = camZ + compZ * newTranslInc;
		detectCollision(camZ_temp, camX_temp);
	}

	// Moves in South direction
	else if (FsGetKeyState(FSKEY_S)) {
		camX_temp = camX - compX * newTranslInc;
		camZ_temp = camZ - compZ * newTranslInc;
		detectCollision(camZ_temp, camX_temp);
	}

	// Moves in East direction
	if (FsGetKeyState(FSKEY_D)) {
		camX_temp = camX + compRightX * newTranslInc;
		camZ_temp = camZ + compRightZ * newTranslInc;
		detectCollision(camZ_temp, camX_temp);
	}

	// Moves in West direction
	else if (FsGetKeyState(FSKEY_A)) {
		camX_temp = camX - compRightX * newTranslInc;
		camZ_temp = camZ - compRightZ * newTranslInc;
		detectCollision(camZ_temp, camX_temp);
	}
}


// Checks for collision detection to prevent going into the walls
void CameraObject::detectCollision(double &camZ_temp, double &camX_temp)
{
	double scale = getFactor();
	int c = (int)(camZ_temp / scale);
	int d = (int)(camX_temp / scale);

	// Indicates valid position
	if (getValMat(c, d) == 1) {
		camX = camX_temp;
		camZ = camZ_temp;
	}

	// Teleports positions when going through portals
	if (getValMat(c, d) == 2 || getValMat(c, d) == 7) {
		camX = 3; camZ = 3;
		heading = 170;
	}
	if (getValMat(c, d) == 3 || getValMat(c, d) == 5) {
		camX = 72; camZ = 12;
		heading = 0;
	}
	if (getValMat(c, d) == 6) {
		camX = 48; camZ = 39;
		heading = 0;
	}
	if (getValMat(c, d) == 4) {
		camX = 51; camZ = 81;
		heading = 0;
	}
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