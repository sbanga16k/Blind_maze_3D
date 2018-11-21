// File that contains all declaration of methods needed for displaying textual info,
// and relevant graphics (compass), menu on the graphics window

#pragma once

#include "CameraObject.h"
#include "Compass.h"

class Screen {

private:
	Compass theCompass;		// The compass object

public:
	Screen();				// Default constructor
	void updateCompass(CameraObject &camera);	// Updates the compass needle direction acc. to camera rotation
	void display(CameraObject &camera);			// Displays compass with relevant text on the graphics window
};