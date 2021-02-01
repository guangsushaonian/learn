#ifndef _HANDLE_GEOGSON
#define _HANDLE_GEOGSON

#include "nlohmann/json.hpp"
#include <iomanip>
using namespace nlohmann;
#include "dp.h"

void handle_LineString(json &j,int i);
void handle_Polygon(json &j,int i);
void handle_MultiLineString(json &j,int i);
void handle_MultiPolygon(json &j,int i);

#endif