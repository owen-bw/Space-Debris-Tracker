#include "debris.h"
#include "gl.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

#ifdef __cplusplus
extern "C" 
{
#endif

#include "tle/DllMainDll_Service.h" 
#include "tle/TimeFuncDll_Service.h"
#include "tle/DllMainDll.h"
#include "tle/EnvConstDll.h"
#include "tle/AstroFuncDll.h"
#include "tle/TimeFuncDll.h"
#include "tle/TleDll.h"
#include "tle/Sgp4PropDll.h"
#ifdef __cplusplus
}
#endif

#pragma once

struct Datetime {
    int day;
    int month;
    int year;

    int hours;
    int minutes;
    int seconds;
};

class TLEReader {
    vector<__int64> satKeys;
    const double earthRadiusKm = 6371.0;

    double 
    pos[3],           //Position (km)
    vel[3],           //Velocity (km/s)
    llh[3],           // Latitude(deg), Longitude(deg), Height above Geoid (km)
    meanKep[6],       //Mean Keplerian elements
    oscKep[6],        //Osculating Keplerian elements
    nodalApPer[3],    //Nodal period, apogee, perigee
    epochDs50UTC,
    mse,
    ds50UTC;

    char  valueStr[GETSETSTRLEN];

    public:
    GLfloat* ReadFile(string fileName, int& numSats, double& epoch);
    void propagate(double time, GLfloat* points, int numSats);
};

Datetime doubleToDate(double time);
double dateToDouble(Datetime& tdate);