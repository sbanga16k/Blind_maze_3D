// Contains declaration of miscallaneous helper functions used across different classes
#pragma once

namespace Utils {
	const double PI = 3.1415927;				// Defining value of PI
	double absVal(double &num);					// Returns absolute value of number
	// Sets input args to components of rotated vector along each axis
	void getRotComponents(double compA, double compB, double &rotA, double &rotB, double rotAngle = 90);
	// Draws circle at specified location with specified radius
	void drawCircle(double centerX, double centerY, double rad, char color, bool fill, double thickness);
	// Draws rectangle at specified location with specified dimensions
	void drawRect(int boxCenterX, int boxCenterY, int boxSizeX, int boxSizeY, char boxColor, bool fill);
}