// Contains declaration of miscallaneous helper functions used across different classes
#include "CameraObject.h"
#include "yssimplesound.h"

#pragma once

namespace Utils {
	const double PI = 3.1415927;				// Defining value of PI
	double absVal(double &num);					// Returns absolute value of number
	// Sets input args to components of rotated vector along each axis
	void getRotComponents(double compA, double compB, double &rotA, double &rotB, double rotAngle = 90);
	// Draws circle at specified location with specified radius
	void drawCircle(double centerX, double centerY, double rad, char color, bool fill, double thickness);
	// Loads the game menu when 'ESC' key pressed
	void loadMenu(bool &terminate, CameraObject &camera, int index, YsSoundPlayer &backgroundPlayer);
}