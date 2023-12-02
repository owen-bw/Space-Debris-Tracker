#include "TLEReader.h"
#include <vector>
#include "gl.h"

GLfloat* TLEReader::ReadFile(char* fileName, int& numSats, double& epoch) {
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
    
    Sgp4LoadFileAll(fileName);

    numSats = TleGetCount();

    std::cout << numSats << std::endl;

    vector<__int64> constructKeys(numSats);

    satKeys = constructKeys;

    TleGetLoaded(2, satKeys.data());

    GLfloat* points = new GLfloat[numSats * 3];

    for (int i = 0; i < numSats; i++) {
        if (Sgp4InitSat(satKeys[i]) != 0) {
            ShowMsgAndTerminate();
        }

        TleGetField(satKeys[i], XF_TLE_EPOCH, valueStr);
        valueStr[GETSETSTRLEN-1] = 0;
        epoch = DTGToUTC(valueStr);

        Sgp4PropDs50UTC(satKeys[i], epoch, &mse, pos, vel, llh);

        points[i * 3] = pos[0] / earthRadiusKm;
        points[i * 3 + 1] = pos[2] / earthRadiusKm;
        points[i * 3 + 2] = pos[1] / earthRadiusKm;
    }

    //cout << points[0] << " " << points[1] << " " << points[2] << endl;

    return points;
}

void TLEReader::propagate(double time, GLfloat* points, int numSats) {
    for (int i = 0; i < numSats; i++) {
        // TleGetField(satKeys[i], XF_TLE_EPOCH, valueStr);
        // valueStr[GETSETSTRLEN-1] = 0;
        // epochDs50UTC = DTGToUTC(valueStr);

        Sgp4PropDs50UTC(satKeys[i], time, &mse, pos, vel, llh);

        points[i * 3] = pos[0] / earthRadiusKm;
        points[i * 3 + 1] = pos[2] / earthRadiusKm;
        points[i * 3 + 2] = pos[1] / earthRadiusKm;
    }
}