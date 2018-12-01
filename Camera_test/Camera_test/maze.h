#pragma once

class mazeData
{
	int mazeLen;
	int M[35][35];
	int factor; 
	bool lightVisible;

public:
	mazeData(); 
	void load(char* name, int len);
	int getValMat(int r, int c);  //Returns value at that index
	void drawCuboid(int x, int , int z);
	int getFactor(); 
	void drawEllipsoid(double centerX, double centerZ, int numLats, int numLongs,
		float radX, float radY, float radZ, char color);
	void drawMaze();	// Draws maze in graphics window
	void drawMazeNew(int minI, int maxI, int minJ, int maxJ);	// Draws maze in graphics window
	// Enabling multi-threading
	static void threadEntry(mazeData *mazePtr, int minI, int maxI, int minJ, int maxJ);				
};

