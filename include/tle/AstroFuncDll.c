// This wrapper file was generated automatically by the GenDllWrappers program.

#include "DllUtils.h"
#include "AstroFuncDll.h"


// AstroFuncDll's function pointers definition
fnPtrAstroFuncInit                  AstroFuncInit;
fnPtrAstroFuncGetInfo               AstroFuncGetInfo;
fnPtrKepToEqnx                      KepToEqnx;
fnPtrKepToPosVel                    KepToPosVel;
fnPtrKepToUVW                       KepToUVW;
fnPtrClassToEqnx                    ClassToEqnx;
fnPtrEqnxToClass                    EqnxToClass;
fnPtrEqnxToKep                      EqnxToKep;
fnPtrEqnxToPosVel                   EqnxToPosVel;
fnPtrPosVelToEqnx                   PosVelToEqnx;
fnPtrPosVelMuToEqnx                 PosVelMuToEqnx;
fnPtrPosVelToKep                    PosVelToKep;
fnPtrPosVelMuToKep                  PosVelMuToKep;
fnPtrPosVelToUUVW                   PosVelToUUVW;
fnPtrPosVelToPTW                    PosVelToPTW;
fnPtrSolveKepEqtn                   SolveKepEqtn;
fnPtrCompTrueAnomaly                CompTrueAnomaly;
fnPtrNToA                           NToA;
fnPtrAToN                           AToN;
fnPtrKozaiToBrouwer                 KozaiToBrouwer;
fnPtrBrouwerToKozai                 BrouwerToKozai;
fnPtrKepOscToMean                   KepOscToMean;
fnPtrXYZToLLH                       XYZToLLH;
fnPtrXYZToLLHTime                   XYZToLLHTime;
fnPtrLLHToXYZ                       LLHToXYZ;
fnPtrLLHToXYZTime                   LLHToXYZTime;
fnPtrEFGToECI                       EFGToECI;
fnPtrEFGToECITime                   EFGToECITime;
fnPtrECIToEFG                       ECIToEFG;
fnPtrECIToEFGTime                   ECIToEFGTime;
fnPtrECRToEFG                       ECRToEFG;
fnPtrECRToEFGTime                   ECRToEFGTime;
fnPtrEFGToECR                       EFGToECR;
fnPtrEFGToECRTime                   EFGToECRTime;
fnPtrEFGPosToLLH                    EFGPosToLLH;
fnPtrLLHToEFGPos                    LLHToEFGPos;
fnPtrRotJ2KToDate                   RotJ2KToDate;
fnPtrRotDateToJ2K                   RotDateToJ2K;
fnPtrCompSunMoonPos                 CompSunMoonPos;
fnPtrCompSunPos                     CompSunPos;
fnPtrCompMoonPos                    CompMoonPos;
fnPtrAstroConvFrTo                  AstroConvFrTo;
fnPtrRADecToLAD                     RADecToLAD;
fnPtrAzElToLAD                      AzElToLAD;
fnPtrECIToTopoComps                 ECIToTopoComps;
fnPtrRaDecToAzEl                    RaDecToAzEl;
fnPtrRaDecToAzElTime                RaDecToAzElTime;
fnPtrAzElToRaDec                    AzElToRaDec;
fnPtrAzElToRaDecTime                AzElToRaDecTime;
fnPtrRAEToECI                       RAEToECI;
fnPtrGetInitialDrag                 GetInitialDrag;
fnPtrCovMtxPTWToUVW                 CovMtxPTWToUVW;
fnPtrCovMtxUVWToPTW                 CovMtxUVWToPTW;
fnPtrEarthObstructionAngles         EarthObstructionAngles;
fnPtrIsPointSunlit                  IsPointSunlit;
fnPtrRotRADecl                      RotRADecl;
fnPtrRotRADec_DateToEqnx            RotRADec_DateToEqnx;
fnPtrRotRADec_EqnxToDate            RotRADec_EqnxToDate;
fnPtrCovMtxEqnxToUVW                CovMtxEqnxToUVW;
fnPtrCovMtxUVWToEqnx                CovMtxUVWToEqnx;
fnPtrCovMtxECIToUVW                 CovMtxECIToUVW;
fnPtrCovMtxUVWToECI                 CovMtxUVWToECI;
fnPtrCovMtxECIToEFG                 CovMtxECIToEFG;
fnPtrCovMtxEFGToECI                 CovMtxEFGToECI;
fnPtrMtx6x6ToLTA21                  Mtx6x6ToLTA21;
fnPtrLTA21ToMtx6x6                  LTA21ToMtx6x6;
fnPtrMtx9x9ToLTA45                  Mtx9x9ToLTA45;
fnPtrLTA45ToMtx9x9                  LTA45ToMtx9x9;
fnPtrPropCovFrState                 PropCovFrState;
fnPtrCovMtxECIToEqnx                CovMtxECIToEqnx;
fnPtrCovMtxEqnxToECI9x9             CovMtxEqnxToECI9x9;
fnPtrCovMtxEqnxToUVW9x9             CovMtxEqnxToUVW9x9;
fnPtrCovMtxUpdate                   CovMtxUpdate;
fnPtrAberrationAnnual               AberrationAnnual;
fnPtrAberrationDiurnal              AberrationDiurnal;
fnPtrJplSetParameters               JplSetParameters;
fnPtrJplGetParameters               JplGetParameters;
fnPtrJplReset                       JplReset;
fnPtrJplCompSunMoonVec              JplCompSunMoonVec;
fnPtrJplCompSunMoonPos              JplCompSunMoonPos;
fnPtrRemoveJpl                      RemoveJpl;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadAstroFuncDll()
{
   // Explicitly load the dll
   hLib = LoadLib(AstroFuncDll);


   // Assign function pointers to the appropriate dll functions
   AstroFuncInit = (fnPtrAstroFuncInit)GetFnPtr(hLib, (char*)"AstroFuncInit");
   AstroFuncGetInfo = (fnPtrAstroFuncGetInfo)GetFnPtr(hLib, (char*)"AstroFuncGetInfo");
   KepToEqnx = (fnPtrKepToEqnx)GetFnPtr(hLib, (char*)"KepToEqnx");
   KepToPosVel = (fnPtrKepToPosVel)GetFnPtr(hLib, (char*)"KepToPosVel");
   KepToUVW = (fnPtrKepToUVW)GetFnPtr(hLib, (char*)"KepToUVW");
   ClassToEqnx = (fnPtrClassToEqnx)GetFnPtr(hLib, (char*)"ClassToEqnx");
   EqnxToClass = (fnPtrEqnxToClass)GetFnPtr(hLib, (char*)"EqnxToClass");
   EqnxToKep = (fnPtrEqnxToKep)GetFnPtr(hLib, (char*)"EqnxToKep");
   EqnxToPosVel = (fnPtrEqnxToPosVel)GetFnPtr(hLib, (char*)"EqnxToPosVel");
   PosVelToEqnx = (fnPtrPosVelToEqnx)GetFnPtr(hLib, (char*)"PosVelToEqnx");
   PosVelMuToEqnx = (fnPtrPosVelMuToEqnx)GetFnPtr(hLib, (char*)"PosVelMuToEqnx");
   PosVelToKep = (fnPtrPosVelToKep)GetFnPtr(hLib, (char*)"PosVelToKep");
   PosVelMuToKep = (fnPtrPosVelMuToKep)GetFnPtr(hLib, (char*)"PosVelMuToKep");
   PosVelToUUVW = (fnPtrPosVelToUUVW)GetFnPtr(hLib, (char*)"PosVelToUUVW");
   PosVelToPTW = (fnPtrPosVelToPTW)GetFnPtr(hLib, (char*)"PosVelToPTW");
   SolveKepEqtn = (fnPtrSolveKepEqtn)GetFnPtr(hLib, (char*)"SolveKepEqtn");
   CompTrueAnomaly = (fnPtrCompTrueAnomaly)GetFnPtr(hLib, (char*)"CompTrueAnomaly");
   NToA = (fnPtrNToA)GetFnPtr(hLib, (char*)"NToA");
   AToN = (fnPtrAToN)GetFnPtr(hLib, (char*)"AToN");
   KozaiToBrouwer = (fnPtrKozaiToBrouwer)GetFnPtr(hLib, (char*)"KozaiToBrouwer");
   BrouwerToKozai = (fnPtrBrouwerToKozai)GetFnPtr(hLib, (char*)"BrouwerToKozai");
   KepOscToMean = (fnPtrKepOscToMean)GetFnPtr(hLib, (char*)"KepOscToMean");
   XYZToLLH = (fnPtrXYZToLLH)GetFnPtr(hLib, (char*)"XYZToLLH");
   XYZToLLHTime = (fnPtrXYZToLLHTime)GetFnPtr(hLib, (char*)"XYZToLLHTime");
   LLHToXYZ = (fnPtrLLHToXYZ)GetFnPtr(hLib, (char*)"LLHToXYZ");
   LLHToXYZTime = (fnPtrLLHToXYZTime)GetFnPtr(hLib, (char*)"LLHToXYZTime");
   EFGToECI = (fnPtrEFGToECI)GetFnPtr(hLib, (char*)"EFGToECI");
   EFGToECITime = (fnPtrEFGToECITime)GetFnPtr(hLib, (char*)"EFGToECITime");
   ECIToEFG = (fnPtrECIToEFG)GetFnPtr(hLib, (char*)"ECIToEFG");
   ECIToEFGTime = (fnPtrECIToEFGTime)GetFnPtr(hLib, (char*)"ECIToEFGTime");
   ECRToEFG = (fnPtrECRToEFG)GetFnPtr(hLib, (char*)"ECRToEFG");
   ECRToEFGTime = (fnPtrECRToEFGTime)GetFnPtr(hLib, (char*)"ECRToEFGTime");
   EFGToECR = (fnPtrEFGToECR)GetFnPtr(hLib, (char*)"EFGToECR");
   EFGToECRTime = (fnPtrEFGToECRTime)GetFnPtr(hLib, (char*)"EFGToECRTime");
   EFGPosToLLH = (fnPtrEFGPosToLLH)GetFnPtr(hLib, (char*)"EFGPosToLLH");
   LLHToEFGPos = (fnPtrLLHToEFGPos)GetFnPtr(hLib, (char*)"LLHToEFGPos");
   RotJ2KToDate = (fnPtrRotJ2KToDate)GetFnPtr(hLib, (char*)"RotJ2KToDate");
   RotDateToJ2K = (fnPtrRotDateToJ2K)GetFnPtr(hLib, (char*)"RotDateToJ2K");
   CompSunMoonPos = (fnPtrCompSunMoonPos)GetFnPtr(hLib, (char*)"CompSunMoonPos");
   CompSunPos = (fnPtrCompSunPos)GetFnPtr(hLib, (char*)"CompSunPos");
   CompMoonPos = (fnPtrCompMoonPos)GetFnPtr(hLib, (char*)"CompMoonPos");
   AstroConvFrTo = (fnPtrAstroConvFrTo)GetFnPtr(hLib, (char*)"AstroConvFrTo");
   RADecToLAD = (fnPtrRADecToLAD)GetFnPtr(hLib, (char*)"RADecToLAD");
   AzElToLAD = (fnPtrAzElToLAD)GetFnPtr(hLib, (char*)"AzElToLAD");
   ECIToTopoComps = (fnPtrECIToTopoComps)GetFnPtr(hLib, (char*)"ECIToTopoComps");
   RaDecToAzEl = (fnPtrRaDecToAzEl)GetFnPtr(hLib, (char*)"RaDecToAzEl");
   RaDecToAzElTime = (fnPtrRaDecToAzElTime)GetFnPtr(hLib, (char*)"RaDecToAzElTime");
   AzElToRaDec = (fnPtrAzElToRaDec)GetFnPtr(hLib, (char*)"AzElToRaDec");
   AzElToRaDecTime = (fnPtrAzElToRaDecTime)GetFnPtr(hLib, (char*)"AzElToRaDecTime");
   RAEToECI = (fnPtrRAEToECI)GetFnPtr(hLib, (char*)"RAEToECI");
   GetInitialDrag = (fnPtrGetInitialDrag)GetFnPtr(hLib, (char*)"GetInitialDrag");
   CovMtxPTWToUVW = (fnPtrCovMtxPTWToUVW)GetFnPtr(hLib, (char*)"CovMtxPTWToUVW");
   CovMtxUVWToPTW = (fnPtrCovMtxUVWToPTW)GetFnPtr(hLib, (char*)"CovMtxUVWToPTW");
   EarthObstructionAngles = (fnPtrEarthObstructionAngles)GetFnPtr(hLib, (char*)"EarthObstructionAngles");
   IsPointSunlit = (fnPtrIsPointSunlit)GetFnPtr(hLib, (char*)"IsPointSunlit");
   RotRADecl = (fnPtrRotRADecl)GetFnPtr(hLib, (char*)"RotRADecl");
   RotRADec_DateToEqnx = (fnPtrRotRADec_DateToEqnx)GetFnPtr(hLib, (char*)"RotRADec_DateToEqnx");
   RotRADec_EqnxToDate = (fnPtrRotRADec_EqnxToDate)GetFnPtr(hLib, (char*)"RotRADec_EqnxToDate");
   CovMtxEqnxToUVW = (fnPtrCovMtxEqnxToUVW)GetFnPtr(hLib, (char*)"CovMtxEqnxToUVW");
   CovMtxUVWToEqnx = (fnPtrCovMtxUVWToEqnx)GetFnPtr(hLib, (char*)"CovMtxUVWToEqnx");
   CovMtxECIToUVW = (fnPtrCovMtxECIToUVW)GetFnPtr(hLib, (char*)"CovMtxECIToUVW");
   CovMtxUVWToECI = (fnPtrCovMtxUVWToECI)GetFnPtr(hLib, (char*)"CovMtxUVWToECI");
   CovMtxECIToEFG = (fnPtrCovMtxECIToEFG)GetFnPtr(hLib, (char*)"CovMtxECIToEFG");
   CovMtxEFGToECI = (fnPtrCovMtxEFGToECI)GetFnPtr(hLib, (char*)"CovMtxEFGToECI");
   Mtx6x6ToLTA21 = (fnPtrMtx6x6ToLTA21)GetFnPtr(hLib, (char*)"Mtx6x6ToLTA21");
   LTA21ToMtx6x6 = (fnPtrLTA21ToMtx6x6)GetFnPtr(hLib, (char*)"LTA21ToMtx6x6");
   Mtx9x9ToLTA45 = (fnPtrMtx9x9ToLTA45)GetFnPtr(hLib, (char*)"Mtx9x9ToLTA45");
   LTA45ToMtx9x9 = (fnPtrLTA45ToMtx9x9)GetFnPtr(hLib, (char*)"LTA45ToMtx9x9");
   PropCovFrState = (fnPtrPropCovFrState)GetFnPtr(hLib, (char*)"PropCovFrState");
   CovMtxECIToEqnx = (fnPtrCovMtxECIToEqnx)GetFnPtr(hLib, (char*)"CovMtxECIToEqnx");
   CovMtxEqnxToECI9x9 = (fnPtrCovMtxEqnxToECI9x9)GetFnPtr(hLib, (char*)"CovMtxEqnxToECI9x9");
   CovMtxEqnxToUVW9x9 = (fnPtrCovMtxEqnxToUVW9x9)GetFnPtr(hLib, (char*)"CovMtxEqnxToUVW9x9");
   CovMtxUpdate = (fnPtrCovMtxUpdate)GetFnPtr(hLib, (char*)"CovMtxUpdate");
   AberrationAnnual = (fnPtrAberrationAnnual)GetFnPtr(hLib, (char*)"AberrationAnnual");
   AberrationDiurnal = (fnPtrAberrationDiurnal)GetFnPtr(hLib, (char*)"AberrationDiurnal");
   JplSetParameters = (fnPtrJplSetParameters)GetFnPtr(hLib, (char*)"JplSetParameters");
   JplGetParameters = (fnPtrJplGetParameters)GetFnPtr(hLib, (char*)"JplGetParameters");
   JplReset = (fnPtrJplReset)GetFnPtr(hLib, (char*)"JplReset");
   JplCompSunMoonVec = (fnPtrJplCompSunMoonVec)GetFnPtr(hLib, (char*)"JplCompSunMoonVec");
   JplCompSunMoonPos = (fnPtrJplCompSunMoonPos)GetFnPtr(hLib, (char*)"JplCompSunMoonPos");
   RemoveJpl = (fnPtrRemoveJpl)GetFnPtr(hLib, (char*)"RemoveJpl");
}



// Free AstroFuncDll
void FreeAstroFuncDll()
{
   FreeLib(hLib, AstroFuncDll);
}
// ========================= End of auto generated code ==========================
