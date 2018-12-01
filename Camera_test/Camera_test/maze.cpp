#include <iostream>
#include <vector>
#include <fstream>
#include "maze.h"
#include "fssimplewindow.h"

mazeData::mazeData()
{
	mazeLen = 35;
	factor = 3;
	load((char *)"MapTest.txt", mazeLen);
	lightVisible = false;
}

void mazeData::load(char* name, int len)
{
	char c;
	std::ifstream fillData;
	fillData.open(name);
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
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

void mazeData::drawCuboid(int x_, int y_, int z_)
{
	// Specifies material color properties
	glEnable(GL_COLOR_MATERIAL);

	std::vector<float> blueDiffuseMatParams{ 0.0f, 0.0f, 1.0f, 1.0f };
	std::vector<float> disableParams{ 0.0f, 0.0f, 0.0f, 1.0f };

	// Define the material type for lighting (only diffuse reflection)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, disableParams.data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueDiffuseMatParams.data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disableParams.data());
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

	int cuboidLen = factor;
	//size_t numDivisions = 25;
	size_t numDivisions = 10;

	float initX = factor * float(x_);
	float initY = 5 * float(y_);
	float initZ = factor * float(z_);

	//float stepX = cuboidLen / (float)numDivisions, stepY = initY / 40.0f, stepZ = stepX;
	float stepX = cuboidLen / (float)numDivisions, stepY = initY / 15.0f, stepZ = stepX;
	
	FsPollDevice();
	int key = FsInkey();

	if (key == FSKEY_F && !lightVisible)
		lightVisible = true;
	else if (key == FSKEY_F && lightVisible)
		lightVisible = false;

	if (lightVisible)
		glColor3f(1.0f, 1.0f, 0.0f);
	else
		glColor3f(0.025f, 0.025f, 0.0f);
	
	// Front face
	float z = initZ + cuboidLen;
	
	for (float x = initX; x < initX + cuboidLen; x += stepX) {
		for (float y = 0.0f; y < initY; y += stepY) {
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(x, y, z);
			glVertex3f(x + stepX, y, z);
			glVertex3f(x + stepX, y + stepY, z);
			glVertex3f(x, y + stepY, z);
			glEnd();
		}
	}

	// Back face
	z = initZ;
	for (float x = initX; x < initX + cuboidLen; x += stepX) {
		for (float y = 0.0f; y < initY; y += stepY) {
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(x, y, z);
			glVertex3f(x + stepX, y, z);
			glVertex3f(x + stepX, y + stepY, z);
			glVertex3f(x, y + stepY, z);
			glEnd();
		}
	}

	// Left face
	float x = initX;
	for (float z = initZ; z < initZ + cuboidLen; z += stepZ) {
		for (float y = 0.0f; y < initY; y += stepY) {
			glBegin(GL_QUADS);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(x, y, z);
			glVertex3f(x, y, z + stepZ);
			glVertex3f(x, y + stepY, z + stepZ);
			glVertex3f(x, y + stepY, z);
			glEnd();
		}
	}

	// Right face
	x = initX + cuboidLen;
	for (float z = initZ; z < initZ + cuboidLen; z += stepZ) {
		for (float y = 0.0f; y < initY; y += stepY) {
			glBegin(GL_QUADS);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(x, y, z);
			glVertex3f(x, y, z + stepZ);
			glVertex3f(x, y + stepY, z + stepZ);
			glVertex3f(x, y + stepY, z);
			glEnd();
		}
	}

	glDisable(GL_COLOR_MATERIAL);
}


// Draws ellipsoid at specified location with specified dimensions
void mazeData::drawEllipsoid(double centerX, double centerZ, int numLats, int numLongs,
	float radX, float radY, float radZ, char color)
{
	glDisable(GL_LIGHTING);
	
	float tStep = (180) / (float)numLats;
	float sStep = (180) / (float)numLongs;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// Draws as wireframe
	for (float t = -90; t <= 90 + .0001; t += tStep)
	{
		if (color == 'p')
			glColor3ub(75, 0, 130);		// Indigo
		else
			glColor3ub(138, 43, 226);	// blueviolet

		// Draws the tesseracted ellipsoid at specified position
		glBegin(GL_TRIANGLE_STRIP);
		for (float s = -180; s <= 180 + .0001; s += sStep)
		{
			glVertex3d(radX * cos(t) * cos(s) + centerX,
				radY * cos(t) * sin(s) + 5, radZ * sin(t) + centerZ);
			glVertex3d(radX * cos(t + tStep) * cos(s) + centerX,
				radY * cos(t + tStep) * sin(s) + 5, radZ * sin(t + tStep) + centerZ);
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);
}


// Draws maze in graphics window
void mazeData::drawMaze() {
	for (int i = 0; i < mazeLen; i++) {

		for (int j = 0; j < mazeLen; j++) {
			if (this->getValMat(i, j) == 0)
				this->drawCuboid(j, 2, i);
			if (this->getValMat(i, j) >= 2 && this->getValMat(i, j) <= 7)
			{
				this->drawEllipsoid(factor*j, factor*i, 6, 6, 6.0f / 3, 18.0f / 3, 6.0f / 3, 'p');
				this->drawEllipsoid(factor*j, factor*i, 10, 10, 5.5f / 3, 17.0f / 3, 5.5f / 3, 'v');
			}
			if (this->getValMat(i, j) == 8)
				this->drawEllipsoid(factor*j, factor*i, 10, 10, 3.75f / 3, 9.0f / 3, 2.75f / 3, 'p');
		}
	}
}


// Draws maze in graphics window
void mazeData::drawMazeNew(int minI, int maxI, int minJ, int maxJ) {
	for (int i = minI; i < maxI; i++) {

		for (int j = minJ; j < maxJ; j++) {
			if (this->getValMat(i, j) == 0)
				this->drawCuboid(j, 2, i);
			if (this->getValMat(i, j) >= 2 && this->getValMat(i, j) <= 7)
			{
				this->drawEllipsoid(factor*j, factor*i, 6, 6, 4.0f / 3, 10.0f / 3, 3.0f / 3, 'p');
				this->drawEllipsoid(factor*j, factor*i, 10, 10, 3.75f / 3, 9.0f / 3, 2.75f / 3, 'v');
			}
			if (this->getValMat(i, j) == 8)
				this->drawEllipsoid(factor*j, factor*i, 10, 10, 3.75f / 3, 9.0f / 3, 2.75f / 3, 'p');
		}
	}
}


// Enabling multi-threading
void mazeData::threadEntry(mazeData * mazePtr, int minI, int maxI, int minJ, int maxJ) {
	mazePtr->drawMazeNew(minI, maxI, minJ, maxJ);
}