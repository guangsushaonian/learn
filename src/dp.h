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

typedef struct Point
{
public:
    int id;
    double x;
    double y;
    bool isRemoved = false;
}Point;

typedef struct Line{
    Point p1;
    Point p2;
}Line;

typedef struct {
    double dist;
    int index;
}DistAndIndex;

void douglasPeucker(vector<Point> &Points, int begin, int end, double threshold);

#endif