#include <stdio.h> 
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>
#include "maze.h"
#include "fssimplewindow.h"

using namespace std;

mazeData::mazeData()
{
	int mazeLen = 35;
	factor = 3; 
	load((char*) "MapTest.txt", mazeLen);
}

void mazeData::load(char* name, int len)
{
	char c;
	std::ifstream fillData;
	fillData.open(name);
	for (int i = 0; i<len; i++) {
		for (int j = 0; j<len; j++) {
			fillData >> c;
			M[i][j] = c - '0';
		}
	}
	fillData.close();
}

int mazeData::getValMat(int r, int c)
{
	return M[r][c];
}

int mazeData::getFactor()
{
	return factor; 
}

void mazeData::drawCuboid(int x, int y, int z)
{
	double cuboidLen = factor; 
	x = factor * x;
	y = 5 * y;
	z = factor * z; 
	glBegin(GL_QUADS);                 // Y    - Height
										   // X, Z - Length and Breadth 
	glColor3f(0.0, 1.0, 0.0);          // Quad on the top surface
	glVertex3f(x + cuboidLen, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + cuboidLen);
	glVertex3f(x + cuboidLen, y, z + cuboidLen);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(x + cuboidLen, 0, z + cuboidLen);  // Quad on the bottom surface 
	glVertex3f(x, 0, z + cuboidLen);
	glVertex3f(x, 0, z);
	glVertex3f(x + cuboidLen, 0, z);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(x + cuboidLen, y, z + cuboidLen);   // Quad on the front surface
	glVertex3f(x, y, z + cuboidLen);
	glVertex3f(x, 0, z + cuboidLen);
	glVertex3f(x + cuboidLen, 0, z + cuboidLen);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(x + cuboidLen, 0, z);   // Quad on the back surface 
	glVertex3f(x, 0, z);
	glVertex3f(x, y, z);
	glVertex3f(x + cuboidLen, y, z);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(x, y, z + cuboidLen);  // Quad on the left surface 
	glVertex3f(x, y, z);
	glVertex3f(x, 0, z);
	glVertex3f(x, 0, z + cuboidLen);

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(x + cuboidLen, y, z);  // Quad on the right surface 
	glVertex3f(x + cuboidLen, y, z + cuboidLen);
	glVertex3f(x + cuboidLen, 0, z + cuboidLen);
	glVertex3f(x + cuboidLen, 0, z);

	glEnd();
}
