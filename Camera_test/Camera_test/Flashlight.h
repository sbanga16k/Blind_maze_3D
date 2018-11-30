#pragma once
#include<vector>

// Flashlight modelled as a spotlight
class Flashlight {
private:
	std::vector<float> ambientLight, diffuseLight, specularLight;
	std::vector<float> lightPosition, lightDirection;
	float lightConeAngle;														// Cone angle for the spotlight
public:
	Flashlight();
	Flashlight(const double cameraX, const double cameraY, const double cameraZ,
		const double camDirX, const double camDirY, const double camDirZ);
	void updateLightPosition(const double cameraX, const double cameraY, const double cameraZ,
		const double camDirX, const double camDirY, const double camDirZ);		// Updates the light position based on the camera location
};
