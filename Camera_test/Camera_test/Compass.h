// File containing declarations for Compass object with method for drawing a needle 
// that points to true North, updating with changing player position

#pragma once

#include <iostream>
#include <vector>
#include "CameraObject.h"

using namespace std;

class Compass
{
private:
	double centerX, centerY;			// x, y coords of center of compass
	double radCompass, dialWidth;		// Radius of the compass dial, thickness of the dial
	// Original coords of the needle of compass with coords stored in the format [x, y, ...]
	vector <double> triangleCoords;
	// Coords of the needle of compass used for drawing; needed separately since these coords
	// are obtained by rotating original coords by current heading angle everytime
	vector <double> rotTriangleCoords;
	
public:
	Compass();		// Default constructor
	// Gets compass direction based on heading angle
	void getDirText(string & dispText, CameraObject &camera);
	void displayText(CameraObject &camera);		// Displays relevant text on the graphics window
	void moveNeedle(CameraObject & camera);		// Rotates needle in response to camera rotation
	void drawNeedle();							// Draws the compass needle on the graphics window
	void drawCompass(CameraObject &camera);		// Draws the compass on the graphics window
};