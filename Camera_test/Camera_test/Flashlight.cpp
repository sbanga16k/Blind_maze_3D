// Important source - https://www.glprogramming.com/red/chapter05.html#name3
#include <iostream>
#include "fssimplewindow.h"
#include "Utils.h"
#include "Flashlight.h"

using namespace std;
Flashlight::Flashlight() {
	// Set the light positions
	this->lightPosition = std::vector<float>{0.0,0.0,0.0,1.0};
	this->lightDirection = std::vector<float>{1.0,1.0,1.0};
	this->lightConeAngle = 5.0;
	// Set light intensiy and colour
	this->ambientLight = std::vector<float>{0.0f, 0.0f, 0.0f, 1.0f};
	this->diffuseLight = std::vector<float>{1.0f, 1.0f, 1.0f, 1.0f};
	this->specularLight = std::vector<float>{1.0f, 1.0f, 1.0f, 1.0f};
}

// Sets up the flashlight
Flashlight::Flashlight(const double cameraX, const double cameraY, const double cameraZ, 
			const double camDirX, const double camDirY, const double camDirZ) : Flashlight() {
	// Initial light position
	this->lightPosition[0] = (float)cameraX;
	this->lightPosition[1] = (float)cameraY;
	this->lightPosition[2] = (float)cameraZ;

	// Initial light direction
	this->lightDirection[0] = (float)camDirX;
	this->lightDirection[1] = (float)camDirY;
	this->lightDirection[2] = (float)camDirZ;

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	// Initial lighting conditions
	glShadeModel(GL_SMOOTH);

	// Setting up the light intensity
	glLightfv(GL_LIGHT0, GL_AMBIENT, this->ambientLight.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, this->diffuseLight.data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, this->specularLight.data());
	// Setting up the light position
	glLightfv(GL_LIGHT0, GL_POSITION, this->lightPosition.data());			// Position of the light
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, this->lightDirection.data());	// Axis of spotlight cone
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, this->lightConeAngle);				// Cone angle for the spotlight
	// Specifying parameters for light intensity attenuation with increasing distance from flashlight
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0002f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

// Updates the light position in the scene
void Flashlight::updateLightPosition(const double cameraX, const double cameraY, const double cameraZ,
						const double camDirX, const double camDirY, const double camDirZ) {
	// Updated light position
	this->lightPosition[0] = (float)cameraX;
	this->lightPosition[1] = (float)cameraY;
	this->lightPosition[2] = (float)cameraZ;

	// Updated light direction
	this->lightDirection[0] = (float)camDirX;
	this->lightDirection[1] = (float)camDirY;
	this->lightDirection[2] = (float)camDirZ;

//	glDisable(GL_LIGHTING);
//	glDisable(GL_LIGHT0);
//	glDisable(GL_DEPTH_TEST);

	// Initial lighting conditions
	glShadeModel(GL_SMOOTH);

	// Setting up the light intensity
	glLightfv(GL_LIGHT0, GL_AMBIENT, this->ambientLight.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, this->diffuseLight.data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, this->specularLight.data());
	// Setting up the light position
	glLightfv(GL_LIGHT0, GL_POSITION, this->lightPosition.data());			// Position of the light
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, this->lightDirection.data());	// Axis of spotlight cone
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, this->lightConeAngle);				// Cone angle for the spotlight
	// Specifying parameters for light intensity attenuation with increasing distance from flashlight
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0002f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}