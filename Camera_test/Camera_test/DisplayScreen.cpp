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


// Calls the compass object's move needle function to update its direction
// with the camera rotation
void Screen::updateCompass(CameraObject &camera) {
	if (FsGetKeyState(FSKEY_UP) || FsGetKeyState(FSKEY_RIGHT) || 
		FsGetKeyState(FSKEY_LEFT) || FsGetKeyState(FSKEY_DOWN))
	theCompass.moveNeedle(camera);
}


// Displays compass with text on the graphics window
void Screen::display(CameraObject &camera, mazeData &mazeObj) {
	theCompass.drawCompass(camera);		// Draws the compass object on the graphics window
	theCompass.displayText(camera, mazeObj);		// Displays text on compass & other parts of screen
}