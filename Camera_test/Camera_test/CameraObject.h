#pragma once

const double PI = 3.14159265359;
const double INF = std::numeric_limits<double>::max();

class CameraObject
{
private:
	double camX, camY, camZ;		// Camera's local coordinates
	double heading, pitch, bank;	// Camera's heading, pitch & bank (Euler) angles (in degrees) measured CCW
	double fov, nearZ, farZ;		// Specifying angle for FoV, nearest & farthest depth for object visibility

public:
	CameraObject();					// Default constructor
	void initialize();				// Initializes camera object

	// Sets camera origin as per global coord system
	void setCameraCoords(double x = INF, double y = INF, double z = INF);
	void setCameraAngles(double h = INF, double p = INF);				// Sets camera angles
	void getCameraParams(double &x, double &z, double &h, double &p);	// Gets camera params

	void setCameraProjection();	// Sets projection mtx for calc. screen coords using camera's coord system
	void setCameraTransform();	// Sets mtx for transformation from global coord to camera's coord system

	void moveCamera(int rotInc = 1, int translInc = 5);	// Moves the camera in accordance with the keypress
	// Sets input args to components of unit vector in current direction along each axis
	void getComponents(double &endX, double &endY, double &endZ);
	char* printVals(char *result);		// Prints values of camera's x,y,z coords & h,p,b angles (for debugging)
};
