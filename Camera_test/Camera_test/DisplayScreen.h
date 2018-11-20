// File that contains all declaration of methods needed for displaying textual info,
// and relevant graphics (compass), menu on the graphics window

#pragma once

#include "CameraObject.h"

class Screen {
public:
	Screen() {};					// Default constructor
	// Gets compass direction based on heading angle
	void getDirText(std::string & dispText, CameraObject &camera);
	void displayText(CameraObject &camera);				// Displays relevant text on the graphics window
};