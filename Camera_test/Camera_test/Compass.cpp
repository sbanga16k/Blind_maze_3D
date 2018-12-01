// File for drawing Compass object with a needle that points to true North using a red triangle
// updating with changing player position

#include <sstream>			// ostringstream
#include <iomanip>			// setprecision
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Utils.h"
#include "Compass.h"

using namespace std;
using namespace Utils;

// Default constructor; initialized the compass params with default values 
Compass::Compass() {

	centerX = 720; centerY = 80;
	radCompass = 60; dialWidth = 3;		// Sets radius & width of compass

	// Setting coords for drawing the needle in default position
	triangleCoords.resize(8);
	rotTriangleCoords.resize(8);

	// Setting x & y coord for the base of triangle
	triangleCoords[2] = 710; triangleCoords[3] = 80;	// Left corner
	triangleCoords[4] = 730; triangleCoords[5] = 80;	// Right corner

	// Sets x & y coords for the North-pointing tip of needle
	triangleCoords[0] = (triangleCoords[2] + triangleCoords[4])/2.;		// x coord
	triangleCoords[1] = triangleCoords[3] - 40;	// y coord

	// Sets x & y coords for the South-pointing tip of needle
	triangleCoords[6] = (triangleCoords[2] + triangleCoords[4]) / 2.;	// x coord
	triangleCoords[7] = triangleCoords[3] + 40;	// y coord

	rotTriangleCoords = triangleCoords;		// Rotated coords is same as original triangle coords initially
}


// Computes compass direction in accordance with the heading angle & adds it to the display text
void Compass::getDirText(string & dispText, CameraObject &camera)
{
	double camX, camY, camZ, heading, pitch, bank;	// Camera params
	camera.getCameraPos(camX, camY, camZ);			// Gets camera pos
	camera.getCameraAngles(heading, pitch, bank);	// Gets camera angles

															// Adds char 'E' or 'W' to start of string if angle b/w NE-SE or NW-SW
	if (absVal(heading) > 56.25 && absVal(heading) < 123.75)
		dispText += (-heading > 0) ? " E" : " W";

	// Adds appropriate chars depending on heading angle
	if (absVal(heading) <= 11.25)
		dispText += " N";
	else if (absVal(heading) > 11.25 && absVal(heading) <= 33.75)
		dispText += " NN";
	else if (absVal(heading) > 33.75 && absVal(heading) <= 56.25)
		dispText += " N";
	else if (absVal(heading) > 56.25 && absVal(heading) < 78.75)
		dispText += "N";
	else if (absVal(heading) > 101.25 && absVal(heading) <= 123.75)
		dispText += "S";
	else if (absVal(heading) > 123.75 && absVal(heading) <= 146.25)
		dispText += " S";
	else if (absVal(heading) > 146.25 && absVal(heading) < 168.75)
		dispText += " SS";
	else if (absVal(heading) >= 168.75)
		dispText += " S";

	// Adds char 'E' or 'W' to end of string except for when it is not in N, E, W, S direction categories
	if ((absVal(heading) > 11.25 && absVal(heading) < 78.75) || 
		(absVal(heading) > 101.25 && absVal(heading) < 168.75))
		dispText += (-heading > 0) ? "E" : "W";

}


// Displays text on the graphics window
void Compass::displayText(CameraObject &camera)
{
	string dispText = "";		// String to store relevant text to display on graphics window

	double camX, camY, camZ, heading, pitch, bank;	// Camera params
	camera.getCameraPos(camX, camY, camZ);			// Gets camera pos
	camera.getCameraAngles(heading, pitch, bank);	// Gets camera angles

	// Limits precision of heading angle to 2
	std::ostringstream oss;
	oss << std::fixed << std::setfill('0') << std::setprecision(2)
		<< (heading > 0)*(-heading + 360) + (heading <= 0)*(-heading);

	// Displays text in terms of compass direction depending on the current heading angle
	dispText = oss.str();
	getDirText(dispText, camera);

	char* result = new char[dispText.size() + 1];
	strcpy_s(result, dispText.size() + 1, dispText.c_str());

	glDisable(GL_LIGHTING);			// Disabling lighting as the compass should be unaffected

	// Displays compass direction
	glColor3ub(255, 0, 0);
	glRasterPos2i(675, 175);
	YsGlDrawFontBitmap12x16(result);

	// Displays letters denoting directions on the compass
	glColor3ub(0, 0, 0);
	glRasterPos2i(717, 40);
	YsGlDrawFontBitmap8x12("N");
	glRasterPos2i(765, 85);
	YsGlDrawFontBitmap8x12("E");
	glRasterPos2i(670, 85);
	YsGlDrawFontBitmap8x12("W");
	glRasterPos2i(718, 132);
	YsGlDrawFontBitmap8x12("S");

	// Displays text about how to quit the game
	glColor3ub(255, 0, 0);
	glRasterPos2i(25, 50);
	YsGlDrawFontBitmap8x12("Press ESC to quit game");

	glEnable(GL_LIGHTING);			// Disabling lighting as the compass should be unaffected
}


// Updates values of triangle coords for rotating the needle in response to the 
// camera rotation
void Compass::moveNeedle(CameraObject &camera)
{	//by rotating original coords

	double headingAngle, PitchAngle, BankAngle;
	camera.getCameraAngles(headingAngle, PitchAngle, BankAngle);

	for (int i = 0; i < 4; i++) {
		// Translating triangle coords to origin before rotation
		triangleCoords[2 * i] -= 720; triangleCoords[2 * i + 1] -= 80;

		// Rotation of triangle coords about origin
		Utils::getRotComponents(triangleCoords[2*i], triangleCoords[2*i + 1], 
			rotTriangleCoords[2*i], rotTriangleCoords[2*i + 1], -headingAngle);

		// Translating both original & rotated triangle coords back to their location on screen
		triangleCoords[2 * i] += 720; triangleCoords[2 * i + 1] += 80;
		rotTriangleCoords[2 * i] += 720; rotTriangleCoords[2 * i + 1] += 80;
	}
}


// Draws the compass needle on the graphics window
void Compass::drawNeedle()
{
	// Draws triangle for North-pointing needle
	glColor3ub(255, 0, 0);			// Sets color of triangle as red (for pointing to true North)

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++) {
		glVertex2d(rotTriangleCoords[2 * i], rotTriangleCoords[2 * i + 1]);
	}
	glEnd();
	
	// Draws triangle for South-pointing needle
	glColor3ub(150, 150, 150);		// Sets color of triangle as gray (for pointing to true South)
	
	glBegin(GL_TRIANGLES);
	for (int i = 1; i < 4; i++) {
		glVertex2d(rotTriangleCoords[2 * i], rotTriangleCoords[2 * i + 1]);
	}
	glEnd();
}


// Draws the compass object on the graphics window
void Compass::drawCompass(CameraObject & camera)
{
	glDisable(GL_LIGHTING);			// Disabling lighting as the compass should be unaffected
	drawCircle(centerX, centerY, radCompass, 'w', 1, dialWidth);
	drawCircle(centerX, centerY, radCompass-5, 'b', 0, dialWidth);
	drawNeedle();
	glEnable(GL_LIGHTING);			// Re-enabling lighting for the rest of the scene
	//drawRect(centerX, centerY, 50, 25, 'b', 1);
}
