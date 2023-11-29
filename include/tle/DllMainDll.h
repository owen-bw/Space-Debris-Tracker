// This wrapper file was generated automatically by the GenDllWrappers program.

#ifndef DLLMAINDLL_H
#define DLLMAINDLL_H

#include "DllUtils.h"

// Provide the path to the dll/so/dylib
#if defined (_WIN32) || defined (__CYGWIN__)
  #define DllMainDll "DllMain.dll"
#elif __APPLE__
  #define DllMainDll "libdllmain.dylib"
#else
  #define DllMainDll "libdllmain.so"
#endif


// Notes: This function has been deprecated since v9.0. 
// Initializes DllMain program (host of Astro Standards libraries) for use in any Astro Standards applications
// returns A handle to the global data set. You will pass this handle to other initialization functions within other DLLs in the API.
typedef __int64 (STDCALL *fnPtrDllMainInit)();


// Returns information about the DllMain DLL. 
// The returned string provides information about the version number, build date, and the platform. 
// infoStr            A string to hold the information about DllMain.dll. (out-Character[128])
typedef void (STDCALL *fnPtrDllMainGetInfo)(char infoStr[128]);


// Loads DllMain-related parameters (AS_MOIC) from a text file
// dllMainFile        The name of the input file. (in-Character[512])
// returns Returns zero indicating the input file has been loaded successfully. Other values indicate an error.
typedef int (STDCALL *fnPtrDllMainLoadFile)(char dllMainFile[512]);


// Opens a log file and enables the writing of diagnostic information into it. 
// All of the DLLs in the library will write diagnostic information into the log file once this function has been called.
// If the file specified by logFileName already exists, its contents are erased.
// 
// Enabling logging can potentially result in large amounts of diagnostic information being generated, which can lead to large amounts of storage being consumed as well as performance decreases. For this reason, it is recommended that this function only be used for debugging purposes.
// fileName           The name of the log file to use. (in-Character[512])
// returns 0 if the file was opened successfully. Other values indicate an error.
typedef int (STDCALL *fnPtrOpenLogFile)(char fileName[512]);


// Closes the currently open log file and reset the last logged error message to null. 
// Remember to close the log file before exiting the program.
typedef void (STDCALL *fnPtrCloseLogFile)();


// Writes a message into the log file.
// Make sure the log file is open by calling OpenLogFile before using this function.
// 
// The message is limited to 128 characters. If the message is longer than this, it will be truncated.
// msgStr             A message to be written into the log file. (in-Character[128])
typedef void (STDCALL *fnPtrLogMessage)(char msgStr[128]);


// Returns a character string describing the last error that occurred. 
// As a common practice, this function is called to retrieve the error message when an error occurs.
// 
// This function works with or without an opened log file.
// 
// If you call this function before you have called DllMainInit(), the function will return an invalid string. This could result in undefined behavior.
// lastErrMsg         A string that stores the last logged error message. The message will be placed in the string you pass to this function. (out-Character[128])
typedef void (STDCALL *fnPtrGetLastErrMsg)(char lastErrMsg[128]);


// Returns a character string describing the last informational message that was recorded. 
// This function is usually called right after space objects (TLEs, VCMs, sensors, observations, etc.) in an input text file were loaded. It gives information about how many records were successfully loaded, how many were bad, and how many were duplicated.
// 
// This function works with or without an opened log file.
// 
// If you call this function before you have called DllMainInit(), the function will return an invalid string. This could result in undefined behavior.
// This function provides a quick way to check whether all of the prerequisite DLLs have been loaded and initialized correctly. Improper initialization of the Standardized Astrodynamic Algorithms DLLs is one of the most common causes of program crashes.
// lastInfoMsg        A string that stores the last logged informational message. The message will be placed in the string you pass to this function. (out-Character[128])
typedef void (STDCALL *fnPtrGetLastInfoMsg)(char lastInfoMsg[128]);


// Notes: This function has been deprecated since v9.0. 
// Returns a list of names of the Standardized Astrodynamic Algorithms DLLs that were initialized successfully.
// initDllNames       A string that stores names of the DLLs that were initialized successfully. (out-Character[512])
typedef void (STDCALL *fnPtrGetInitDllNames)(char initDllNames[512]);


// Tests different input/output data types that are supported by the Astrodynamic Standards library.
// cIn                an input character (in-Character)
// cOut               an output character - should return the same value as the input cIn (out-Character)
// intIn              an input 32-bit integer (in-Integer)
// intOut             an output 32-bit integer - should return the same value as the input intIn (out-Integer)
// longIn             an input 64-bit integer (in-Long)
// longOut            an output 64-bit integer - should return the same value as the input longIn (out-Long)
// realIn             an input 64-bit real (in-Double)
// realOut            an output 64-bit real - should return the same value as the input realIn (out-Double)
// strIn              input string (in-Character[512])
// strOut             output string - should return the same value as the input strIn (out-Character[512])
// int1DIn            an input array of 32-bit integers (in-Integer[3])
// int1DOut           an output array of 32-bit integers - should return the same values as the input int1DIn (out-Integer[3])
// long1DIn           an input array of 64-bit integers (in-Long[3])
// long1DOut          an output array of 64-bit integers - should return the same values as the input long1DIn (out-Long[3])
// real1DIn           an input array of 64-bit reals (in-Double[3])
// real1DOut          an output array of 64-bit reals - should return the same values as the input real1DIn (out-Double[3])
// int2DIn            an input 2D-array of 32-bit integers (2 rows, 3 columns) - for column-major order language, reverse the order (in-Integer[2, 3])
// int2DOut           an output 2D-array of 32-bit integers - should return the same values as the input int2DIn (out-Integer[2, 3])
// long2DIn           an input 2D-array of 64-bit integers (2 rows, 3 columns) - for column-major order language, reverse the order (in-Long[2, 3])
// long2DOut          an output 2D-array of 64-bit integers - should return the same values as the input long2DIn (out-Long[2, 3])
// real2DIn           an input 2D-array of 64-bit reals (2 rows, 3 columns) - for column-major order language, reverse the order (in-Double[2, 3])
// real2DOut          an output 2D-array of 64-bit reals - should return the same values as the input real2DIn (out-Double[2, 3])
typedef void (STDCALL *fnPtrTestInterface)(char cIn, char* cOut, int intIn, int* intOut, __int64 longIn, __int64* longOut, double realIn, double* realOut, char strIn[512], char strOut[512], int int1DIn[3], int int1DOut[3], __int64 long1DIn[3], __int64 long1DOut[3], double real1DIn[3], double real1DOut[3], int int2DIn[2][3], int int2DOut[2][3], __int64 long2DIn[2][3], __int64 long2DOut[2][3], double real2DIn[2][3], double real2DOut[2][3]);


// Tests different input/output data types that are supported by the Astrodynamic Standards library.
// cInOut             Output should return 'Z' (inout-Character)
// intInOut           Output should return Input + 1 (inout-Integer)
// longInOut          Output should return Input + 2 (inout-Long)
// realInOut          Output should return Input + 42.123456 (inout-Double)
// strInOut           Output should return "It doesn't matter what your string was." (inout-Character[512])
// int1DInOut         Output should return Input + 1 (inout-Integer[3])
// long1DInOut        Output should return Input + 1234567890123456789 (inout-Long[3])
// real1DInOut        Output should return Input + 42.0 (inout-Double[3])
// int2DInOut         Output should return Input + 1 (inout-Integer[2, 3])
// long2DInOut        Output should return Input + 6 (inout-Long[2, 3])
// real2DInOut        Output should return Input + 7.6 (inout-Double[2, 3])
typedef void (STDCALL *fnPtrTestInterface2)(char* cInOut, int* intInOut, __int64* longInOut, double* realInOut, char strInOut[512], int int1DInOut[3], __int64 long1DInOut[3], double real1DInOut[3], int int2DInOut[2][3], __int64 long2DInOut[2][3], double real2DInOut[2][3]);


// Tests input and output arrays with unknown length that are supported by the Astrodynamic Standards library.
// Unk1DIn            Unknown dimension should be length (3) (in-Integer[*])
// Unk1DOut           Unknown dimension should be length (3), Unk1DOut should return same as Unk1DIn * 4 (out-Integer[*])
// Unk2DIn            Unknown dimension should be length (2) (in-Integer[*, 3])
// Unk2DOut           Unknown dimension should be length (2), Unk2DOut should return same as Unk2DIn * 5 (out-Integer[*, 3])
typedef void (STDCALL *fnPtrTestInterface3)(int Unk1DIn[], int Unk1DOut[], int Unk2DIn[][3], int Unk2DOut[][3]);


// Returns data parsed from user's AS_MOIC-typed input card - up to 128 fields are allowed.
// arrSize            size of the xa_moc array - actual number of fields the user enters in an "AS_MOIC" input card (in-Integer)
// xa_moic            The returning xa_moc array (out-Double[*])
typedef void (STDCALL *fnPtrGetMOICData)(int arrSize, double xa_moic[]);


// Sets ELSET key mode
// This mode can also be turned on if the user loads an input text file that includes this line - "AS_DMA_ON" -
// and is currently calling any of these methods: DllMainLoadFile(), TleLoadFile(), SpVecLoadFile(), or VcmLoadFile()
// elset_keyMode      Desired elset key mode (see ELSET_KEYMODE_? for available modes) (in-Integer)
// returns 0 if the set is successful, non-0 if there is an error.
typedef int (STDCALL *fnPtrSetElsetKeyMode)(int elset_keyMode);


// Gets current ELSET key mode
// returns Current elset key mode (see ELSET_KEYMODE_? for available modes)
typedef int (STDCALL *fnPtrGetElsetKeyMode)();


// Sets key mode for ALL (elsets/obs/sensors). This takes precedence over individual elset/obs/sensor key mode
// This mode can also be turned on if the user loads an input text file that includes this line - "AS_DMA_ALL_ON"
// all_keyMode        Desired elset key mode (see ALL_KEYMODE_? for available modes) (in-Integer)
// returns 0 if the set is successful, non-0 if there is an error.
typedef int (STDCALL *fnPtrSetAllKeyMode)(int all_keyMode);


// Gets current ALL (elsets/obs/sensors) key mode
// returns Current elset key mode (see ALL_KEYMODE_? for available modes)
typedef int (STDCALL *fnPtrGetAllKeyMode)();


// Resets ALL (elsets/obs/sensors) key mode to its default value which then allows individual elsets/obs/sensors to use their own key mode settings
typedef void (STDCALL *fnPtrResetAllKeyMode)();
  
  // log message string length
  #define LOGMSGLEN   128    
  
  // DHN 06Feb12 - Increase file path length to 512 characters from 128 characters to handle longer file path
  #define FILEPATHLEN   512 
  
  // DHN 10Feb12 - Uniformally using 512 characters to passing/receiving string in all Get/Set Field functions
  #define GETSETSTRLEN   512 
  
  #define INFOSTRLEN   128 
  
  // DHN 10Feb12 - All input card types' (elsets, ob, sensors, ...) can now have maximum of 512 characters
  #define INPUTCARDLEN   512 
  
  // Different orbital element types 
  static const int  
     ELTTYPE_TLE_SGP   = 1,    // Element type - SGP Tle type 0
     ELTTYPE_TLE_SGP4  = 2,    // Element type - SGP4 Tle type 2
     ELTTYPE_TLE_SP    = 3,    // Element type - SP Tle type 6
     ELTTYPE_SPVEC_B1P = 4,    // Element type - SP Vector
     ELTTYPE_VCM       = 5,    // Element type - VCM
     ELTTYPE_EXTEPH    = 6,    // Element type - External ephemeris
     ELTTYPE_TLE_XP    = 7;    // Element type - SGP Tle type 4 - XP
  
  //*******************************************************************************
  
  // Propagation types
  static const int  
     PROPTYPE_GP  = 1,       // GP/SGP4/SGP4-XP propagator
     PROPTYPE_SP  = 2,       // SP propagator
     PROPTYPE_X   = 3,       // External ephemeris
     PROPTYPE_UK  = 4;       // Unknown
  //*******************************************************************************
  
  // Add sat error 
  static const int  
     BADSATKEY = -1,      // Bad satellite key
     DUPSATKEY =  0;      // Duplicate satellite key
  
  //*******************************************************************************
  
  // satellite/observation/sensor key possible errors
  static const int  
     BADKEY = -1,      // Bad (satellite/observation/sensor) key
     DUPKEY =  0;      // Duplicate (satellite/observation/sensor) key
  
  //*******************************************************************************
  
  // Options used in GetLoaded()   
  static const int  
     IDX_ORDER_ASC   = 0,    // ascending order
     IDX_ORDER_DES   = 1,    // descending order
     IDX_ORDER_READ  = 2,    // order as read
     IDX_ORDER_QUICK = 9;    // tree traversal order
  
  //*******************************************************************************
  
  // Different key mode options for all elset-satKey/obs-obsKey/sensor-senKey
  static const int  
     ALL_KEYMODE_NODUP  = 0,    // Default - duplicate elsets/observations/sensors can not be loaded in their binary trees                           
     ALL_KEYMODE_DMA    = 1;    // Allow duplicate elsets/obs/sensor to be loaded and have direct memory access (DMA - no duplication check and no binary tree)
     
  //*******************************************************************************
  
     
  // Different key mode options for elset satKey
  static const int  
     ELSET_KEYMODE_NODUP  = 0,    // Default - duplicate elsets can not be loaded in binary tree                           
     ELSET_KEYMODE_DMA    = 1;    // Allow duplicate elsets to be loaded and have direct memory access (DMA - no duplication check and no binary tree)
     
  //*******************************************************************************
     
  static const int  
     TIME_IS_MSE = 1,     // Input time is in minutes since epoch 
     TIME_IS_TAI = 2,     // Input time is in days since 1950 TAI
     TIME_IS_UTC = 3;     // Input time is in days since 1950 UTC
     
  //*******************************************************************************   
     
// DllMainDll's function pointers declaration
extern fnPtrDllMainInit                    DllMainInit;
extern fnPtrDllMainGetInfo                 DllMainGetInfo;
extern fnPtrDllMainLoadFile                DllMainLoadFile;
extern fnPtrOpenLogFile                    OpenLogFile;
extern fnPtrCloseLogFile                   CloseLogFile;
extern fnPtrLogMessage                     LogMessage;
extern fnPtrGetLastErrMsg                  GetLastErrMsg;
extern fnPtrGetLastInfoMsg                 GetLastInfoMsg;
extern fnPtrGetInitDllNames                GetInitDllNames;
extern fnPtrTestInterface                  TestInterface;
extern fnPtrTestInterface2                 TestInterface2;
extern fnPtrTestInterface3                 TestInterface3;
extern fnPtrGetMOICData                    GetMOICData;
extern fnPtrSetElsetKeyMode                SetElsetKeyMode;
extern fnPtrGetElsetKeyMode                GetElsetKeyMode;
extern fnPtrSetAllKeyMode                  SetAllKeyMode;
extern fnPtrGetAllKeyMode                  GetAllKeyMode;
extern fnPtrResetAllKeyMode                ResetAllKeyMode;



void LoadDllMainDll();
void FreeDllMainDll();




#endif
// ========================= End of auto generated code ==========================
