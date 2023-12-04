#include <vector>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "gl.h"
#include "TLEReader.h"
#include "SpaceDebris.h"

GLfloat* TLEReader::ReadFiles(int& numSats, double& epoch, vector<SpaceDebris>& debris) {
    // Load MainDll dll
    LoadDllMainDll();

    // Load EnvConst dll and assign function pointers
    LoadEnvConstDll();

    // Load TimeFunc dll and assign function pointers
    LoadTimeFuncDll();

    // Load AstroFunc dll and assign function pointers
    LoadAstroFuncDll();

    // Load Tle dll and assign function pointers
    LoadTleDll();

    // Load Sgp4Prop dll and assign function pointers
    LoadSgp4PropDll();
    
    Sgp4LoadFileAll("2023_332.txt");

    numSats = TleGetCount();

    std::cout << numSats << std::endl;

    vector<__int64> constructKeys(numSats);

    satKeys = constructKeys;

    TleGetLoaded(2, satKeys.data());

    GLfloat* points = new GLfloat[numSats * 3];

    TleGetField(satKeys[0], XF_TLE_EPOCH, valueStr);
    valueStr[GETSETSTRLEN-1] = 0;
    epoch = DTGToUTC(valueStr);

    for (int i = 0; i < numSats; i++) {
        if (Sgp4InitSat(satKeys[i]) != 0) {
            ShowMsgAndTerminate();
        }

        Sgp4PropDs50UTC(satKeys[i], epoch, &mse, pos, vel, llh);

        points[i * 3] = pos[0] / earthRadiusKm;
        points[i * 3 + 1] = pos[2] / earthRadiusKm;
        points[i * 3 + 2] = pos[1] / earthRadiusKm;
        
        SpaceDebris newDebris(i, i * 3, i * 3 + 2, i * 3 + 1);

        debris.push_back(newDebris);
    }

    return points;
}

void TLEReader::propagate(double time, GLfloat* points, int numSats) {
    for (int i = 0; i < numSats; i++) {
        Sgp4PropDs50UTC(satKeys[i], time, &mse, pos, vel, llh);

        points[i * 3] = pos[0] / earthRadiusKm;
        points[i * 3 + 1] = pos[2] / earthRadiusKm;
        points[i * 3 + 2] = pos[1] / earthRadiusKm;
    }
}

Datetime doubleToDate(double time) {
    int64_t totalSeconds = static_cast<int64_t>(time * 86400);

    std::time_t baseTime = std::mktime(new std::tm{0, 0, 0, 1, 0, 50});
    std::time_t targetTime = baseTime + totalSeconds;

    std::tm* timeStruct = std::gmtime(&targetTime);

    Datetime result;
    result.year = timeStruct->tm_year + 1900;
    result.month = timeStruct->tm_mon + 1;
    result.day = timeStruct->tm_mday;
    result.hours = timeStruct->tm_hour;
    result.minutes = timeStruct->tm_min;
    result.seconds = timeStruct->tm_sec;

    return result;
}

double dateToDouble(Datetime& tdate) {
    std::tm timeStruct = {};
    timeStruct.tm_year = tdate.year - 1900;
    timeStruct.tm_mon = tdate.month - 1;
    timeStruct.tm_mday = tdate.day;
    timeStruct.tm_hour = tdate.hours;
    timeStruct.tm_min = tdate.minutes;
    timeStruct.tm_sec = tdate.seconds;

    std::time_t timeSinceEpoch = std::mktime(&timeStruct);

    std::time_t localTime = timeSinceEpoch - timezone;

    std::time_t baseTime = std::mktime(new std::tm{0, 0, 0, 1, 0, 50}); // Jan 1, 1950
    double daysSince1950 = difftime(localTime, baseTime) / (60 * 60 * 24);

    return daysSince1950;
}