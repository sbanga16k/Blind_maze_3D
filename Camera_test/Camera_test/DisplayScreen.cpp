// File that contains all definitions of methods for displaying textual info,
// and relevant graphics (compass), menu on the graphics window

#include <iostream>
#include <sstream>			// ostringstream
#include <iomanip>			// setprecision
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "DisplayScreen.h"
#include "Utils.h"

using namespace std;
using namespace Utils;

// Computes compass direction in accordance with the heading angle & adds it to the display text
void Screen::getDirText(std::string & dispText, CameraObject &camera)
{
	double camX, camZ, heading, pitch;	// Camera params
	camera.getCameraParams(camX, camZ, heading, pitch);		// Gets camera params

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
	if ((absVal(heading) > 11.25 && absVal(heading) < 78.75) || (absVal(heading) > 101.25 && absVal(heading) < 168.75))
		dispText += (-heading > 0) ? "E" : "W";

}


// Displays text on the graphics window
void Screen::displayText(CameraObject &camera)
{
	string dispText = "";		// String to store relevant text to display on graphics window

	double camX, camZ, heading, pitch;	// Camera params
	camera.getCameraParams(camX, camZ, heading, pitch);		// Gets camera params
	
	// Limits precision of heading angle to 2
	std::ostringstream oss;
	oss << std::fixed << std::setfill('0') << std::setprecision(2)
		<< (heading >= 0)*(-heading + 360) + (heading < 0)*(-heading);

	// Displays text in terms of compass direction depending on the current heading angle
	dispText = oss.str();
	getDirText(dispText, camera);

	char* result = new char[dispText.size() + 1];
	strcpy_s(result, dispText.size() + 1, dispText.c_str());

	// Displays compass direction
	glColor3ub(255, 255, 255);
	glRasterPos2i(650, 25);
	YsGlDrawFontBitmap8x12(result);

	// Displays text about how to quit the game
	glColor3ub(255, 0, 0);
	glRasterPos2i(25, 25);
	YsGlDrawFontBitmap8x12("Press ESC to quit game");
}