// This wrapper file was generated automatically by the GenDllWrappers program.

#include "DllUtils.h"
#include "EnvConstDll.h"


// EnvConstDll's function pointers definition
fnPtrEnvInit                        EnvInit;
fnPtrEnvGetInfo                     EnvGetInfo;
fnPtrEnvLoadFile                    EnvLoadFile;
fnPtrEnvSaveFile                    EnvSaveFile;
fnPtrEnvGetFkIdx                    EnvGetFkIdx;
fnPtrEnvSetFkIdx                    EnvSetFkIdx;
fnPtrEnvGetGeoIdx                   EnvGetGeoIdx;
fnPtrEnvSetGeoIdx                   EnvSetGeoIdx;
fnPtrEnvGetGeoStr                   EnvGetGeoStr;
fnPtrEnvSetGeoStr                   EnvSetGeoStr;
fnPtrEnvGetGeoConst                 EnvGetGeoConst;
fnPtrEnvGetFkConst                  EnvGetFkConst;
fnPtrEnvGetFkPtr                    EnvGetFkPtr;
fnPtrEnvSetEarthShape               EnvSetEarthShape;
fnPtrEnvGetEarthShape               EnvGetEarthShape;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadEnvConstDll()
{
   // Explicitly load the dll
   hLib = LoadLib(EnvConstDll);


   // Assign function pointers to the appropriate dll functions
   EnvInit = (fnPtrEnvInit)GetFnPtr(hLib, (char*)"EnvInit");
   EnvGetInfo = (fnPtrEnvGetInfo)GetFnPtr(hLib, (char*)"EnvGetInfo");
   EnvLoadFile = (fnPtrEnvLoadFile)GetFnPtr(hLib, (char*)"EnvLoadFile");
   EnvSaveFile = (fnPtrEnvSaveFile)GetFnPtr(hLib, (char*)"EnvSaveFile");
   EnvGetFkIdx = (fnPtrEnvGetFkIdx)GetFnPtr(hLib, (char*)"EnvGetFkIdx");
   EnvSetFkIdx = (fnPtrEnvSetFkIdx)GetFnPtr(hLib, (char*)"EnvSetFkIdx");
   EnvGetGeoIdx = (fnPtrEnvGetGeoIdx)GetFnPtr(hLib, (char*)"EnvGetGeoIdx");
   EnvSetGeoIdx = (fnPtrEnvSetGeoIdx)GetFnPtr(hLib, (char*)"EnvSetGeoIdx");
   EnvGetGeoStr = (fnPtrEnvGetGeoStr)GetFnPtr(hLib, (char*)"EnvGetGeoStr");
   EnvSetGeoStr = (fnPtrEnvSetGeoStr)GetFnPtr(hLib, (char*)"EnvSetGeoStr");
   EnvGetGeoConst = (fnPtrEnvGetGeoConst)GetFnPtr(hLib, (char*)"EnvGetGeoConst");
   EnvGetFkConst = (fnPtrEnvGetFkConst)GetFnPtr(hLib, (char*)"EnvGetFkConst");
   EnvGetFkPtr = (fnPtrEnvGetFkPtr)GetFnPtr(hLib, (char*)"EnvGetFkPtr");
   EnvSetEarthShape = (fnPtrEnvSetEarthShape)GetFnPtr(hLib, (char*)"EnvSetEarthShape");
   EnvGetEarthShape = (fnPtrEnvGetEarthShape)GetFnPtr(hLib, (char*)"EnvGetEarthShape");
}



// Free EnvConstDll
void FreeEnvConstDll()
{
   FreeLib(hLib, EnvConstDll);
}
// ========================= End of auto generated code ==========================
