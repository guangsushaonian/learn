#include "dp.h"

double pointDistToLine(Point p1, Point p2, Point p3)
{
	double dist;
	double A, B, C;
	A = -(p2.y - p1.y) / (p2.x - p1.x);
	B = 1.0;
	C = -A * p1.x - p1.y;
	dist = abs(A * p3.x + B * p3.y + C) / sqrt(A * A + B * B);
	return dist;
}
 
double getMaxDist(vector<Point> &Points, int begin, int end)
{
	vector<double> dists;
	double maxdist;
	for (int i = begin; i <= end; i++)
	{
		dists.push_back(pointDistToLine(Points[begin], Points[end], Points[i]));
	}
	auto max = max_element(dists.begin(), dists.end());
	return *max;
}
 
int getMaxDistIndex(vector<Point> &Points, int begin, int end)
{
	vector<double> dists;
	int index;
	for (int i = begin; i <= end; i++)
	{
		dists.push_back(pointDistToLine(Points[begin], Points[end], Points[i]));
	}
	auto max = max_element(dists.begin(), dists.end());
	index = Points[begin].ID + distance(dists.begin(),max);
	return index;
}
 
void douglas_Peucker(vector<Point> &Points, int begin, int end, double threshold)
{
	int mid;
	if (end - begin > 1)
	{
		if (getMaxDist(Points, begin, end) > threshold)
		{
			mid = getMaxDistIndex(Points, begin, end);
			douglas_Peucker(Points, begin, mid, threshold);
			douglas_Peucker(Points, mid, end, threshold);
		}
		else
		{
			for (int i = begin + 1; i < end; i++)
			{
				Points[i].isRemoved = true;
			}
		}
	}
	else
	{
		return;
	}
}