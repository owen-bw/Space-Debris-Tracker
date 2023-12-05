/****************************************************************/
/*                       TLEReader (Header)                     */
/*                           Blake Owen                         */
/*        This implementation uses the US SpaceForce publicly   */
/*        released SGP4 propagation libraries for reading and   */
/*        propagating TLE debris and satellite objects.         */
/****************************************************************/

#include "SpaceDebris.h"
#include "gl.h"
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

#ifdef __cplusplus
extern "C" 
{
#endif

// https://www.space-track.org/documentation#sgp4
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
    unordered_set<int> uniqueSats;
    unordered_set<int> addedSet;

    double 
    pos[3],           //Position (km)
    vel[3],           //Velocity (km/s)
    llh[3],           //Latitude(deg), Longitude(deg), Height above Geoid (km)
    meanKep[6],       //Mean Keplerian elements
    oscKep[6],        //Osculating Keplerian elements
    nodalApPer[3],    //Nodal period, apogee, perigee
    epochDs50UTC,
    mse,
    ds50UTC;

    char  valueStr[GETSETSTRLEN];

    public:
    __int64 getKey(int i) {return satKeys.at(i);}
    bool isAdded(int id) {return (addedSet.find(id) != addedSet.end());}
    GLfloat* ReadFiles(int& numSats, double& epoch, vector<SpaceDebris>& debris);
    void propagate(double time, GLfloat* points, int numSats, bool setDebris, vector<SpaceDebris>& debris);
};

Datetime doubleToDate(double time);
double dateToDouble(Datetime& tdate);