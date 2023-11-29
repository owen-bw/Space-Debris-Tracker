// This wrapper file was generated automatically by the GenDllWrappers program.

#include "DllUtils.h"
#include "TleDll.h"


// TleDll's function pointers definition
fnPtrTleInit                        TleInit;
fnPtrTleGetInfo                     TleGetInfo;
fnPtrTleLoadFile                    TleLoadFile;
fnPtrTleSaveFile                    TleSaveFile;
fnPtrTleRemoveSat                   TleRemoveSat;
fnPtrTleRemoveAllSats               TleRemoveAllSats;
fnPtrTleGetCount                    TleGetCount;
fnPtrTleGetLoaded                   TleGetLoaded;
fnPtrTleAddSatFrLines               TleAddSatFrLines;
fnPtrTleAddSatFrLinesML             TleAddSatFrLinesML;
fnPtrTleAddSatFrCsv                 TleAddSatFrCsv;
fnPtrTleAddSatFrCsvML               TleAddSatFrCsvML;
fnPtrTleAddSatFrFieldsGP            TleAddSatFrFieldsGP;
fnPtrTleAddSatFrFieldsGP2           TleAddSatFrFieldsGP2;
fnPtrTleAddSatFrFieldsGP2ML         TleAddSatFrFieldsGP2ML;
fnPtrTleUpdateSatFrFieldsGP         TleUpdateSatFrFieldsGP;
fnPtrTleUpdateSatFrFieldsGP2        TleUpdateSatFrFieldsGP2;
fnPtrTleAddSatFrFieldsSP            TleAddSatFrFieldsSP;
fnPtrTleAddSatFrFieldsSPML          TleAddSatFrFieldsSPML;
fnPtrTleUpdateSatFrFieldsSP         TleUpdateSatFrFieldsSP;
fnPtrTleSetField                    TleSetField;
fnPtrTleGetField                    TleGetField;
fnPtrTleGetAllFieldsGP              TleGetAllFieldsGP;
fnPtrTleGetAllFieldsGP2             TleGetAllFieldsGP2;
fnPtrTleGetAllFieldsSP              TleGetAllFieldsSP;
fnPtrTleParseGP                     TleParseGP;
fnPtrTleLinesToArray                TleLinesToArray;
fnPtrTleParseSP                     TleParseSP;
fnPtrTleGetLines                    TleGetLines;
fnPtrTleGetCsv                      TleGetCsv;
fnPtrTleGPFieldsToLines             TleGPFieldsToLines;
fnPtrTleGPFieldsToCsv               TleGPFieldsToCsv;
fnPtrTleGPArrayToLines              TleGPArrayToLines;
fnPtrTleGPArrayToCsv                TleGPArrayToCsv;
fnPtrTleSPFieldsToLines             TleSPFieldsToLines;
fnPtrTleGetSatKey                   TleGetSatKey;
fnPtrTleGetSatKeyML                 TleGetSatKeyML;
fnPtrTleFieldsToSatKey              TleFieldsToSatKey;
fnPtrTleFieldsToSatKeyML            TleFieldsToSatKeyML;
fnPtrTleAddSatFrArray               TleAddSatFrArray;
fnPtrTleAddSatFrArrayML             TleAddSatFrArrayML;
fnPtrTleUpdateSatFrArray            TleUpdateSatFrArray;
fnPtrTleDataToArray                 TleDataToArray;
fnPtrTleLinesToCsv                  TleLinesToCsv;
fnPtrTleCsvToLines                  TleCsvToLines;
fnPtrSetTleKeyMode                  SetTleKeyMode;
fnPtrGetTleKeyMode                  GetTleKeyMode;
fnPtrGetCheckSums                   GetCheckSums;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadTleDll()
{
   // Explicitly load the dll
   hLib = LoadLib(TleDll);


   // Assign function pointers to the appropriate dll functions
   TleInit = (fnPtrTleInit)GetFnPtr(hLib, (char*)"TleInit");
   TleGetInfo = (fnPtrTleGetInfo)GetFnPtr(hLib, (char*)"TleGetInfo");
   TleLoadFile = (fnPtrTleLoadFile)GetFnPtr(hLib, (char*)"TleLoadFile");
   TleSaveFile = (fnPtrTleSaveFile)GetFnPtr(hLib, (char*)"TleSaveFile");
   TleRemoveSat = (fnPtrTleRemoveSat)GetFnPtr(hLib, (char*)"TleRemoveSat");
   TleRemoveAllSats = (fnPtrTleRemoveAllSats)GetFnPtr(hLib, (char*)"TleRemoveAllSats");
   TleGetCount = (fnPtrTleGetCount)GetFnPtr(hLib, (char*)"TleGetCount");
   TleGetLoaded = (fnPtrTleGetLoaded)GetFnPtr(hLib, (char*)"TleGetLoaded");
   TleAddSatFrLines = (fnPtrTleAddSatFrLines)GetFnPtr(hLib, (char*)"TleAddSatFrLines");
   TleAddSatFrLinesML = (fnPtrTleAddSatFrLinesML)GetFnPtr(hLib, (char*)"TleAddSatFrLinesML");
   TleAddSatFrCsv = (fnPtrTleAddSatFrCsv)GetFnPtr(hLib, (char*)"TleAddSatFrCsv");
   TleAddSatFrCsvML = (fnPtrTleAddSatFrCsvML)GetFnPtr(hLib, (char*)"TleAddSatFrCsvML");
   TleAddSatFrFieldsGP = (fnPtrTleAddSatFrFieldsGP)GetFnPtr(hLib, (char*)"TleAddSatFrFieldsGP");
   TleAddSatFrFieldsGP2 = (fnPtrTleAddSatFrFieldsGP2)GetFnPtr(hLib, (char*)"TleAddSatFrFieldsGP2");
   TleAddSatFrFieldsGP2ML = (fnPtrTleAddSatFrFieldsGP2ML)GetFnPtr(hLib, (char*)"TleAddSatFrFieldsGP2ML");
   TleUpdateSatFrFieldsGP = (fnPtrTleUpdateSatFrFieldsGP)GetFnPtr(hLib, (char*)"TleUpdateSatFrFieldsGP");
   TleUpdateSatFrFieldsGP2 = (fnPtrTleUpdateSatFrFieldsGP2)GetFnPtr(hLib, (char*)"TleUpdateSatFrFieldsGP2");
   TleAddSatFrFieldsSP = (fnPtrTleAddSatFrFieldsSP)GetFnPtr(hLib, (char*)"TleAddSatFrFieldsSP");
   TleAddSatFrFieldsSPML = (fnPtrTleAddSatFrFieldsSPML)GetFnPtr(hLib, (char*)"TleAddSatFrFieldsSPML");
   TleUpdateSatFrFieldsSP = (fnPtrTleUpdateSatFrFieldsSP)GetFnPtr(hLib, (char*)"TleUpdateSatFrFieldsSP");
   TleSetField = (fnPtrTleSetField)GetFnPtr(hLib, (char*)"TleSetField");
   TleGetField = (fnPtrTleGetField)GetFnPtr(hLib, (char*)"TleGetField");
   TleGetAllFieldsGP = (fnPtrTleGetAllFieldsGP)GetFnPtr(hLib, (char*)"TleGetAllFieldsGP");
   TleGetAllFieldsGP2 = (fnPtrTleGetAllFieldsGP2)GetFnPtr(hLib, (char*)"TleGetAllFieldsGP2");
   TleGetAllFieldsSP = (fnPtrTleGetAllFieldsSP)GetFnPtr(hLib, (char*)"TleGetAllFieldsSP");
   TleParseGP = (fnPtrTleParseGP)GetFnPtr(hLib, (char*)"TleParseGP");
   TleLinesToArray = (fnPtrTleLinesToArray)GetFnPtr(hLib, (char*)"TleLinesToArray");
   TleParseSP = (fnPtrTleParseSP)GetFnPtr(hLib, (char*)"TleParseSP");
   TleGetLines = (fnPtrTleGetLines)GetFnPtr(hLib, (char*)"TleGetLines");
   TleGetCsv = (fnPtrTleGetCsv)GetFnPtr(hLib, (char*)"TleGetCsv");
   TleGPFieldsToLines = (fnPtrTleGPFieldsToLines)GetFnPtr(hLib, (char*)"TleGPFieldsToLines");
   TleGPFieldsToCsv = (fnPtrTleGPFieldsToCsv)GetFnPtr(hLib, (char*)"TleGPFieldsToCsv");
   TleGPArrayToLines = (fnPtrTleGPArrayToLines)GetFnPtr(hLib, (char*)"TleGPArrayToLines");
   TleGPArrayToCsv = (fnPtrTleGPArrayToCsv)GetFnPtr(hLib, (char*)"TleGPArrayToCsv");
   TleSPFieldsToLines = (fnPtrTleSPFieldsToLines)GetFnPtr(hLib, (char*)"TleSPFieldsToLines");
   TleGetSatKey = (fnPtrTleGetSatKey)GetFnPtr(hLib, (char*)"TleGetSatKey");
   TleGetSatKeyML = (fnPtrTleGetSatKeyML)GetFnPtr(hLib, (char*)"TleGetSatKeyML");
   TleFieldsToSatKey = (fnPtrTleFieldsToSatKey)GetFnPtr(hLib, (char*)"TleFieldsToSatKey");
   TleFieldsToSatKeyML = (fnPtrTleFieldsToSatKeyML)GetFnPtr(hLib, (char*)"TleFieldsToSatKeyML");
   TleAddSatFrArray = (fnPtrTleAddSatFrArray)GetFnPtr(hLib, (char*)"TleAddSatFrArray");
   TleAddSatFrArrayML = (fnPtrTleAddSatFrArrayML)GetFnPtr(hLib, (char*)"TleAddSatFrArrayML");
   TleUpdateSatFrArray = (fnPtrTleUpdateSatFrArray)GetFnPtr(hLib, (char*)"TleUpdateSatFrArray");
   TleDataToArray = (fnPtrTleDataToArray)GetFnPtr(hLib, (char*)"TleDataToArray");
   TleLinesToCsv = (fnPtrTleLinesToCsv)GetFnPtr(hLib, (char*)"TleLinesToCsv");
   TleCsvToLines = (fnPtrTleCsvToLines)GetFnPtr(hLib, (char*)"TleCsvToLines");
   SetTleKeyMode = (fnPtrSetTleKeyMode)GetFnPtr(hLib, (char*)"SetTleKeyMode");
   GetTleKeyMode = (fnPtrGetTleKeyMode)GetFnPtr(hLib, (char*)"GetTleKeyMode");
   GetCheckSums = (fnPtrGetCheckSums)GetFnPtr(hLib, (char*)"GetCheckSums");
}



// Free TleDll
void FreeTleDll()
{
   FreeLib(hLib, TleDll);
}
// ========================= End of auto generated code ==========================
