#include "handle_geojson.h"


void handle_LineString(json &j,int i)
{
    std::cout << "=================== this is LineString ======================" << std::endl;

    std::vector<double> lat;       //Storage accuracy
    std::vector<double> lon;       //Storage latitude
    std::vector<Point> point_line; //Storage point on LineString
    Point point;                   //class pont

    int count_point=0; 

    while(j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point] != nullptr)
    {        
        int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][0];
        int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][1];

        point.x = lat_value;
        point.y = lon_value;
        point.ID = count_point;
        point_line.push_back(point);
        ++count_point;
    }
    
    --count_point;

    //start DP
    douglas_Peucker(point_line, 0, count_point, 5.0);

    count_point = 0; 

    //clear point on the LineString
    j["/features"_json_pointer][i]["geometry"]["coordinates"] = nullptr;

    //assignment after DP 
    std::cout << "\n\nLineString threshold=5.0" << std::endl;
    for (int k = 0; k < point_line.size(); k++)
    {      
        if (point_line[k].isRemoved==false)
        {
            j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][0] = point_line[k].x;
            j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][1] = point_line[k].y;
            ++count_point;
            //std::cout << point_line[k].x << "," << point_line[k].y << "\n";
        }
    }
    
    //deposit (After processing LineString)
    std::ofstream o("pretty.json");
    o << std::setw(4) << j << std::endl;
}

void handle_Polygon(json &j,int i)
{
    std::cout << "=================== this is Polygon ======================" << std::endl;

    std::vector<double> lat;        //Storage accuracy
    std::vector<double> lon;        //Storage latitude
    std::vector<Point> point_line;  //Storage point on LineString
    Point point;                    //class pont

    int count_point=0;
    int count_polygon=0;

    count_polygon = j["/features"_json_pointer][i]["geometry"]["coordinates"].size();

    std::cout << count_polygon << std::endl;
    
    for(int k = 0; k<count_polygon; k++)
    {  
        while(j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point] != nullptr)
        {                
            int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][0];
            int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][1];

            point.x = lat_value;
            point.y = lon_value;
            point.ID = count_point;
            point_line.push_back(point);
            
            ++count_point;
        }    
        
        --count_point;
        --count_point;

        std::cout << "-------------------------clear----------------------------" << std::endl;
        j["/features"_json_pointer][i]["geometry"]["coordinates"][k] = nullptr;
        
        //start DP
        douglas_Peucker(point_line, 0, count_point, 5.0);
            
        count_point = 0;

        //assignment after DP 
        std::cout << "\n\nMultiLineString threshold=5.0" << std::endl;
        for (int h = 0; h < point_line.size(); h++)
        {
            if (point_line[h].isRemoved==false)
            {
                j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][0] = point_line[h].x;
                j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][1] = point_line[h].y;
                ++count_point;
            }
        }

        count_point = 0;
        point_line.clear();

    }

    //deposit (After processing MultiLineString)
    std::ofstream o("pretty_1.json");
    o << std::setw(4) << j << std::endl;
}

void handle_MultiLineString(json &j,int i)
{
    std::cout << "=================== this is MultiLineString ======================" << std::endl;

    std::vector<double> lat;        //Storage accuracy
    std::vector<double> lon;        //Storage latitude
    std::vector<Point> point_line;  //Storage point on LineString
    Point point;                    //class pont

    int count_point=0;
    int count_line=0;

    count_line = j["/features"_json_pointer][i]["geometry"]["coordinates"].size();

    std::cout << count_line << std::endl;
    
    for(int k = 0; k<count_line; k++)
    {  
        while(j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point] != nullptr)
        {                
            int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][0];
            int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][1];

            point.x = lat_value;
            point.y = lon_value;
            point.ID = count_point;
            point_line.push_back(point);
            
            ++count_point;
        }    
        count_point--;
        
        std::cout << "-------------------------clear----------------------------" << std::endl;
        j["/features"_json_pointer][i]["geometry"]["coordinates"][k] = nullptr;
        
        //start DP
        douglas_Peucker(point_line, 0, count_point, 5.0);
            
        count_point = 0;

        //assignment after DP 
        std::cout << "\n\nMultiLineString threshold=5.0" << std::endl;
        for (int h = 0; h < point_line.size(); h++)
        {
            if (point_line[h].isRemoved==false)
            {
                j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][0] = point_line[h].x;
                j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][1] = point_line[h].y;
                ++count_point;
            }
        }

        count_point = 0;
        point_line.clear();

    }

    //deposit (After processing MultiLineString)
    std::ofstream o("pretty_2.json");
    o << std::setw(4) << j << std::endl;
}

void handle_MultiPolygon(json &j,int i)
{
    std::cout << "=================== this is MultiPolygon ======================" << std::endl;
    std::vector<double> lat;        //Storage accuracy
    std::vector<double> lon;        //Storage latitude
    std::vector<Point> point_multiploygon;  //Storage point on LineString
    Point point;                    //class pont

    int count_point = 0;
    int count_line = 0;
    int count_polygon = 0;
    int count_polygon_nest = 0;
       
    count_polygon = j["/features"_json_pointer][i]["geometry"]["coordinates"].size();

    for(int k = 0; k < count_polygon; k++)
    {
        count_polygon_nest = j["/features"_json_pointer][i]["geometry"]["coordinates"][k].size();
        
        for(int l = 0; l < count_polygon_nest; l++)
        {
            while(j["/features"_json_pointer][i]["geometry"]["coordinates"][k][l][count_point] != nullptr)
            {                
                int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][l][count_point][0];
                int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][l][count_point][1];

                point.x = lat_value;
                point.y = lon_value;
                point.ID = count_point;
                point_multiploygon.push_back(point);
                
                ++count_point;
            }    
            
            --count_point;
            --count_point;

            std::cout << "-------------------------clear----------------------------" << std::endl;
            j["/features"_json_pointer][i]["geometry"]["coordinates"][k][l] = nullptr;
            
            //start DP
            douglas_Peucker(point_multiploygon, 0, count_point, 5.0);
                
            count_point = 0;

            //assignment after DP 
            std::cout << "\n\nMultiLineString threshold=5.0" << std::endl;
            for (int h = 0; h < point_multiploygon.size(); h++)
            {
                if (point_multiploygon[h].isRemoved==false)
                {
                    j["/features"_json_pointer][i]["geometry"]["coordinates"][k][l][count_point][0] = point_multiploygon[h].x;
                    j["/features"_json_pointer][i]["geometry"]["coordinates"][k][l][count_point][1] = point_multiploygon[h].y;
                    ++count_point;
                }
            }

            count_point = 0;
            point_multiploygon.clear();
        }

    }

    //deposit (After processing MultiPolygon)
    std::ofstream o("pretty_3.json");
    o << std::setw(4) << j << std::endl;
}