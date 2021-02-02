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

typedef struct Line{
	Point p1;
	Point p2;
}Line;

typedef struct {
    double dist;
	int index;
}distAndIndex;

void douglasPeucker(vector<Point> &Points, int begin, int end, double threshold);

#endif