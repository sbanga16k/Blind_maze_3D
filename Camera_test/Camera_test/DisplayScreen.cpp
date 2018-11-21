// File that contains all definitions of methods for displaying textual info,
// and relevant graphics (compass), menu on the graphics window

#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "DisplayScreen.h"

using namespace std;


// Default constructor for initializing the Compass object
Screen::Screen() {
	Compass theCompass;
}


// Displays compass with text on the graphics window
void Screen::display(CameraObject &camera) {
	theCompass.drawCompass(camera);		// Draws the compass object on the graphics window
	theCompass.displayText(camera);		// Displays text on compass & other parts of screen
}