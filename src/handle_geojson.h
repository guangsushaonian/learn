#ifndef _HANDLE_GEOGSON
#define _HANDLE_GEOGSON

#include "nlohmann/json.hpp"
#include <iomanip>
#include "dp.h"

using namespace nlohmann;

void handleLineString(json &lineString);
void handlePolygon(json &polygon);
void handleMultiLineString(json &multiLineString);
void handleMultiPolygon(json &multiPolygon);

#endif