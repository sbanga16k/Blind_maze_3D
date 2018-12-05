// File that declares CameraObject class with methods for moving camera, printing text to screen

#pragma once

#include<string>
#include<limits>
#include "yssimplesound.h"
#include "maze.h"
#include "Audio.h"

const double PI = 3.14159265359;
const double INF = std::numeric_limits<double>::infinity();

class CameraObject : public mazeData
{
private:
	double camX, camY, camZ;		// Camera's local coordinates
	double heading, pitch, bank;	// Camera's heading, pitch & bank (Euler) angles (in degrees) measured CCW
	double rotInc, translInc;		// Increments for camera rotation & translation resp
	double fov, nearZ, farZ;		// Specifying angle for FoV, nearest & farthest depth for object visibility

public:
	CameraObject();					// Default constructor
	void initialize();				// Initializes camera object

	// Sets camera origin as per global coord system
	void setCameraCoords(double x = 0., double y = 0., double z = 0.);
	void setCameraAngles(double h = 0., double p = 0.);			// Sets camera angles
	void getCameraPos(double &x, double &y, double &z);			// Gets camera position
	void getCameraAngles(double & h, double & p, double & b);	// Gets camera angles
	void setCameraProjection();	// Sets projection mtx for calc. screen coords using camera's coord system
	void setCameraTransform();	// Sets mtx for transformation from global coord to camera's coord system

	// Moves the camera in accordance with the keypress
	void moveCamera(Sounds &audio, bool &terminate, YsSoundPlayer &backgroundPlayer);
	// Sets input args to components of unit vector in current forward direction along each axis
	void getForwardComponents(double &endX, double &endY, double &endZ);
	// Detects collision with wall to prevent going into it
	void detectCollision(double &camZ_temp, double &camX_temp, Sounds &audio, 
		bool &terminate, YsSoundPlayer &backgroundPlayer);
	// Prints values of camera's coord & angles (for debugging)
	char* printVals();
};
