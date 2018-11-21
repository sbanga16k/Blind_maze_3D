// File that declares CameraObject class with methods for moving camera, printing text to screen

#pragma once

#include<string>
#include<limits>

const double PI = 3.14159265359;
const double INF = std::numeric_limits<double>::infinity();

class CameraObject
{
private:
	double camX, camY, camZ;		// Camera's local coordinates
	double heading, pitch, bank;	// Camera's heading, pitch & bank (Euler) angles (in degrees) measured CCW
	double rotInc, translInc;		// Increments for camera translation & rotation resp
	double fov, nearZ, farZ;		// Specifying angle for FoV, nearest & farthest depth for object visibility

public:
	CameraObject();					// Default constructor
	void initialize();				// Initializes camera object

	// Sets camera origin as per global coord system
	void setCameraCoords(double x = 0., double y = 0., double z = 0.);
	void setCameraAngles(double h = 0., double p = 0.);				// Sets camera angles
	void getCameraParams(double &x, double &z, double &h, double &p);	// Gets camera params

	void setCameraProjection();	// Sets projection mtx for calc. screen coords using camera's coord system
	void setCameraTransform();	// Sets mtx for transformation from global coord to camera's coord system

	void moveCamera();	// Moves the camera in accordance with the keypress
	// Sets input args to components of unit vector in current forward direction along each axis
	void getForwardComponents(double &endX, double &endY, double &endZ);
	// Sets input args to components of rotated vector along each axis
	void getRotComponents(double compX, double compZ, double &rotX, double &rotZ, double rotAngle = 90);
	char* printVals();		// Prints values of camera's coord & angles (for debugging)
};
