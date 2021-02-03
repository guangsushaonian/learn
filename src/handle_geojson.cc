#include "handle_geojson.h"

/*  
   when json's type is "LineString" or "MultiLineString" ,shape is equal to 'false'.
   when json's is "Polygon" or "MultiPolygon" ,shape is equal to 'true' . 
   I need this way,to delete duplicate points on "Polygon" and "MultiPolygon".
*/  
void  dpToPoints(json *pointset,bool shape)
{
    std::vector<double> lat;       
    std::vector<double> lon;       
    std::vector<Point> points; 
    Point point;                   

    int count_point=0; 
    for(auto it = (*pointset).begin(); it != (*pointset).end(); it++)
    {
        point.x = (*it)[0];
        point.y = (*it)[1];
        points.push_back(point);
        ++count_point;
    }

    if(shape == true)
    {
        --count_point;
        --count_point;
    }
    else{
        --count_point;
    }

    //start DP
    douglasPeucker(points, 0, count_point, 5.0);

    count_point = 0; 

    //clear point on the LineString
    (*pointset).clear();

    //assignment after DP 
    for(auto it = points.begin(); it != points.end(); it++)
    {
        if((*it).isRemoved == false)
        {
            (*pointset).push_back({(*it).x,(*it).y});
        }
    }
} 


void handleLineString(json &lineString)
{
     
    json *lineStringPoint = &lineString["geometry"]["coordinates"];

    dpToPoints(lineStringPoint,false);  

}


void handlePolygon(json &polygon)
{

    json *polygonLine = &polygon["geometry"]["coordinates"];
     
    for(auto it = (*polygonLine).begin(); it != (*polygonLine).end(); it++)
    {        
        dpToPoints(&(*it),true);
    }

}

void handleMultiLineString(json &multiLineString)
{
     
    json *polygonLine = &multiLineString["geometry"]["coordinates"];

    for(auto it = (*polygonLine).begin(); it != (*polygonLine).end(); it++)
    {        
        dpToPoints(&(*it),false);
    }
   
}

void handleMultiPolygon(json &multiPolygon)
{

    json *polygon = &multiPolygon["geometry"]["coordinates"];

    for(auto it = (*polygon).begin(); it != (*polygon).end(); it++)
    {
        for(auto st = (*it).begin(); st != (*it).end(); st++)
        {
            dpToPoints(&(*st),true);
        }
    } 

}