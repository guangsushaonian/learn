#include "dp.h"

double pointDistToLine(Point point, Line line)
{
	double A, B, C;
	A = -(line.p2.y - line.p1.y) / (line.p2.x - line.p1.x);
	B = 1.0;
	C = -A * line.p1.x - line.p1.y;
	return abs(A * point.x + B * point.y + C) / sqrt(A * A + B * B);	
}
 
DistAndIndex getMaxDist(vector<Point> &Points, int begin, int end)
{
	vector<double> dists;
	DistAndIndex distIndex;
	
	for (int i = begin; i <= end; i++)
	{
		Line line;
		line.p1 = Points[begin];
		line.p2 = Points[end];	
		dists.push_back(pointDistToLine(Points[i], line));
	}

	auto max = max_element(dists.begin(), dists.end());
	
	distIndex.index = begin + distance(dists.begin(),max);
    distIndex.dist = *max;
    
	return distIndex;
}
  
void douglasPeucker(vector<Point> &Points, int begin, int end, double threshold)
{
	int mid;
	if (end - begin > 1)
	{
		DistAndIndex distIndex = getMaxDist(Points,begin,end);
		if (distIndex.dist > threshold)
		{
			mid = distIndex.index;
			douglasPeucker(Points, begin, mid, threshold);
			douglasPeucker(Points, mid, end, threshold);
		}
		else
		{
			for (int i = begin + 1; i < end; i++)
			{
				Points[i].isRemoved = true;
			}
		}
	}
}