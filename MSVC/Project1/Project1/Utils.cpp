// Contains definitions of the helper functions used across different 
// classes defined in the heaeder file

#include <iostream>
#include "Utils.h"

using namespace std;

// Returns absolute value of number
double Utils::absVal(double & num) {
	return ((num > 0) ? num : -num);
}