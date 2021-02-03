#include "handle_geojson.h"

void applyDpOnPoints(json *pointset, bool isPolygon)
{
    std::vector<Point> points;
    Point point;

    for (auto it = (*pointset).begin(); it != (*pointset).end(); it++)
    {
        point.x = (*it)[0];
        point.y = (*it)[1];
        points.push_back(point);
    }

    if (isPolygon == true)
    {
        douglasPeucker(points, 0, points.size() - 2, 5.0);
    }
    else
    {
        douglasPeucker(points, 0, points.size() - 1, 5.0);
    }

    (*pointset).clear();

    //assignment after DP
    for (auto it = points.begin(); it != points.end(); it++)
    {
        if ((*it).isRemoved == false)
        {
            (*pointset).push_back({(*it).x, (*it).y});
        }
    }
}

void handleLineString(json &lineString)
{

    json *lineStringPoint = &lineString["geometry"]["coordinates"];

    applyDpOnPoints(lineStringPoint, false);
}

void handlePolygon(json &polygon)
{

    json *polygonLine = &polygon["geometry"]["coordinates"];

    for (auto it = (*polygonLine).begin(); it != (*polygonLine).end(); it++)
    {
        applyDpOnPoints(&(*it), true);
    }
}

void handleMultiLineString(json &multiLineString)
{

    json *polygonLine = &multiLineString["geometry"]["coordinates"];

    for (auto it = (*polygonLine).begin(); it != (*polygonLine).end(); it++)
    {
        applyDpOnPoints(&(*it), false);
    }
}

void handleMultiPolygon(json &multiPolygon)
{

    json *polygon = &multiPolygon["geometry"]["coordinates"];

    for (auto it = (*polygon).begin(); it != (*polygon).end(); it++)
    {
        for (auto st = (*it).begin(); st != (*it).end(); st++)
        {
            applyDpOnPoints(&(*st), true);
        }
    }
}