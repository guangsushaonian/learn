#include "handle_geojson.h"
#include "handle_geojson.cc"

//Pass in the .geojson file to be processed
int main(int argc,char *argv[]) {
    
    if(argc < 2)
    {
        std::cout << "please input .geojson file address" << std::endl;
    }
    
    // /home/json_dp/dp/json_file/simple.geojson
      
    std::cout << argv[1] << std::endl;  // Original path

    std::cout << argv[2] << std::endl;  // Destination path

    //read .geojson file
    ifstream i_file(argv[1]);
    // create an array using push_back
    json j;      
    //convert json format
    i_file >> j;
      
    int count = 0;   //type numbers 
    count = j["/features"_json_pointer].size();
     

    std::cout << "========================================================" << std::endl;
    std::cout << count << std::endl;
    std::cout << "========================================================" << std::endl;

    
    for(auto it = j["/features"_json_pointer].begin(); it != j["/features"_json_pointer].end(); it++)
    {
        if((*it)["geometry"]["type"] == "LineString")
        {
            handleLineString(*it);
        }

        else if((*it)["geometry"]["type"] == "Polygon")
        {
            handlePolygon(*it);
        }

        else if((*it)["geometry"]["type"] == "MultiLineString")
        {
            handleMultiLineString(*it);
        }

        else if((*it)["geometry"]["type"] == "MultiPolygon")
        {
            handleMultiPolygon(*it);
        }       

    }

    std::ofstream o(argv[2]);
    o << std::setw(4) << j << std::endl;  

    return 0;

}
