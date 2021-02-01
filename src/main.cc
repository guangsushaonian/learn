#include "handle_geojson.h"
#include "handle_geojson.cc"

//Pass in the .geojson file to be processed
int main(int argc,char *argv[]) {
    
    if(argc < 2)
    {
        std::cout << "please input .geojson file address" << std::endl;
    }

    // /home/json_dp/dp/json_file/simple.geojson
     
    cout << argv[1] << endl; 

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

    for(int i = 0; i < count; i++)
    {   
        if(j["/features"_json_pointer][i]["geometry"]["type"] == "LineString")
        {
            handle_LineString(j,i);
        }  

        else if(j["/features"_json_pointer][i]["geometry"]["type"] == "Polygon")
        {
            handle_Polygon(j,i);
        }

        else if(j["/features"_json_pointer][i]["geometry"]["type"] == "MultiLineString")
        {
            handle_MultiLineString(j,i);
        }

        else if(j["/features"_json_pointer][i]["geometry"]["type"] == "MultiPolygon")
        {
            handle_MultiPolygon(j,i);
        }
    }

    return 0;

}
