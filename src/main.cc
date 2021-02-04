#include "handle_geojson.h"


//Pass in the .geojson file to be processed
int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <GeoJSON file>" << std::endl;
    }

    ifstream i_file(argv[1]);
    // create an array using push_back
    json j;
    //convert json format
    i_file >> j;

    for (auto feature = j["/features"_json_pointer].begin(); feature != j["/features"_json_pointer].end(); feature++)
    {
        if ((*feature)["geometry"]["type"] == "LineString")
        {
            handleLineString(*feature);
        }

        else if ((*feature)["geometry"]["type"] == "Polygon")
        {
            handlePolygon(*feature);
        }

        else if ((*feature)["geometry"]["type"] == "MultiLineString")
        {
            handleMultiLineString(*feature);
        }

        else if ((*feature)["geometry"]["type"] == "MultiPolygon")
        {
            handleMultiPolygon(*feature);
        }
    }

    std::cout << std::setw(4) << j << std::endl;

    return 0;
}
