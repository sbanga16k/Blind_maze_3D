#include <iostream>
#include <vector>
#include <fstream>
#include "maze.h"
#include "fssimplewindow.h"

using namespace std;

// Default contructor
mazeData::mazeData() {
	initialize();
}


// Initializes parameters associated with the maze object 
void mazeData::initialize()
{
	mazeLen = 35;
	factor = 3;
	load((char *)"MapTest.txt", mazeLen);
	lightVisible = false;
	std::chrono::time_point<std::chrono::system_clock> a, b;
	b = std::chrono::system_clock::now();
	a = std::chrono::system_clock::now();
	elapsed = a - b;
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

// Returns value at that index
int mazeData::getValMat(int r, int c) {
	return M[r][c];
}

// Returns the factor for scaling drawing
int mazeData::getFactor() {
	return factor;
}

// Returns elapsed time for flashlight life
double mazeData::getElapsedTime() {
	return elapsed.count();
}

// Sets value of elapsed time
void mazeData::setElapsedTime() 
{
	std::chrono::time_point<std::chrono::system_clock> d, e;
	d = std::chrono::system_clock::now();
	e = std::chrono::system_clock::now();
	elapsed = d - e;
}

// Returns whether flashlight is on/off
bool mazeData::getLightVisible() {
	return lightVisible;
}

// Turns the flashlight off
void mazeData::setLightInvisible() {
	lightVisible = false;
}

// Turns the flashlight on
void mazeData::setLightVisible() {
	lightVisible = true;
}

void mazeData::drawCuboid(int x_, int y_, int z_, Sounds &audio)
{
	// Specifies material color properties
	glEnable(GL_COLOR_MATERIAL);

	std::vector<float> diffuseMatParams{ 0.0f, 0.0f, 0.0f, 1.0f };
	std::vector<float> disableParams{ 0.0f, 0.0f, 0.0f, 1.0f };

	// Define the material type for lighting (only diffuse reflection)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, disableParams.data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMatParams.data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, disableParams.data());
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

	int cuboidLen = factor;
	//size_t numDivisions = 25;
	int numDivisions = 10;		// Specifies number of unit squares used for drawing each wall

	// Initial positions of space coords
	float initX = factor * float(x_);
	float initY = 5 * float(y_);
	float initZ = factor * float(z_);

	//float stepX = cuboidLen / (float)numDivisions, stepY = initY / 40.0f, stepZ = stepX;
	float stepX = cuboidLen / (float)numDivisions, stepY = initY / 15.0f, stepZ = stepX;

	FsPollDevice();
	int key = FsInkey();

	// Check for flashlight on/off & play flashlight toggle sound
	if (key == FSKEY_F && !lightVisible)
	{
		lightVisible = true;
		audio.playSound(2);
		store = elapsed;
		start = std::chrono::system_clock::now();
	}
	else if (key == FSKEY_F && lightVisible)
	{
		lightVisible = false;
		audio.playSound(2);
	}

	// Accumulates elapsed time when flashlight is on
	if (lightVisible == true)
	{
		end = std::chrono::system_clock::now();
		elapsed = store + end - start;
		//cout << elapsed.count() << endl;
	}

	// Condition for flashlight battery running out
	if (elapsed.count()>120)
		lightVisible = false;


	// Specifies color of walls to be visible depending on whether flashlight is on/off
	if (lightVisible)
		glColor3f(1.0f, 1.0f, 0.0f);
	else
		glColor3f(0.025f, 0.025f, 0.0f);

	//// Actual drawing of the cuboid
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
void mazeData::drawEllipsoid(double centerX, double centerZ, float elevation, int numLats, int numLongs,
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
		else if (color == 'v')
			glColor3ub(138, 43, 226);	// blueviolet
		else if (color == 'g')
			glColor3ub(255, 200, 25);	// gold
		else if (color == 'y')
			glColor3ub(229, 181, 25);	// dull gold
		else if (color == 'w')
			glColor3ub(255, 255, 255);	// white
		else
			glColor3ub(0, 0, 0);	// black
		

		// Draws the tesseracted ellipsoid at specified position
		glBegin(GL_TRIANGLE_STRIP);
		for (float s = -180; s <= 180 + .0001; s += sStep)
		{
			glVertex3d(radX * cos(t) * cos(s) + centerX,
				radY * cos(t) * sin(s) + elevation, radZ * sin(t) + centerZ);
			glVertex3d(radX * cos(t + tStep) * cos(s) + centerX,
				radY * cos(t + tStep) * sin(s) + elevation, radZ * sin(t + tStep) + centerZ);
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);
}


// Draws maze in graphics window
void mazeData::drawMaze(Sounds &audio) {
	for (int i = 0; i < mazeLen; i++) {

		for (int j = 0; j < mazeLen; j++) {
			if (this->getValMat(i, j) == 0)
				this->drawCuboid(j, 2, i, audio);
			if (this->getValMat(i, j) >= 2 && this->getValMat(i, j) <= 7)
			{
				this->drawEllipsoid(factor*j, factor*i, 5.1f, 6, 6, 6.0f / 3, 18.0f / 3, 6.0f / 3, 'p');
				this->drawEllipsoid(factor*j, factor*i, 5.1f, 10, 10, 5.5f / 3, 17.0f / 3, 5.5f / 3, 'v');
			}
			// Drawing BB-8 robot (Changed design to not look like a snowman xD - Saurabh)
			if (this->getValMat(i, j) == 8)
			{
				this->drawEllipsoid(factor*j, factor*i, 1.5f, 20, 20, 1.5f, 1.5f, 1.5f, 'g');
				this->drawEllipsoid(factor*j, factor*i, 1.5f, 10, 10, 0.75f, 0.75f, 2.0f, 'b');
				this->drawEllipsoid(factor*j, factor*i, 1.5f, 10, 10, 1.0f, 1.0f, 1.8f, 'w');
				this->drawEllipsoid(factor*j, factor*i, 3.25f, 20, 20, 1.0f, 1.0f, 1.0f, 'y');
				this->drawEllipsoid(factor*j, factor*i, 3.5f, 10, 10, 0.35f, 0.35f, 1.2f, 'w');
			}
		}
	}
}


// Draws maze in graphics window
//void mazeData::drawMazeNew(int minI, int maxI, int minJ, int maxJ) {
//	for (int i = minI; i < maxI; i++) {
//
//		for (int j = minJ; j < maxJ; j++) {
//			if (this->getValMat(i, j) == 0)
//				this->drawCuboid(j, 2, i);
//			if (this->getValMat(i, j) >= 2 && this->getValMat(i, j) <= 7)
//			{
//				this->drawEllipsoid(factor*j, factor*i, 6, 6, 4.0f / 3, 10.0f / 3, 3.0f / 3, 'p', 5);
//				this->drawEllipsoid(factor*j, factor*i, 10, 10, 3.75f / 3, 9.0f / 3, 2.75f / 3, 'v', 5);
//			}
//			if (this->getValMat(i, j) == 8)
//			{
//				this->drawEllipsoid(factor*j, factor*i, 10, 10, 2.2, 2.2, 2.2, 'p', 2);
//				this->drawEllipsoid(factor*j, factor*i, 10, 10, 1, 1, 1, 'p',5);
//			}
//		}
//	}
//}


// Enabling multi-threading
//void mazeData::threadEntry(mazeData * mazePtr, int minI, int maxI, int minJ, int maxJ) {
//	mazePtr->drawMazeNew(minI, maxI, minJ, maxJ);
//}