// This wrapper file was generated automatically by the GenDllWrappers program.

#include "DllUtils.h"
#include "TimeFuncDll.h"


// TimeFuncDll's function pointers definition
fnPtrTimeFuncInit                   TimeFuncInit;
fnPtrTimeFuncGetInfo                TimeFuncGetInfo;
fnPtrTConLoadFile                   TConLoadFile;
fnPtrTimeFuncLoadFile               TimeFuncLoadFile;
fnPtrIsTConFileLoaded               IsTConFileLoaded;
fnPtrTConSaveFile                   TConSaveFile;
fnPtrTConAddARec                    TConAddARec;
fnPtrTConAddOne                     TConAddOne;
fnPtrUTCToTConRec                   UTCToTConRec;
fnPtrTConRemoveAll                  TConRemoveAll;
fnPtrUTCToDTG20                     UTCToDTG20;
fnPtrUTCToDTG19                     UTCToDTG19;
fnPtrUTCToDTG17                     UTCToDTG17;
fnPtrUTCToDTG15                     UTCToDTG15;
fnPtrDTGToUTC                       DTGToUTC;
fnPtrUTCToTAI                       UTCToTAI;
fnPtrUTCToUT1                       UTCToUT1;
fnPtrUTCToET                        UTCToET;
fnPtrTAIToUTC                       TAIToUTC;
fnPtrTAIToUT1                       TAIToUT1;
fnPtrYrDaysToUTC                    YrDaysToUTC;
fnPtrUTCToYrDays                    UTCToYrDays;
fnPtrTimeComps1ToUTC                TimeComps1ToUTC;
fnPtrUTCToTimeComps1                UTCToTimeComps1;
fnPtrTimeComps2ToUTC                TimeComps2ToUTC;
fnPtrUTCToTimeComps2                UTCToTimeComps2;
fnPtrThetaGrnwch                    ThetaGrnwch;
fnPtrThetaGrnwchFK4                 ThetaGrnwchFK4;
fnPtrThetaGrnwchFK5                 ThetaGrnwchFK5;
fnPtrTimeConvFrTo                   TimeConvFrTo;
fnPtrGet6P                          Get6P;
fnPtrSet6P                          Set6P;
fnPtrGet6PCardLine                  Get6PCardLine;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadTimeFuncDll()
{
   // Explicitly load the dll
   hLib = LoadLib(TimeFuncDll);


   // Assign function pointers to the appropriate dll functions
   TimeFuncInit = (fnPtrTimeFuncInit)GetFnPtr(hLib, (char*)"TimeFuncInit");
   TimeFuncGetInfo = (fnPtrTimeFuncGetInfo)GetFnPtr(hLib, (char*)"TimeFuncGetInfo");
   TConLoadFile = (fnPtrTConLoadFile)GetFnPtr(hLib, (char*)"TConLoadFile");
   TimeFuncLoadFile = (fnPtrTimeFuncLoadFile)GetFnPtr(hLib, (char*)"TimeFuncLoadFile");
   IsTConFileLoaded = (fnPtrIsTConFileLoaded)GetFnPtr(hLib, (char*)"IsTConFileLoaded");
   TConSaveFile = (fnPtrTConSaveFile)GetFnPtr(hLib, (char*)"TConSaveFile");
   TConAddARec = (fnPtrTConAddARec)GetFnPtr(hLib, (char*)"TConAddARec");
   TConAddOne = (fnPtrTConAddOne)GetFnPtr(hLib, (char*)"TConAddOne");
   UTCToTConRec = (fnPtrUTCToTConRec)GetFnPtr(hLib, (char*)"UTCToTConRec");
   TConRemoveAll = (fnPtrTConRemoveAll)GetFnPtr(hLib, (char*)"TConRemoveAll");
   UTCToDTG20 = (fnPtrUTCToDTG20)GetFnPtr(hLib, (char*)"UTCToDTG20");
   UTCToDTG19 = (fnPtrUTCToDTG19)GetFnPtr(hLib, (char*)"UTCToDTG19");
   UTCToDTG17 = (fnPtrUTCToDTG17)GetFnPtr(hLib, (char*)"UTCToDTG17");
   UTCToDTG15 = (fnPtrUTCToDTG15)GetFnPtr(hLib, (char*)"UTCToDTG15");
   DTGToUTC = (fnPtrDTGToUTC)GetFnPtr(hLib, (char*)"DTGToUTC");
   UTCToTAI = (fnPtrUTCToTAI)GetFnPtr(hLib, (char*)"UTCToTAI");
   UTCToUT1 = (fnPtrUTCToUT1)GetFnPtr(hLib, (char*)"UTCToUT1");
   UTCToET = (fnPtrUTCToET)GetFnPtr(hLib, (char*)"UTCToET");
   TAIToUTC = (fnPtrTAIToUTC)GetFnPtr(hLib, (char*)"TAIToUTC");
   TAIToUT1 = (fnPtrTAIToUT1)GetFnPtr(hLib, (char*)"TAIToUT1");
   YrDaysToUTC = (fnPtrYrDaysToUTC)GetFnPtr(hLib, (char*)"YrDaysToUTC");
   UTCToYrDays = (fnPtrUTCToYrDays)GetFnPtr(hLib, (char*)"UTCToYrDays");
   TimeComps1ToUTC = (fnPtrTimeComps1ToUTC)GetFnPtr(hLib, (char*)"TimeComps1ToUTC");
   UTCToTimeComps1 = (fnPtrUTCToTimeComps1)GetFnPtr(hLib, (char*)"UTCToTimeComps1");
   TimeComps2ToUTC = (fnPtrTimeComps2ToUTC)GetFnPtr(hLib, (char*)"TimeComps2ToUTC");
   UTCToTimeComps2 = (fnPtrUTCToTimeComps2)GetFnPtr(hLib, (char*)"UTCToTimeComps2");
   ThetaGrnwch = (fnPtrThetaGrnwch)GetFnPtr(hLib, (char*)"ThetaGrnwch");
   ThetaGrnwchFK4 = (fnPtrThetaGrnwchFK4)GetFnPtr(hLib, (char*)"ThetaGrnwchFK4");
   ThetaGrnwchFK5 = (fnPtrThetaGrnwchFK5)GetFnPtr(hLib, (char*)"ThetaGrnwchFK5");
   TimeConvFrTo = (fnPtrTimeConvFrTo)GetFnPtr(hLib, (char*)"TimeConvFrTo");
   Get6P = (fnPtrGet6P)GetFnPtr(hLib, (char*)"Get6P");
   Set6P = (fnPtrSet6P)GetFnPtr(hLib, (char*)"Set6P");
   Get6PCardLine = (fnPtrGet6PCardLine)GetFnPtr(hLib, (char*)"Get6PCardLine");
}



// Free TimeFuncDll
void FreeTimeFuncDll()
{
   FreeLib(hLib, TimeFuncDll);
}
// ========================= End of auto generated code ==========================
