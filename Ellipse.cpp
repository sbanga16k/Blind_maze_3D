void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC)
{
	double Pi = 3.14159265359;
	float tStep = (Pi) / (float)uiSlices;
	float sStep = (Pi) / (float)uiStacks;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (float t = -Pi / 2; t <= (Pi / 2) + .0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float s = -Pi; s <= Pi + .0001; s += sStep)
		{
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
			glVertex3f(fA * cos(t + tStep) * cos(s), fB * cos(t + tStep) * sin(s), fC * sin(t + tStep));
		}
		glEnd();
	}
}

void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = 1;//we start at angle = 0 
	float y = 0;

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		//apply radius and offset
		glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}
void drawEllipsoid(float a, float b, float c, int lats, int longs)
{
	int i, j;
	double M_PI = 3.141592653;
	for (i = 0; i <= lats; i++)
	{
		float lat0 = M_PI * (-0.5f + (float)(i - 1) / lats);
		float z0 = sin(lat0);
		float zr0 = cos(lat0);

		float lat1 = M_PI * (-0.5f + (float)i / lats);
		float z1 = sin(lat1);
		float zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++)
		{
			float lng = 2 * M_PI * (float)(j - 1) / longs;
			float x = cos(lng);
			float y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0 * a, y * zr0 * b, z0 * c);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1 * a, y * zr1 * b, z1 * c);
		}
		glEnd();
	}
}
//// This is a simple introductory program; its main window contains a static
//// picture of a torus.  The program illustrates viewing by choosing a camera
//// setup with gluLookAt(), which is conceptually simpler than transforming
//// objects to move into a predefined view volume.
// Clears the window and draws the torus.
//void display() {
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	// Draw a white torus of outer radius 3, inner radius 0.5 with 15 stacks
//	// and 30 slices.
//	glColor3f(1.0, 1.0, 1.0);
//	glutWireTorus(0.5, 3, 15, 30);
//
//	// Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
//	// axes are ten units long.
//	glBegin(GL_LINES);
//	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
//	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
//	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
//	glEnd();
//
//	glFlush();
//}
//
//// Sets up global attributes like clear color and drawing color, and sets up
//// the desired projection and modelview matrices.
//void init() {
//
//	// Set the current clear color to black and the current drawing color to
//	// white.
//	glClearColor(0.0, 0.0, 0.0, 1.0);
//	glColor3f(1.0, 1.0, 1.0);
//
//	// Set the camera lens to have a 60 degree (vertical) field of view, an
//	// aspect ratio of 4/3, and have everything closer than 1 unit to the
//	// camera and greater than 40 units distant clipped away.
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0, 4.0 / 3.0, 1, 40);
//
//	// Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
//	// <0, 1, 0> pointing upward.
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
//}
//
//// Initializes GLUT, the display mode, and main window; registers callbacks;
//// does application initialization; enters the main event loop.
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(80, 80);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("A Simple Torus");
//	glutDisplayFunc(display);
//	init();
//	glutMainLoop();
//}