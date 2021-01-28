#ifndef DP_H
#define DP_H


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
	string Name;
	double x;
	double y;
	bool isRemoved = false;
};

void DP(vector<Point> &Points, int begin, int end, double threshold);

#endif //DP_H