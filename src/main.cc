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
      
    std::cout << j << std::endl;

    int count = 0;   //type numbers
    //std::cout << "size:" << j["/features"_json_pointer].size() << "\n";

     
    count = j["/features"_json_pointer].size();

    
    std::cout << count << std::endl;
  
    for(int i = 0; i < count; i++)
    {   

        if(j["/features"_json_pointer][i]["geometry"]["type"] == "LineString")
        {
            std::vector<double> lat;
            std::vector<double> lon;
            std::vector<Point> point_line;
            Point point;

            int count_point=0;

            while(j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point] != nullptr)
            {
                std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][0] << std::endl;
                std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][1] << std::endl;
                
                int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][0];
                int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][1];

                //lat.push_back(lat_value);
                //lon.push_back(lon_value);
                point.x = lat_value;
                point.y = lon_value;
                point.ID = count_point;
                point_line.push_back(point);
                ++count_point;
            }
            
            //start DP
            DP(point_line, 0, count, 5.0);

            count_point = 0; 

            j["/features"_json_pointer][i]["geometry"]["coordinates"] = nullptr;

            std::cout << "\n\nthreshold=5.0" << std::endl;
	        for (int k = 0; k < point_line.size(); k++)
	        {
	        	if (point_line[k].isRemoved==false)
		        {

                    j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][0] = point_line[k].x;
                    j["/features"_json_pointer][i]["geometry"]["coordinates"][count_point][1] = point_line[k].y;
                    ++count_point;
			        std::cout << point_line[k].x << "," << point_line[k].y << "\n";
		        }
	        }

            std::ofstream o("pretty.json");
            o << std::setw(4) << j << std::endl;

        }

        else if(j["/features"_json_pointer][i]["geometry"]["type"] == "Polygon")
        {
            std::vector<double> lat;
            std::vector<double> lon;
            std::vector<Point> point_line;
            Point point;

            int count_point=0;

            while(j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point] != nullptr)
            {
                std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][0] << std::endl;
                std::cout << j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][1] << std::endl;
                
                int lat_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][0];
                int lon_value = j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][1];

                point.x = lat_value;
                point.y = lon_value;
                point.ID = count_point;
                point_line.push_back(point);
                ++count_point;
            }
            
            //start DP
            DP(point_line, 0, count, 5.0);

            count_point = 0; 
            j["/features"_json_pointer][i]["geometry"]["coordinates"][0] = nullptr;

            std::cout << "\n\nthreshold=5.0" << std::endl;
	        for (int k = 0; k < point_line.size(); k++)
	        {
	        	if (point_line[k].isRemoved==false)
		        {

                    j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][0] = point_line[k].x;
                    j["/features"_json_pointer][i]["geometry"]["coordinates"][0][count_point][1] = point_line[k].y;
                    ++count_point;
			        std::cout << point_line[k].x << "," << point_line[k].y << "\n";
		        }
	        }

            std::cout << std::setw(4) << j << std::endl;
           
            std::ofstream o("pretty_1.json");
            o << std::setw(4) << j << std::endl;
        }
    }


    

}
