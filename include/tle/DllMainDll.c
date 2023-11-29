// This wrapper file was generated automatically by the GenDllWrappers program.

#include "DllUtils.h"
#include "DllMainDll.h"


// DllMainDll's function pointers definition
fnPtrDllMainInit                    DllMainInit;
fnPtrDllMainGetInfo                 DllMainGetInfo;
fnPtrDllMainLoadFile                DllMainLoadFile;
fnPtrOpenLogFile                    OpenLogFile;
fnPtrCloseLogFile                   CloseLogFile;
fnPtrLogMessage                     LogMessage;
fnPtrGetLastErrMsg                  GetLastErrMsg;
fnPtrGetLastInfoMsg                 GetLastInfoMsg;
fnPtrGetInitDllNames                GetInitDllNames;
fnPtrTestInterface                  TestInterface;
fnPtrTestInterface2                 TestInterface2;
fnPtrTestInterface3                 TestInterface3;
fnPtrGetMOICData                    GetMOICData;
fnPtrSetElsetKeyMode                SetElsetKeyMode;
fnPtrGetElsetKeyMode                GetElsetKeyMode;
fnPtrSetAllKeyMode                  SetAllKeyMode;
fnPtrGetAllKeyMode                  GetAllKeyMode;
fnPtrResetAllKeyMode                ResetAllKeyMode;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadDllMainDll()
{
   // Explicitly load the dll
   hLib = LoadLib(DllMainDll);


   // Assign function pointers to the appropriate dll functions
   DllMainInit = (fnPtrDllMainInit)GetFnPtr(hLib, (char*)"DllMainInit");
   DllMainGetInfo = (fnPtrDllMainGetInfo)GetFnPtr(hLib, (char*)"DllMainGetInfo");
   DllMainLoadFile = (fnPtrDllMainLoadFile)GetFnPtr(hLib, (char*)"DllMainLoadFile");
   OpenLogFile = (fnPtrOpenLogFile)GetFnPtr(hLib, (char*)"OpenLogFile");
   CloseLogFile = (fnPtrCloseLogFile)GetFnPtr(hLib, (char*)"CloseLogFile");
   LogMessage = (fnPtrLogMessage)GetFnPtr(hLib, (char*)"LogMessage");
   GetLastErrMsg = (fnPtrGetLastErrMsg)GetFnPtr(hLib, (char*)"GetLastErrMsg");
   GetLastInfoMsg = (fnPtrGetLastInfoMsg)GetFnPtr(hLib, (char*)"GetLastInfoMsg");
   GetInitDllNames = (fnPtrGetInitDllNames)GetFnPtr(hLib, (char*)"GetInitDllNames");
   TestInterface = (fnPtrTestInterface)GetFnPtr(hLib, (char*)"TestInterface");
   TestInterface2 = (fnPtrTestInterface2)GetFnPtr(hLib, (char*)"TestInterface2");
   TestInterface3 = (fnPtrTestInterface3)GetFnPtr(hLib, (char*)"TestInterface3");
   GetMOICData = (fnPtrGetMOICData)GetFnPtr(hLib, (char*)"GetMOICData");
   SetElsetKeyMode = (fnPtrSetElsetKeyMode)GetFnPtr(hLib, (char*)"SetElsetKeyMode");
   GetElsetKeyMode = (fnPtrGetElsetKeyMode)GetFnPtr(hLib, (char*)"GetElsetKeyMode");
   SetAllKeyMode = (fnPtrSetAllKeyMode)GetFnPtr(hLib, (char*)"SetAllKeyMode");
   GetAllKeyMode = (fnPtrGetAllKeyMode)GetFnPtr(hLib, (char*)"GetAllKeyMode");
   ResetAllKeyMode = (fnPtrResetAllKeyMode)GetFnPtr(hLib, (char*)"ResetAllKeyMode");
}



// Free DllMainDll
void FreeDllMainDll()
{
   FreeLib(hLib, DllMainDll);
}
// ========================= End of auto generated code ==========================
