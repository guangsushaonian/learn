#ifndef _DP
#define _DP

#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "cmath"
#include <algorithm>
#include <cstring> 

using namespace std;

class Point
{
public:
	int ID;
	double x;
	double y;
	bool isRemoved = false;
};

void douglas_Peucker(vector<Point> &Points, int begin, int end, double threshold);

#endif