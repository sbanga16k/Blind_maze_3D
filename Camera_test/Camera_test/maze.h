#pragma once
#include <chrono>
#include "Audio.h"
using namespace std::chrono;

class mazeData
{
	int mazeLen;
	int M[35][35];
	int factor;
	bool lightVisible;
	std::chrono::duration<double> elapsed, store;
	std::chrono::time_point<std::chrono::system_clock> start, end;

public:
	mazeData();
	void initialize();
	//std::chrono::duration<double> elapsed;
	void load(char* name, int len);
	int getValMat(int r, int c);  // Returns value at that index
	// Used for drawing the wall
	void drawCuboid(int x, int, int z, Sounds &audio);

	int getFactor();	// Returns the factor for scaling drawing

	double getElapsedTime();	// Returns elapsed time for flashlight life
	void setElapsedTime();		// Sets value of elapsed time

	bool getLightVisible();		// Returns whether flashlight is on/off
	void setLightInvisible();	// Turns the flashlight off
	void setLightVisible();		// Turns the flashlight on

	void drawEllipsoid(double centerX, double centerZ, float elevation, int numLats, int numLongs,
		float radX, float radY, float radZ, char color);
	void drawMaze(Sounds &audio);	// Draws maze in graphics window
};