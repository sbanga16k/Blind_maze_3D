#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>
#include "fssimplewindow.h"

class mazeData
{
	int M[35][35];
	int factor; 
public:
	mazeData(); 
	void load(char* name, int len);
	int getValMat(int r, int c);  //Returns value at that index
	void drawCuboid(int x, int , int z);
	int getFactor(); 
};

