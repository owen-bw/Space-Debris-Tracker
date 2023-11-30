#include "debris.h"
#include <iostream>


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

class TLEReader {
    public:
    void ReadFile(char* fileName) {
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

        int numSats = TleGetCount();

        std::cout << numSats << std::endl;

        vector<__int64> satKeys(numSats);

        TleGetLoaded(2, satKeys.data());

        for (int i = 0; i < numSats; i++) {

        }
    }
};