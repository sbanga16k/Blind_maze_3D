// Contains definitions of the helper functions used across different 
// classes defined in the heaeder file

#include <iostream>
#include "fssimplewindow.h"
#include "Utils.h"

using namespace std;

// Returns absolute value of number
double Utils::absVal(double & num) {
	return ((num > 0) ? num : -num);
}


// Sets input args to components of vector along each axis rotated by specified angle (in degrees CCW)
void Utils::getRotComponents(double compA, double compB, double &rotA, double &rotB, double rotAngle)
{
	double theta = rotAngle * PI / 180.;
	rotA = compA * cos(theta) - compB * sin(theta);
	rotB = compA * sin(theta) + compB * cos(theta);
}


// Draws circle at specified location with specified radius
void Utils::drawCircle(double centerX, double centerY, double rad, char color, bool fill, double thickness) {

	if (color == 'w')
		glColor3ub(255, 255, 255);	// Sets color of circle as white
	else if (color == 'b')
		glColor3ub(0, 0, 0);		// Sets color of circle as black

	// Draws filled circle or just line loop depending on specification
	if (fill)
		glBegin(GL_POLYGON);
	else {
		glLineWidth((GLfloat)thickness);
		glBegin(GL_LINE_LOOP);
	}

	// Drawing an approximate circle using the below coordinates
	for (int i = 0; i < 120; i++) {
		double angle = (double)i * PI / 15.0;
		double x = centerX + cos(angle)*rad;
		double y = centerY + sin(angle)*rad;
		glVertex2d(x, y);
	}

	glEnd();
}


//// Draws rectangle at specified location with specified dimensions
//void Utils::drawRect(int boxCenterX, int boxCenterY, int boxSizeX, int boxSizeY, char boxColor, bool fill)
//{
//	// Coordinates for bottom left corner of rectangle
//	float botLeftX = boxCenterX - boxSizeX / 2.0f;
//	float botLeftY = boxCenterY - boxSizeY / 2.0f;
//
//	// Draws rectangle of desired color
//	if (boxColor == 'r')
//		glColor3d(1.0, 0.0, 0.0);
//	else if (boxColor == 'v')
//		glColor3d(205 / 255., 215 / 255., 1.);
//	else if (boxColor == 'w')
//		glColor3d(220 / 228., 220 / 228., 220 / 228.);
//	else
//		glColor3d(0.0, 1.0, 0.0);
//
//	// Draws filled rectangle by default. But can draw hollow rectangle if specify bool=0
//	if (fill)
//		glBegin(GL_QUADS);
//	else
//		glBegin(GL_LINE_LOOP);
//
//	// Arrays for storing x & y coordinates for corners of rectangle
//	double recX[4] = { botLeftX, botLeftX + boxSizeX, botLeftX + boxSizeX, botLeftX };
//	double recY[4] = { botLeftY, botLeftY, botLeftY + boxSizeY, botLeftY + boxSizeY };
//
//	// Drawing the rectangle using above defined coordinates
//	for (int i = 0; i < 4; i++)
//	{
//		if (boxColor == 'b')
//			glColor3ub(0, 0, 0);			// Sets color of rectangle to black
//		else
//			glColor3ub(255, 255, 255);		// Sets color of rectangle to white
//
//		glVertex2d(recX[i], recY[i]);
//	}
//
//	glEnd();
//}

// Draws ellipsoid at specified location with specified dimensions
void Utils::drawEllipsoid(double centerX, double centerZ, int numLats, int numLongs,
	float radX, float radY, float radZ, char color)
{
	glDisable(GL_LIGHTING);

	float tStep = (180) / (float)numLats;
	float sStep = (180) / (float)numLongs;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// Draws as wireframe
	for (float t = -90; t <= 90 + .0001; t += tStep)
	{
		// Sets color of ellipsoid
		if (color == 'p')
			glColor3ub(75, 0, 130);		// Indigo
		else
			glColor3ub(138, 43, 226);	// blueviolet

										// Draws the tesseracted ellipsoid at specified position
		glBegin(GL_TRIANGLE_STRIP);
		for (float s = -180; s <= 180 + .0001; s += sStep)
		{
			glVertex3f(radX * cos(t) * cos(s) + (float)centerX,
				radY * cos(t) * sin(s) + 2.5, radZ * sin(t) + (float)centerZ);
			glVertex3f(radX * cos(t + tStep) * cos(s) + (float)centerX,
				radY * cos(t + tStep) * sin(s) + 2.5, radZ * sin(t + tStep) + (float)centerZ);
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);
}