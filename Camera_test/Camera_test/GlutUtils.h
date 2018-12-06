#pragma once
namespace GlutUtils {
	void init();			// Sets up global attributes needed for GlutWindow functioning
	void display();			// Screen display function
	void Menu(int argc, char ** argv);	// Function for displaying the start window
	// Key handler function for start window
	void NormalKeyHandler1(unsigned char key, int xmouse, int ymouse);
	// Key handler function for game (Pause) menu
	void NormalKeyHandler(unsigned char key, int xmouse, int ymouse);
	//void displayWin();		// Display winning screen if user manages to rescue the robot
	//void displayLose();	// Display lose screen (Unused)
}