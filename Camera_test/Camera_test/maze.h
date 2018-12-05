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
	//std::chrono::duration<double> elapsed;
	void load(char* name, int len);
	int getValMat(int r, int c);  //Returns value at that index
	void drawCuboid(int x, int, int z, Sounds &audio);
	int getFactor();
	void drawEllipsoid(double centerX, double centerZ, float elevation, int numLats, int numLongs,
		float radX, float radY, float radZ, char color);
	void drawMaze(Sounds &audio);	// Draws maze in graphics window
};