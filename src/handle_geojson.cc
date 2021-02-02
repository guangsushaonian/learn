#include "handle_geojson.h"


void  twoDimensional(json *pointset,bool shape)
{
    std::vector<double> lat;       //Storage Latitude
    std::vector<double> lon;       //Storage Longitude
    std::vector<Point> point_line; //Storage point on LineString
    Point point;                   //class pont

    int count_point=0; 
    for(auto it = (*pointset).begin(); it != (*pointset).end(); it++)
    {
        point.x = (*it)[0];
        point.y = (*it)[1];
        point.ID = count_point;
        point_line.push_back(point);
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
    douglasPeucker(point_line, 0, count_point, 5.0);

    count_point = 0; 

    //clear point on the LineString
    (*pointset) = nullptr;

    //assignment after DP 
    std::cout << "\n\nLineString threshold=5.0" << std::endl;  
    for(auto it = point_line.begin(); it != point_line.end(); it++)
    {
        if((*it).isRemoved == false)
        {
            (*pointset)[count_point] = {(*it).x,(*it).y};
            ++count_point;
        }
    }
} 


void handleLineString(json &lineString)
{
    std::cout << "=================== this is LineString ======================" << std::endl;
     
    json *lineStringPoint = &lineString["geometry"]["coordinates"];

    twoDimensional(lineStringPoint,false);  

}


void handlePolygon(json &polygon)
{
    std::cout << "=================== this is Polygon ======================" << std::endl;

    json *polygonLine = &polygon["geometry"]["coordinates"];
     
    for(auto it = (*polygonLine).begin(); it != (*polygonLine).end(); it++)
    {        
        twoDimensional(&(*it),true);
    }

}

void handleMultiLineString(json &multiLineString)
{
    std::cout << "=================== this is MultiLineString ======================" << std::endl;
     
    json *polygonLine = &multiLineString["geometry"]["coordinates"];

    for(auto it = (*polygonLine).begin(); it != (*polygonLine).end(); it++)
    {        
        twoDimensional(&(*it),false);
    }
   
}

void handleMultiPolygon(json &multiPolygon)
{
    std::cout << "=================== this is MultiPolygon ======================" << std::endl;

    json *polygon = &multiPolygon["geometry"]["coordinates"];

    for(auto it = (*polygon).begin(); it != (*polygon).end(); it++)
    {
        for(auto st = (*it).begin(); st != (*it).end(); st++)
        {
            twoDimensional(&(*st),true);
        }
    } 

}