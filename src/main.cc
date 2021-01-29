#include "dp.h"
#include "nlohmann/json.hpp"
#include <iomanip>

using namespace nlohmann;

int main() {

    // create an array using push_back
    json j;
    
    //read .geojson file
    ifstream i_file("/home/json_dp/dp/json_file/simple.geojson");
    
    //convert json format
    i_file >> j;
      
    //std::cout << j << std::endl;

    int count = 0;   //type numbers 
    count = j["/features"_json_pointer].size();
  
    std::cout << "========================================================" << std::endl;
    std::cout << count << std::endl;
    std::cout << "========================================================" << std::endl;


    for(int i = 0; i < count; i++)
    {   

        if(j["/features"_json_pointer][i]["geometry"]["type"] == "LineString")
        {
            std::cout << "=================== this is LineString ======================" << std::endl;

            std::vector<double> lat;       //Storage accuracy
            std::vector<double> lon;       //Storage latitude
            std::vector<Point> point_line; //Storage point on LineString
            Point point;                   //class pont

            int count_point=0; 

            while(j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point] != nullptr)
            {
                //std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][0] << std::endl;
                //std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][1] << std::endl;
                
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
            DP(point_line, 0, count_point, 5.0);

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

        else if(j["/features"_json_pointer][i]["geometry"]["type"] == "Polygon")
        {
            std::cout << "=================== this is Polygon ======================" << std::endl;

            std::vector<double> lat;        //Storage accuracy
            std::vector<double> lon;        //Storage latitude
            std::vector<Point> point_line;  //Storage point on LineString
            Point point;                    //class pont

            int count_point=0;

            while(j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point] != nullptr)
            {
                //std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][0] << std::endl;
                //std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][1] << std::endl;
                
                int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][0];
                int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][1];

                point.x = lat_value;
                point.y = lon_value;
                point.ID = count_point;
                point_line.push_back(point);
                ++count_point;
            }
            
            --count_point;
            --count_point;
            //start DP
            DP(point_line, 0, count_point, 5.0);

            count_point = 0; 
            j["/features"_json_pointer][i]["geometry"]["coordinates"][0] = nullptr;

            //assignment after DP 
            std::cout << "\n\nPolygon threshold=5.0" << std::endl;
	        for (int k = 0; k < point_line.size(); k++)
	        {
	        	if (point_line[k].isRemoved==false)
		        {

                    j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][0] = point_line[k].x;
                    j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][1] = point_line[k].y;
                    ++count_point;
			        //std::cout << point_line[k].x << "," << point_line[k].y << "\n";
		        }
	        }

            //deposit (After processing Polygon)
            std::ofstream o("pretty_1.json");
            o << std::setw(4) << j << std::endl;
        }

        else if(j["/features"_json_pointer][i]["geometry"]["type"] == "MultiLineString")
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
                    //std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][0] << std::endl;
                    //std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][1] << std::endl;
                
                      
                    int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][0];
                    int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][count_point][1];

                    point.x = lat_value;
                    point.y = lon_value;
                    point.ID = count_point;
                    point_line.push_back(point);
                    
                    ++count_point;
                    
                    //std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][k] << std::endl; 
                }    
                count_point--;
                
                std::cout << "-------------------------clear----------------------------" << std::endl;
                j["/features"_json_pointer][i]["geometry"]["coordinates"][k] = nullptr;
                
                //start DP
                DP(point_line, 0, count_point, 5.0);
                 
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
                        //std::cout << point_line[h].x << "," << point_line[h].y << "\n";
                    }
                }

                count_point = 0;
                point_line.clear();

            }

            //deposit (After processing MultiLineString)
            std::ofstream o("pretty_2.json");
            o << std::setw(4) << j << std::endl;

        }

        else if(j["/features"_json_pointer][i]["geometry"]["type"] == "MultiPolygon")
        {
            std::cout << "=================== this is MultiPolygon ======================" << std::endl;
            std::vector<double> lat;        //Storage accuracy
            std::vector<double> lon;        //Storage latitude
            std::vector<Point> point_line;  //Storage point on LineString
            Point point;                    //class pont

            int count_point = 0;
            int count_line = 0;
            int count_polygon = 0;

            count_polygon = j["/features"_json_pointer][i]["geometry"]["coordinates"].size();

            
            for(int k = 0; k < count_polygon; k++)
            {
                while(j["/features"_json_pointer][i]["geometry"]["coordinates"][k][0][count_point] != nullptr)
                {         
                    int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][0][count_point][0];
                    int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][k][0][count_point][1];

                    point.x = lat_value;
                    point.y = lon_value;
                    point.ID = count_point;
                    point_line.push_back(point);
                    
                    ++count_point;

                    //std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][k][0] << std::endl; 
                }    

                count_point--;
                count_point--;
                

                std::cout << "-------------------------clear----------------------------" << std::endl;
                j["/features"_json_pointer][i]["geometry"]["coordinates"][k][0] = nullptr;
                
                //start DP
                DP(point_line, 0, count_point, 5.0);
                 
                count_point = 0;

                //assignment after DP 
                std::cout << "\n\nMultiPolygon threshold=5.0" << std::endl;

                for (int h = 0; h < point_line.size(); h++)
                {
                    if (point_line[h].isRemoved==false)
                    {

                        j["/features"_json_pointer][i]["geometry"]["coordinates"][k][0][count_point][0] = point_line[h].x;
                        j["/features"_json_pointer][i]["geometry"]["coordinates"][k][0][count_point][1] = point_line[h].y;
                        ++count_point;
                        std::cout << point_line[h].x << "," << point_line[h].y << "\n";
                    }
                }
                
                count_point = 0;
                point_line.clear();
                
            }

            //deposit (After processing MultiPolygon)
            std::ofstream o("pretty_3.json");
            o << std::setw(4) << j << std::endl;


        }


    }

}
