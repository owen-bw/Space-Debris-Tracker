#include "debris.h"
#include "gl.h"
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
    GLfloat* ReadFile(char* fileName, int& numSats);
    void propagate();
};