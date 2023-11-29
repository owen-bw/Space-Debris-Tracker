// This wrapper file was generated automatically by the GenDllWrappers program.

#ifndef ASTROFUNCDLL_H
#define ASTROFUNCDLL_H

#include "DllUtils.h"

// Provide the path to the dll/so/dylib
#if defined (_WIN32) || defined (__CYGWIN__)
  #define AstroFuncDll "AstroFunc.dll"
#elif __APPLE__
  #define AstroFuncDll "libastrofunc.dylib"
#else
  #define AstroFuncDll "libastrofunc.so"
#endif


// Notes: This function has been deprecated since v9.0. 
// Initializes AstroFunc DLL for use in the program.
// If this function returns an error, it is recommended that you stop the program immediately.
// 
// An error will occur if you forget to load and initialize all the prerequisite DLLs, as listed in the DLL Prerequisites section of the accompanying documentation, before using this DLL.
// apAddr             The handle that was returned from DllMainInit(). See the documentation for DllMain.dll for details. (in-Long)
// returns 0 if AstroFunc.dll is initialized successfully, non-0 if there is an error.
typedef int (STDCALL *fnPtrAstroFuncInit)(__int64 apAddr);


// Retrieves information about the current version of AstroFunc.dll. The information is placed in the string parameter you pass in.
// The returned string provides information about the version number, build date, and platform.
// infoStr            A string to hold the information about AstroFunc.dll. (out-Character[128])
typedef void (STDCALL *fnPtrAstroFuncGetInfo)(char infoStr[128]);


// Converts a set of Keplerian elements to a set of equinoctial elements. 
// xa_kep             The set of Keplerian elements to be converted. see XA_KEP_? (in-Double[6])
// xa_eqnx            The resulting set of equinoctial elements. see XA_EQNX_? (out-Double[6])
typedef void (STDCALL *fnPtrKepToEqnx)(double xa_kep[6], double xa_eqnx[6]);


// Converts a set of osculating Keplerian elements to osculating position and velocity vectors.
// xa_kep             The set of Keplerian elements to be converted. see XA_KEP_? (in-Double[6])
// pos                The resulting position vector. (out-Double[3])
// vel                The resulting velocity vector. (out-Double[3])
typedef void (STDCALL *fnPtrKepToPosVel)(double xa_kep[6], double pos[3], double vel[3]);


// Converts a set of Keplerian elements to Ubar, Vbar, and Wbar vectors.
// xa_kep             The set of Keplerian elements to be converted. see XA_KEP_? (in-Double[6])
// uBar               The resulting ubar vector. (out-Double[3])
// vBar               The resulting vbar vector. (out-Double[3])
// wBar               The resulting wbar vector. (out-Double[3])
typedef void (STDCALL *fnPtrKepToUVW)(double xa_kep[6], double uBar[3], double vBar[3], double wBar[3]);


// Converts a set of classical elements to a set of equinoctial elements. 
// xa_cls             The set of classical elements to be converted. see XA_CLS_? (in-Double[6])
// xa_eqnx            The resulting set of equinoctial elements. see XA_EQNX_? (out-Double[6])
typedef void (STDCALL *fnPtrClassToEqnx)(double xa_cls[6], double xa_eqnx[6]);


// Converts a set of equinoctial elements to a set of classical elements.
// xa_eqnx            The set of equinoctial elements to be converted. see XA_EQNX_? (in-Double[6])
// xa_cls             The resulting set of classical elements. see XA_CLS_? (out-Double[6])
typedef void (STDCALL *fnPtrEqnxToClass)(double xa_eqnx[6], double xa_cls[6]);


// Converts a set of equinoctial elements to a set of Keplerian elements. 
// xa_eqnx            The set of equinoctial elements to be converted. see XA_EQNX_? (in-Double[6])
// xa_kep             The resulting set of Keplerian elements. see XA_KEP_? (out-Double[6])
typedef void (STDCALL *fnPtrEqnxToKep)(double xa_eqnx[6], double xa_kep[6]);


// Converts a set of equinoctial elements to position and velocity vectors.
// xa_eqnx            The set of equinoctial elements to be converted. see XA_EQNX_? (in-Double[6])
// pos                The resulting position vector. (out-Double[3])
// vel                The resulting velocity vector. (out-Double[3])
typedef void (STDCALL *fnPtrEqnxToPosVel)(double xa_eqnx[6], double pos[3], double vel[3]);


// Converts position and velocity vectors to a set of equinoctial elements.
// pos                The position vector to be converted. (in-Double[3])
// vel                The velocity vector to be converted. (in-Double[3])
// xa_eqnx            The resulting set of equinoctial elements. see XA_EQNX_? (out-Double[6])
typedef void (STDCALL *fnPtrPosVelToEqnx)(double pos[3], double vel[3], double xa_eqnx[6]);


// Converts position and velocity vectors to a set of equinoctial elements with the given mu value. 
// This function is used when working with the SP propagator to get a more accurate set of equinoctial elements.
// pos                The position vector to be converted. (in-Double[3])
// vel                The velocity vector to be converted. (in-Double[3])
// mu                 The value of mu. (in-Double)
// xa_eqnx            The resulting set of equinoctial elements. see XA_EQNX_? (out-Double[6])
typedef void (STDCALL *fnPtrPosVelMuToEqnx)(double pos[3], double vel[3], double mu, double xa_eqnx[6]);


// Converts osculating position and velocity vectors to a set of osculating Keplerian elements.
// pos                The position vector to be converted. (in-Double[3])
// vel                The velocity vector to be converted. (in-Double[3])
// xa_kep             The resulting set of Keplerian elements. see XA_KEP_? (out-Double[6])
typedef void (STDCALL *fnPtrPosVelToKep)(double pos[3], double vel[3], double xa_kep[6]);


// Converts osculating position and velocity vectors to a set of osculating Keplerian elements with the given value of mu.
// This function is used when working with the SP propagator to get a more accurate set of Keplerian elements.
// pos                The position vector to be converted. (in-Double[3])
// vel                The velocity vector to be converted. (in-Double[3])
// mu                 The value of mu. (in-Double)
// xa_kep             The resulting set of Keplerian elements. see XA_KEP_? (out-Double[6])
typedef void (STDCALL *fnPtrPosVelMuToKep)(double pos[3], double vel[3], double mu, double xa_kep[6]);


// Converts position and velocity vectors to U, V, W vectors. See the remarks section for details.
// The resulting vectors have the following meanings.
// U vector: along radial direction
// V vector: W x U
// W vector: pos x vel
// pos                The position vector to be converted. (in-Double[3])
// vel                The velocity vector to be converted. (in-Double[3])
// uvec               The resulting U vector. (out-Double[3])
// vVec               The resulting V vector. (out-Double[3])
// wVec               The resulting W vector. (out-Double[3])
typedef void (STDCALL *fnPtrPosVelToUUVW)(double pos[3], double vel[3], double uvec[3], double vVec[3], double wVec[3]);


// Converts position and velocity vectors to U, V, W vectors. See the remarks section for details.
// The resulting vectors have the following meanings.
// U vector: V x W
// V vector: along velocity direction
// W vector: pos x vel
// pos                The position vector. (in-Double[3])
// vel                The velocity vector. (in-Double[3])
// uvec               The resulting U vector. (out-Double[3])
// vVec               The resulting V vector. (out-Double[3])
// wVec               The resulting W vector. (out-Double[3])
typedef void (STDCALL *fnPtrPosVelToPTW)(double pos[3], double vel[3], double uvec[3], double vVec[3], double wVec[3]);


// Solves Kepler's equation (M = E - e sin(E)) for the eccentric anomaly, E, by iteration.
// xa_kep             The set of Keplerian elements for which to solve the equation. see XA_KEP_? (in-Double[6])
// returns The eccentric anomaly.
typedef double (STDCALL *fnPtrSolveKepEqtn)(double xa_kep[6]);


// Computes true anomaly from a set of Keplerian elements.
// xa_kep             The set of Keplerian elements for which to compute true anomaly. see XA_KEP_? (in-Double[6])
// returns The true anomaly in degrees.
typedef double (STDCALL *fnPtrCompTrueAnomaly)(double xa_kep[6]);


// Converts mean motion N to semi-major axis A.
// n                  Mean motion N (revs/day). (in-Double)
// returns The semi-major axis A (km).
typedef double (STDCALL *fnPtrNToA)(double n);


// Converts semi-major axis A to mean motion N.
// a                  Semi-major axis A (km). (in-Double)
// returns The mean motion N (revs/day).
typedef double (STDCALL *fnPtrAToN)(double a);


// Converts Kozai mean motion to Brouwer mean motion.
// SGP TLE's use Kozai mean motion while SGP4/SGP4-XP TLE's use Brouwer mean motion.
// eccen              eccentricity (in-Double)
// incli              inclination (degrees) (in-Double)
// nKozai             Kozai mean motion (revs/day). (in-Double)
// returns Brouwer mean motion (revs/day).
typedef double (STDCALL *fnPtrKozaiToBrouwer)(double eccen, double incli, double nKozai);


// Converts Brouwer mean motion to Kozai mean motion.
// SGP TLE's use Kozai mean motion while SGP4/SGP4-XP TLE's use Brouwer mean motion.
// eccen              eccentricity (in-Double)
// incli              inclination (degrees) (in-Double)
// nBrouwer           Brouwer mean motion (revs/day). (in-Double)
// returns Kozai mean motion (revs/day).
typedef double (STDCALL *fnPtrBrouwerToKozai)(double eccen, double incli, double nBrouwer);


// Converts a set of osculating Keplerian elements to a set of mean Keplerian elements using method 9 algorithm.
// xa_OscKep          The set of osculating Keplerian elements to be converted. see XA_KEP_? (in-Double[6])
// xa_MeanKep         The resulting set of mean Keplerian elements. see XA_KEP_? (out-Double[6])
typedef void (STDCALL *fnPtrKepOscToMean)(double xa_OscKep[6], double xa_MeanKep[6]);


// Converts an ECI position vector XYZ to geodetic latitude, longitude, and height.
// thetaG             ThetaG - Greenwich mean sidereal time (rad). (in-Double)
// metricPos          The ECI (TEME of Date) position vector (km) to be converted. (in-Double[3])
// metricLLH          The resulting geodetic north latitude (degree), east longitude(degree), and height (km). (out-Double[3])
typedef void (STDCALL *fnPtrXYZToLLH)(double thetaG, double metricPos[3], double metricLLH[3]);


// Converts an ECI position vector XYZ to geodetic latitude, longitude, and height at the specified time.
// ds50UTC            Input time in days since 1950 UTC (in-Double)
// metricPos          The ECI (TEME of Date) position vector (km) to be converted. (in-Double[3])
// metricLLH          The resulting geodetic north latitude (degree), east longitude(degree), and height (km). (out-Double[3])
typedef void (STDCALL *fnPtrXYZToLLHTime)(double ds50UTC, double metricPos[3], double metricLLH[3]);


// Converts geodetic latitude, longitude, and height to an ECI position vector XYZ.
// thetaG             Theta - Greenwich mean sidereal time (rad). (in-Double)
// metricLLH          An array containing geodetic north latitude (degree), east longitude (degree), and height (km) to be converted. (in-Double[3])
// metricXYZ          The resulting ECI (TEME of Date) position vector (km). (out-Double[3])
typedef void (STDCALL *fnPtrLLHToXYZ)(double thetaG, double metricLLH[3], double metricXYZ[3]);


// Converts geodetic latitude, longitude, and height to an ECI position vector XYZ at the specified time.
// ds50UTC            Input time in days since 1950 UTC (in-Double)
// metricLLH          An array containing geodetic north latitude (degree), east longitude (degree), and height (km) to be converted. (in-Double[3])
// metricXYZ          The resulting ECI (TEME of Date) position vector (km). (out-Double[3])
typedef void (STDCALL *fnPtrLLHToXYZTime)(double ds50UTC, double metricLLH[3], double metricXYZ[3]);


// Converts EFG position and velocity vectors to ECI position and velocity vectors.
// thetaG             Theta - Greenwich mean sidereal time (rad). (in-Double)
// posEFG             The EFG position vector (km) to be converted. (in-Double[3])
// velEFG             The EFG velocity vector (km/s) to be converted. (in-Double[3])
// posECI             The resulting ECI (TEME of Date) position vector (km). (out-Double[3])
// velECI             The resulting ECI (TEME of Date) velocity vector (km/s). (out-Double[3])
typedef void (STDCALL *fnPtrEFGToECI)(double thetaG, double posEFG[3], double velEFG[3], double posECI[3], double velECI[3]);


// Converts EFG position and velocity vectors to ECI position and velocity vectors at the specified time.
// ds50UTC            Input time in days since 1950 UTC (in-Double)
// posEFG             The EFG position vector (km) to be converted. (in-Double[3])
// velEFG             The EFG velocity vector (km/s) to be converted. (in-Double[3])
// posECI             The resulting ECI (TEME of Date) position vector (km). (out-Double[3])
// velECI             The resulting ECI (TEME of Date) velocity vector (km/s). (out-Double[3])
typedef void (STDCALL *fnPtrEFGToECITime)(double ds50UTC, double posEFG[3], double velEFG[3], double posECI[3], double velECI[3]);


// Converts ECI position and velocity vectors to EFG position and velocity vectors.
// thetaG             Theta - Greenwich mean sidereal time (rad). (in-Double)
// posECI             The ECI (TEME of Date) position vector (km) to be converted. (in-Double[3])
// velECI             The ECI (TEME of Date) velocity vector (km/s) to be converted. (in-Double[3])
// posEFG             The resulting EFG position vector (km). (out-Double[3])
// velEFG             The resulting EFG velocity vector (km/s). (out-Double[3])
typedef void (STDCALL *fnPtrECIToEFG)(double thetaG, double posECI[3], double velECI[3], double posEFG[3], double velEFG[3]);


// Converts ECI position and velocity vectors to EFG position and velocity vectors at the specified time.
// ds50UTC            Input time in days since 1950 UTC (in-Double)
// posECI             The ECI (TEME of Date) position vector (km) to be converted. (in-Double[3])
// velECI             The ECI (TEME of Date) velocity vector (km/s) to be converted. (in-Double[3])
// posEFG             The resulting EFG position vector (km). (out-Double[3])
// velEFG             The resulting EFG velocity vector (km/s). (out-Double[3])
typedef void (STDCALL *fnPtrECIToEFGTime)(double ds50UTC, double posECI[3], double velECI[3], double posEFG[3], double velEFG[3]);


// Converts ECR position and velocity vectors to EFG position and velocity vectors.
// polarX             Polar motion X (arc-sec). (in-Double)
// polarY             Polar motion Y (arc-sec). (in-Double)
// posECR             The ECR position vector (km) to be converted. (in-Double[3])
// velECR             The ECR velocity vector (km/s) to be converted. (in-Double[3])
// posEFG             The resulting EFG position vector (km). (out-Double[3])
// velEFG             The resulting EFG velocity vector (km/s). (out-Double[3])
typedef void (STDCALL *fnPtrECRToEFG)(double polarX, double polarY, double posECR[3], double velECR[3], double posEFG[3], double velEFG[3]);


// Converts ECR position and velocity vectors to EFG position and velocity vectors at the specified time.
// ds50UTC            Input time in days since 1950 UTC. (in-Double)
// posECR             The ECR position vector (km) to be converted. (in-Double[3])
// velECR             The ECR velocity vector (km/s) to be converted. (in-Double[3])
// posEFG             The resulting EFG position vector (km) (set to zeros if timing constants not loaded). (out-Double[3])
// velEFG             The resulting EFG velocity vector (km/s) (set to zeros if timing constants not loaded). (out-Double[3])
typedef void (STDCALL *fnPtrECRToEFGTime)(double ds50UTC, double posECR[3], double velECR[3], double posEFG[3], double velEFG[3]);


// Converts EFG position and velocity vectors to ECR position and velocity vectors.
// polarX             Polar motion X (arc-sec). (in-Double)
// polarY             Polar motion Y (arc-sec). (in-Double)
// posEFG             The EFG position vector (km) to be converted. (in-Double[3])
// velEFG             The EFG velocity vector (km/s) to be converted. (in-Double[3])
// posECR             The resulting ECR position vector (km). (out-Double[3])
// velECR             The resulting ECR velocity vector (km/s). (out-Double[3])
typedef void (STDCALL *fnPtrEFGToECR)(double polarX, double polarY, double posEFG[3], double velEFG[3], double posECR[3], double velECR[3]);


// Converts EFG position and velocity vectors to ECR position and velocity vectors at the specified time.
// ds50UTC            Input time in days since 1950 UTC (in-Double)
// posEFG             The EFG position vector (km) to be converted. (in-Double[3])
// velEFG             The EFG velocity vector (km/s) to be converted. (in-Double[3])
// posECR             The resulting ECR position vector (km) (set to zeros if timing constants not loaded). (out-Double[3])
// velECR             The resulting ECR velocity vector (km/s) (set to zeros if timing constants not loaded). (out-Double[3])
typedef void (STDCALL *fnPtrEFGToECRTime)(double ds50UTC, double posEFG[3], double velEFG[3], double posECR[3], double velECR[3]);


// Converts an EFG position vector to geodetic latitude, longitude, and height.
// posEFG             The EFG position vector (km) to be converted. (in-Double[3])
// metricLLH          The resulting geodetic north latitude (degree), east longitude (degree), and height (km). (out-Double[3])
typedef void (STDCALL *fnPtrEFGPosToLLH)(double posEFG[3], double metricLLH[3]);


// Converts geodetic latitude, longitude, and height to an EFG position vector.
// metricLLH          An Array containing the geodetic north latitude (degree), east longitude (degree), and height (km) to be converted. (in-Double[3])
// posEFG             The resulting EFG position vector (km). (out-Double[3])
typedef void (STDCALL *fnPtrLLHToEFGPos)(double metricLLH[3], double posEFG[3]);


// Rotates position and velocity vectors from J2000 to coordinates of the specified date, expressed in ds50TAI.
// spectr             Specifies whether to run in SPECTR compatibility mode. A value of 1 means Yes. (in-Integer)
// nutationTerms      Nutation terms (4-106, 4:least accurate, 106:most acurate). (in-Integer)
// ds50TAI            The date to rotate to coordinates of, expressed in days since 1950, TAI. (in-Double)
// posJ2K             The position vector from J2000. (in-Double[3])
// velJ2K             The velocity vector from J2000. (in-Double[3])
// posDate            The resulting position vector in coordinates of date, ds50TAI. (out-Double[3])
// velDate            The resulting velocity vector in coordinates of date, ds50TAI. (out-Double[3])
typedef void (STDCALL *fnPtrRotJ2KToDate)(int spectr, int nutationTerms, double ds50TAI, double posJ2K[3], double velJ2K[3], double posDate[3], double velDate[3]);


// Rotates position and velocity vectors from coordinates of date to J2000.
// spectr             Specifies whether to run in SPECTR compatibility mode. A value of 1 means Yes. (in-Integer)
// nutationTerms      Nutation terms (4-106, 4:least accurate, 106:most acurate). (in-Integer)
// ds50TAI            Time in days since 1950, TAI for which the coordinates of position and velocity vectors are currently expressed. (in-Double)
// posDate            The position vector from coordinates of Date. (in-Double[3])
// velDate            The velocity vector from coordinates of Date. (in-Double[3])
// posJ2K             The resulting position vector in coordinates of J2000. (out-Double[3])
// velJ2K             The resulting velocity vector in coordinates of J2000. (out-Double[3])
typedef void (STDCALL *fnPtrRotDateToJ2K)(int spectr, int nutationTerms, double ds50TAI, double posDate[3], double velDate[3], double posJ2K[3], double velJ2K[3]);


// Computes the Sun and Moon position at the specified time.
// ds50ET             The number of days since 1950, ET for which to compute the sun and moon position. (in-Double)
// uvecSun            The resulting sun position unit vector. (out-Double[3])
// sunVecMag          The resulting magnitude of the sun position vector (km). (out-Double)
// uvecMoon           The resulting moon position unit vector. (out-Double[3])
// moonVecMag         The resulting magnitude of the moon position vector (km). (out-Double)
typedef void (STDCALL *fnPtrCompSunMoonPos)(double ds50ET, double uvecSun[3], double* sunVecMag, double uvecMoon[3], double* moonVecMag);


// Computes the Sun position at the specified time.
// ds50ET             The number of days since 1950, ET for which to compute the sun position. (in-Double)
// uvecSun            The resulting sun position unit vector. (out-Double[3])
// sunVecMag          The resulting magnitude of the sun position vector (km). (out-Double)
typedef void (STDCALL *fnPtrCompSunPos)(double ds50ET, double uvecSun[3], double* sunVecMag);


// Computes the Moon position at the specified time.
// ds50ET             The number of days since 1950, ET for which to compute the moon position. (in-Double)
// uvecMoon           The resulting moon position unit vector. (out-Double[3])
// moonVecMag         The resulting magnitude of the moon position vector (km). (out-Double)
typedef void (STDCALL *fnPtrCompMoonPos)(double ds50ET, double uvecMoon[3], double* moonVecMag);


// This function is intended for future use.  No information is currently available.
// This function is intended for future use.  No information is currently available.
// xf_Conv            Index of the conversion function (in-Integer)
// frArr              The input array (in-Double[128])
// toArr              The resulting array (out-Double[128])
typedef void (STDCALL *fnPtrAstroConvFrTo)(int xf_Conv, double frArr[128], double toArr[128]);


// Converts right ascension and declination to vector triad LAD in topocentric equatorial coordinate system.
// RA                 Right ascension (deg). (in-Double)
// dec                Declination (deg). (in-Double)
// L                  The resulting unit vector from the station to the satellite (referred to the equatorial coordinate system axis). (out-Double[3])
// A_Tilde            The resulting unit vector perpendicular to the hour circle passing through the satellite, in the direction of increasing RA. (out-Double[3])
// D_Tilde            The resulting unit vector perpendicular to L and is directed toward the north, in the plane of the hour circle. (out-Double[3])
typedef void (STDCALL *fnPtrRADecToLAD)(double RA, double dec, double L[3], double A_Tilde[3], double D_Tilde[3]);


// Converts azimuth and elevation to vector triad LAD in topocentric horizontal coordinate system.
// az                 Input azimuth (deg). (in-Double)
// el                 Input elevation angle (deg). (in-Double)
// Lh                 The resulting unit vector from the station to the satellite (referred to the horizon coordinate system axis). (out-Double[3])
// Ah                 The resulting unit vector perpendicular to the hour circle passing through the satellite, in the direction of increasing Az. (out-Double[3])
// Dh                 The resulting unit vector perpendicular to L and is directed toward the zenith, in the plane of the hour circle. (out-Double[3])
typedef void (STDCALL *fnPtrAzElToLAD)(double az, double el, double Lh[3], double Ah[3], double Dh[3]);


// Converts satellite ECI position/velocity vectors and sensor location to topocentric components.
// The xa_topo array has the following structure:
// [0]: Resulting right ascension (RA) (deg)
// [1]: Declination (deg)
// [2]: Azimuth (deg)
// [3]: Elevation (deg)
// [4]: Range (km)
// [5]: RAdot (first derivative of right ascension) (deg/s)
// [6]: DecDot (first derivative of declination) (deg/s)
// [7]: AzDot (first derivative of azimuth) (deg/s)
// [8]: ElDot (first derivative of elevation) (deg/s)
// [9]: RangeDot (first derivative of range) (km/s)   
// theta              Theta - local sidereal time(rad). (in-Double)
// lat                Station's astronomical latitude (deg). (+N) (-S) (in-Double)
// senPos             Sensor position in ECI (km). (in-Double[3])
// satPos             Satellite position in ECI (km). (in-Double[3])
// satVel             Satellite velocity in ECI (km/s). (in-Double[3])
// xa_topo            An array that stores the resulting topocentric components.  see XA_TOPO_? (out-Double[10])
typedef void (STDCALL *fnPtrECIToTopoComps)(double theta, double lat, double senPos[3], double satPos[3], double satVel[3], double xa_topo[10]);


// Converts right ascension and declination in the topocentric reference frame to Azimuth/Elevation in the local horizon reference frame.
// thetaG             Theta - Greenwich mean sidereal time (rad). (in-Double)
// lat                Station's astronomical latitude (deg). (+N) (-S) (in-Double)
// lon                Station's astronomical longitude (deg). (+E) (-W) (in-Double)
// RA                 Right ascension (deg) (in-Double)
// dec                Declination (deg) (in-Double)
// az                 Azimuth (deg) (out-Double)
// el                 Elevation (deg) (out-Double)
typedef void (STDCALL *fnPtrRaDecToAzEl)(double thetaG, double lat, double lon, double RA, double dec, double* az, double* el);


// Converts right ascension and declination in the topocentric reference frame to Azimuth/Elevation in the local horizon reference frame.
// ds50UTC            Input time in days since 1950 UTC (in-Double)
// lat                Station's astronomical latitude (deg). (+N) (-S) (in-Double)
// lon                Station's astronomical longitude (deg). (+E) (-W) (in-Double)
// RA                 Right ascension (deg) (in-Double)
// dec                Declination (deg) (in-Double)
// az                 Azimuth (deg) (out-Double)
// el                 Elevation (deg) (out-Double)
typedef void (STDCALL *fnPtrRaDecToAzElTime)(double ds50UTC, double lat, double lon, double RA, double dec, double* az, double* el);


// Converts Azimuth/Elevation in the local horizon reference frame to Right ascension/Declination in the topocentric reference frame
// thetaG             Theta - Greenwich mean sidereal time (rad). (in-Double)
// lat                Station's astronomical latitude (deg). (+N) (-S) (in-Double)
// lon                Station's astronomical longitude (deg). (+E) (-W) (in-Double)
// az                 Azimuth (deg) (in-Double)
// el                 Elevation (deg) (in-Double)
// RA                 Right ascension (deg) (out-Double)
// dec                Declination (deg) (out-Double)
typedef void (STDCALL *fnPtrAzElToRaDec)(double thetaG, double lat, double lon, double az, double el, double* RA, double* dec);


// Converts Azimuth/Elevation in the local horizon reference frame to Right ascension/Declination in the topocentric reference frame
// ds50UTC            Input time in days since 1950 UTC (in-Double)
// lat                Station's astronomical latitude (deg). (+N) (-S) (in-Double)
// lon                Station's astronomical longitude (deg). (+E) (-W) (in-Double)
// az                 Azimuth (deg) (in-Double)
// el                 Elevation (deg) (in-Double)
// RA                 Right ascension (deg) (out-Double)
// dec                Declination (deg) (out-Double)
typedef void (STDCALL *fnPtrAzElToRaDecTime)(double ds50UTC, double lat, double lon, double az, double el, double* RA, double* dec);


// Converts full state RAE (range, az, el, and their rates) to full state ECI (position and velocity)
// The xa_rae array has the following structure:
// [0]: Range (km)
// [1]: Azimuth (deg)
// [2]: Elevation (deg)
// [3]: Range Dot (km/s)
// [4]: Azimuth Dot (deg/s)
// [5]: Elevation Dot (deg/s)
// theta              Theta - local sidereal time(rad). (in-Double)
// astroLat           Astronomical latitude (ded). (in-Double)
// xa_rae             An array contains input data.  see XA_RAE_? (in-Double[6])
// senPos             Sensor position in ECI (km). (in-Double[3])
// satPos             Satellite position in ECI (km). (out-Double[3])
// satVel             Satellite velocity in ECI (km/s). (out-Double[3])
typedef void (STDCALL *fnPtrRAEToECI)(double theta, double astroLat, double xa_rae[6], double senPos[3], double satPos[3], double satVel[3]);


// Computes initial values for the SGP drag term nDot and the SGP4 drag term BSTAR based upon eccentricity and semi-major axis.
// semiMajorAxis      Semi-major axis (km). (in-Double)
// eccen              Eccentricity (unitless). (in-Double)
// nDot               nDot (revs/day^2). (out-Double)
// bstar              Bstar (1/earth radii). (out-Double)
typedef void (STDCALL *fnPtrGetInitialDrag)(double semiMajorAxis, double eccen, double* nDot, double* bstar);


// Converts covariance matrix PTW to UVW.
// PTW = P: TxW, T: along velocity direction, W: pos x vel.
// UVW = U: radial direction, V: in plane, perpendicular to U, W: pos x vel.
// pos                The input position vector (km). (in-Double[3])
// vel                The input velocity vector (km/s). (in-Double[3])
// ptwCovMtx          The PTW covariance matrix to be converted. (in-Double[6, 6])
// uvwCovMtx          The resulting UVW covariance matrix. (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxPTWToUVW)(double pos[3], double vel[3], double ptwCovMtx[6][6], double uvwCovMtx[6][6]);


// Converts covariance matrix UVW to PTW.
// PTW = P: TxW, T: along velocity direction, W: pos x vel.
// UVW = U: radial direction, V: in plane, perpendicular to U, W: pos x vel.
// pos                The input position vector (km). (in-Double[3])
// vel                The input velocity vector (km/s). (in-Double[3])
// uvwCovMtx          The UVW covariance matrix to be converted. (in-Double[6, 6])
// ptwCovMtx          The resulting PTW covariance matrix. (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxUVWToPTW)(double pos[3], double vel[3], double uvwCovMtx[6][6], double ptwCovMtx[6][6]);


// Computes Earth/Sensor/Earth Limb and Earth/Sensor/Satellite angles.
// earthLimb          Earth limb distance (km). (in-Double)
// satECI             Satellite position in ECI (km). (in-Double[3])
// senECI             Sensor position in ECI (km). (in-Double[3])
// earthSenLimb       The resulting earth/sensor/limb angle (deg). (out-Double)
// earthSenSat        The resulting earth/sensor/sat angle (deg). (out-Double)
// satEarthSen        The resulting sat/earth/sensor angle (deg). (out-Double)
typedef void (STDCALL *fnPtrEarthObstructionAngles)(double earthLimb, double satECI[3], double senECI[3], double* earthSenLimb, double* earthSenSat, double* satEarthSen);


// Determines if a point in space is sunlit at the input time ds50ET
// ds50ET             The number of days since 1950, ET for which to determine if the point is sunlit. (in-Double)
// ptEci              a position in ECI (km). (in-Double[3])
// returns 0=no, the specified point isn't sunlit, 1=yes, the specified point is sunlit
typedef int (STDCALL *fnPtrIsPointSunlit)(double ds50ET, double ptEci[3]);


// Rotates Right Ascension and Declination to specified epoch
// nutationTerms      Nutation terms (4-106, 4:least accurate, 106:most acurate). (in-Integer)
// dir                1: TEME of Date To MEME year of equinox, 2: MEME year of equinox to TEME of Date (in-Integer)
// ds50UTCIn          Origin time in days since 1950 UTC (in-Double)
// RAIn               Input right ascension (deg) (in-Double)
// declIn             Input declination (deg) (in-Double)
// ds50UTCOut         Destination time in days since 1950 UTC (in-Double)
// RAOut              Output right ascension (deg) (out-Double)
// declOut            Output declination (deg) (out-Double)
typedef void (STDCALL *fnPtrRotRADecl)(int nutationTerms, int dir, double ds50UTCIn, double RAIn, double declIn, double ds50UTCOut, double* RAOut, double* declOut);


// Rotates Right Ascension and Declination from TEME of Date to MEME of the specified year of equinox
// nutationTerms      Nutation terms (4-106, 4:least accurate, 106:most acurate). (in-Integer)
// yrOfEqnx           Year of equinox (=1: 0 Jan of input year, =2: J2000, =3: B1950) (in-Integer)
// ds50UTCIn          Input time in days since 1950 UTC (in-Double)
// RAIn               Input right ascension (deg) (in-Double)
// declIn             Input declination (deg) (in-Double)
// RAOut              Output right ascension (deg) (out-Double)
// declOut            Output declination (deg) (out-Double)
// returns 0 if the rotation was successful, non-0 if there is an error
typedef int (STDCALL *fnPtrRotRADec_DateToEqnx)(int nutationTerms, int yrOfEqnx, double ds50UTCIn, double RAIn, double declIn, double* RAOut, double* declOut);


// Rotates Right Ascension and Declination from MEME of the specified year of equinox to TEME of Date
// nutationTerms      Nutation terms (4-106, 4:least accurate, 106:most acurate) (in-Integer)
// yrOfEqnx           Year of equinox (=1: 0 Jan of input year, =2: J2000, =3: B1950) (in-Integer)
// ds50UTCIn          Input time in days since 1950 UTC (in-Double)
// RAIn               Input right ascension (deg) (in-Double)
// declIn             Input declination (deg) (in-Double)
// RAOut              Output right ascension (deg) (out-Double)
// declOut            Output declination (deg) (out-Double)
// returns 0 if the rotation was successful, non-0 if there is an error
typedef int (STDCALL *fnPtrRotRADec_EqnxToDate)(int nutationTerms, int yrOfEqnx, double ds50UTCIn, double RAIn, double declIn, double* RAOut, double* declOut);


// Rotates the Equinoctial covariance to UVW
// Note: This method uses the global Earth constants so make sure that you select the right Earth model by calling the EnvConst/EnvSetGeoIdx method
// The n terms must be normalized by n
// The input position, velocity and covariance must all have the same reference equator and equinox.
// pos                The input position vector in ECI (in-Double[3])
// vel                The input velocity vector in ECI (in-Double[3])
// covMtxEqnx         The input covariance matrix in equinoctial elements (af, ag, Lbar, n/n, chi, psi) (in-Double[6, 6])
// covMtxUVW          The output covariance in UVW (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxEqnxToUVW)(double pos[3], double vel[3], double covMtxEqnx[6][6], double covMtxUVW[6][6]);


// Rotates the UVW covariance to Equinoctial
// Note: This method uses the global Earth constants so make sure that you select the right Earth model by calling the EnvConst/EnvSetGeoIdx method
// The n terms are normalized by n
// The input position, velocity reference equator and equinox determine the output covariance reference frame.
// pos                The input position vector in ECI TEME Of Date (in-Double[3])
// vel                The input velocity vector in ECI TEME Of Date (in-Double[3])
// covMtxUVW          The input covariance matrix UVW (in-Double[6, 6])
// covMtxEqnx         The output covariance in in equinoctial elements (af, ag, Lbar, n/n, chi, psi) (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxUVWToEqnx)(double pos[3], double vel[3], double covMtxUVW[6][6], double covMtxEqnx[6][6]);


// Rotates the ECI covariance to UVW
// Note: This method uses the global Earth constants so make sure that you select the proper Earth model by calling the EnvConst/EnvSetGeoIdx method
// pos                The input position vector in either TEME or J2K ECI (in-Double[3])
// vel                The input velocity vector in either TEME or J2K ECI (in-Double[3])
// covMtxECI          The input covariance matrix in ECI (in-Double[6, 6])
// covMtxUVW          The output covariance in UVW (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxECIToUVW)(double pos[3], double vel[3], double covMtxECI[6][6], double covMtxUVW[6][6]);


// Rotates the UVW covariance to ECI
// Note: This method uses the global Earth constants so make sure that you select the proper Earth model by calling the EnvConst/EnvSetGeoIdx method
// pos                The input position vector in either TEME or J2K ECI (in-Double[3])
// vel                The input velocity vector in either TEME or J2K ECI (in-Double[3])
// covMtxUVW          The input covariance matrix in UVW (in-Double[6, 6])
// covMtxECI          The output covariance in ECI (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxUVWToECI)(double pos[3], double vel[3], double covMtxUVW[6][6], double covMtxECI[6][6]);


// Converts covariance matrix ECI to EFG.
// EFG = Earth Fixed Greenwich
// ECI = Earth Centered Inertial - need to determine TEME or J2K
// thetaG             theta - local sidereal time (rad) (in-Double)
// covECI             6x6 ECI Covariance (in-Double[6, 6])
// covEFG             6x6 EFG Covariance (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxECIToEFG)(double thetaG, double covECI[6][6], double covEFG[6][6]);


// Converts covariance matrix EFG to ECI.
// EFG = Earth Fixed Greenwich
// ECI = Earth Centered Inertial - need to determine TEME or J2K
// thetaG             theta - local sidereal time (rad) (in-Double)
// covEFG             6x6 EFG Covariance (in-Double[6, 6])
// covECI             6x6 ECI Covariance (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxEFGToECI)(double thetaG, double covEFG[6][6], double covECI[6][6]);


// Converts 6x6 symmetric Matrix/2D array to 1D array of 21 elements (lower triangular of a 6x6 symmetric matrix)
// symMtx6x6          Input 6x6 symmetric matrix (in-Double[6, 6])
// lta21              Output 1D array of 21 elements (lower triangular of a 6x6 matrix) (out-Double[21])
typedef void (STDCALL *fnPtrMtx6x6ToLTA21)(double symMtx6x6[6][6], double lta21[21]);


// Converts 1D array of 21 elements (lower triangular of a 6x6 symmetric matrix) to a 6x6 symmetric matrix
// lta21              Input 1D array of 21 elements (lower triangular of a 6x6 matrix) (in-Double[21])
// symMtx6x6          Output 6x6 symmetric matrix (out-Double[6, 6])
typedef void (STDCALL *fnPtrLTA21ToMtx6x6)(double lta21[21], double symMtx6x6[6][6]);


// Converts 9x9 symmetric Matrix/2D array to 1D array of 45 elements (lower triangular of a 9x9 symmetric matrix)
// symMtx9x9          Input 9x9 symmetric matrix (in-Double[9, 9])
// lta45              Output 1D array of 45 elements (lower triangular of a 9x9 matrix) (out-Double[45])
typedef void (STDCALL *fnPtrMtx9x9ToLTA45)(double symMtx9x9[9][9], double lta45[45]);


// Converts 1D array of 45 elements (lower triangular of a 9x9 symmetric matrix) to a 9x9 symmetric matrix
// lta45              Input 1D array of 45 elements (lower triangular of a 9x9 matrix) (in-Double[45])
// symMtx9x9          Output 9x9 symmetric matrix (out-Double[9, 9])
typedef void (STDCALL *fnPtrLTA45ToMtx9x9)(double lta45[45], double symMtx9x9[9][9]);


// Propagate xyzDate covariance forward to the propagation time
// rms                Root mean square of observation residulas (in-Double)
// consider           Density consider parameter, 12 is recommended (this is a percentile) (in-Double)
// stateArray         State transition matrix (in-Double[54])
// cov                Covariance matrix at start time (in-Double[9, 9])
// propCov            Covariance at end time for state matrix (out-Double[6, 6])
typedef void (STDCALL *fnPtrPropCovFrState)(double rms, double consider, double stateArray[54], double cov[9][9], double propCov[6][6]);


// Rotates the ECI covariance to UVW
// Note: This method uses the global Earth constants so make sure that you select the proper Earth model by calling the EnvConst/EnvSetGeoIdx method
// pos                The input position vector in either TEME or J2K ECI (in-Double[3])
// vel                The input velocity vector in either TEME or J2K ECI (in-Double[3])
// covMtxECI          The input covariance matrix in ECI (in-Double[9, 9])
// covMtxEqnx         The output covariance in UVW (out-Double[9, 9])
typedef void (STDCALL *fnPtrCovMtxECIToEqnx)(double pos[3], double vel[3], double covMtxECI[9][9], double covMtxEqnx[9][9]);


// Rotates the UVW covariance to ECI
// Note: This method uses the global Earth constants so make sure that you select the proper Earth model by calling the EnvConst/EnvSetGeoIdx method
// pos                The input position vector in either TEME or J2K ECI (in-Double[3])
// vel                The input velocity vector in either TEME or J2K ECI (in-Double[3])
// covEqnx            45 or 55 (in-Double[9, 9])
// covMtxECI          The output covariance in ECI (out-Double[9, 9])
typedef void (STDCALL *fnPtrCovMtxEqnxToECI9x9)(double pos[3], double vel[3], double covEqnx[9][9], double covMtxECI[9][9]);


// Rotates the UVW covariance to ECI
// Note: This method uses the global Earth constants so make sure that you select the proper Earth model by calling the EnvConst/EnvSetGeoIdx method
// pos                The input position vector in either TEME or J2K ECI (in-Double[3])
// vel                The input velocity vector in either TEME or J2K ECI (in-Double[3])
// covEqnx            45 or 55 (in-Double[9, 9])
// covMtxUVW          The output covariance in ECI (out-Double[9, 9])
typedef void (STDCALL *fnPtrCovMtxEqnxToUVW9x9)(double pos[3], double vel[3], double covEqnx[9][9], double covMtxUVW[9][9]);


// Update (propagate) covariance to a future time with a supplied covariance, state transition matrix
// consider parameter and RMS. Consider parameter is applied to the drag term only.
// Full covariance matrix is multiplied by RMS squared.  State transition matrix can be obtained from 
// SpProp.SpGetStateMtx or supplying your own. State matrix, input and output covariance must be in 
// matching coordinate systems.
// rmsIn              Root mean square of sensor errors (in-Double)
// consider           Consider parameter (percentage) (in-Double)
// cov                Covariance at epoch (in-Double[9, 9])
// stateArray         Consider parameter and root mean square (in-Double[54])
// propCov            Updated covariance (out-Double[6, 6])
typedef void (STDCALL *fnPtrCovMtxUpdate)(double rmsIn, double consider, double cov[9][9], double stateArray[54], double propCov[6][6]);


// Annual Aberration calculated using equations from Astronomical Algorithms, Jean Meeus, 2nd Edition with Corrections as of June 15, 2005
// ra                 Input right ascension (Degrees) (in-Double)
// decl               Input declination (Degrees) (in-Double)
// dS50UTC            Time in days since 1950 UTC (in-Double)
// raDelta            Right Ascension delta due to Annual Aberration (deg) (out-Double)
// decDelta           Declination delta due to Annual Aberration (deg) (out-Double)
typedef void (STDCALL *fnPtrAberrationAnnual)(double ra, double decl, double dS50UTC, double* raDelta, double* decDelta);


// Diurnal Aberration is due to the rotation of the Earth about it's axis. This is only valid for ground based sensors.
// Diurnal Aberration calculated using equations from Explanatory Supplement to the Astronomical Almanac 3rd Edition, 2013
// ra                 Input right ascension (Degrees) (in-Double)
// decl               Input declination (Degrees) (in-Double)
// dS50UTC            Time in days since 1950 UTC (in-Double)
// senPos             Sensor EFG geocentric position (meters) (in-Double[3])
// raDelta            Right Ascension delta due to Diurnal Aberration (Degrees) (out-Double)
// decDelta           Declination delta due to Diurnal Aberration  (Degrees) (out-Double)
typedef void (STDCALL *fnPtrAberrationDiurnal)(double ra, double decl, double dS50UTC, double senPos[3], double* raDelta, double* decDelta);


// Sets JPL parameters
// Notes: Set JPL parameters will be used by SP, SPG4-XP, and anything that requires access to JPL data
// jplFile            The name of the JPL file. (in-Character[512])
// ds50Start          Start Time of JPL ephmeris to load (in-Double)
// ds50Stop           End Time of JPL ephemeris to load (in-Double)
typedef void (STDCALL *fnPtrJplSetParameters)(char jplFile[512], double ds50Start, double ds50Stop);


// Gets JPL parameters
// jplFile            The name of the JPL file. (out-Character[512])
// ds50Start          Start Time of Ephmeris to load (out-Double)
// ds50Stop           End Time of Ephemeris to load (out-Double)
typedef void (STDCALL *fnPtrJplGetParameters)(char jplFile[512], double* ds50Start, double* ds50Stop);


// Resets JPL parameters & removes JPL ephemeris data
typedef void (STDCALL *fnPtrJplReset)();


// Computes various Sun and Moon vectors base on loaded JPL data at the specified time.
// Note: if JPL data isn't loaded or available, all output parameters are set to zero
// ds50UTC            Input time in day since 1950 UTC (in-Double)
// uvecSun            The resulting sun position unit vector. (out-Double[3])
// sunVecMag          The resulting magnitude of the sun position vector (km). (out-Double)
// uvecMoon           The resulting moon position unit vector. (out-Double[3])
// moonVecMag         The resulting magnitude of the moon position vector (km). (out-Double)
typedef void (STDCALL *fnPtrJplCompSunMoonVec)(double ds50UTC, double uvecSun[3], double* sunVecMag, double uvecMoon[3], double* moonVecMag);


// Computes Sun and Moon position vectors base on loaded JPL data at the specified time.
// Note: if JPL data isn't loaded or available, all output parameters are set to zero
// ds50UTC            Input time in day since 1950 UTC (in-Double)
// sunVec             The resulting sun position vector (km). (out-Double[3])
// moonVec            The resulting sun position vector (km). (out-Double[3])
typedef void (STDCALL *fnPtrJplCompSunMoonPos)(double ds50UTC, double sunVec[3], double moonVec[3]);


// Removes the JPL ephemeris from memory
typedef void (STDCALL *fnPtrRemoveJpl)();
  
  // Index of Keplerian elements
  static const int  
     XA_KEP_A     =   0,       // semi-major axis (km)
     XA_KEP_E     =   1,       // eccentricity (unitless)
     XA_KEP_INCLI =   2,       // inclination (deg)
     XA_KEP_MA    =   3,       // mean anomaly (deg)
     XA_KEP_NODE  =   4,       // right ascension of the asending node (deg)
     XA_KEP_OMEGA =   5,       // argument of perigee (deg)
     XA_KEP_SIZE  =  6;   
     
  // Index of classical elements
  static const int  
     XA_CLS_N     =   0,       // N mean motion (revs/day)
     XA_CLS_E     =   1,       // eccentricity (unitless)
     XA_CLS_INCLI =   2,       // inclination (deg)
     XA_CLS_MA    =   3,       // mean anomaly (deg)
     XA_CLS_NODE  =   4,       // right ascension of the asending node (deg)
     XA_CLS_OMEGA =   5,       // argument of perigee (deg)
     XA_CLS_SIZE  =   6;
  
  // Index of equinoctial elements
  static const int  
     XA_EQNX_AF   =   0,       // Af (unitless) 
     XA_EQNX_AG   =   1,       // Ag (unitless)
     XA_EQNX_CHI  =   2,       // chi (unitless)
     XA_EQNX_PSI  =   3,       // psi (unitless)
     XA_EQNX_L    =   4,       // L mean longitude (deg)
     XA_EQNX_N    =   5,       // N mean motion (revs/day)
     XA_EQNX_SIZE =   6;
     
  // Indexes of AstroConvFrTo
  static const int  
     XF_CONV_SGP42SGP = 101;        // SGP4 (A, E, Incli, BStar) to SGP (nDot, n2Dot)
  
  
  // Indexes for topocentric components
  static const int  
     XA_TOPO_RA    = 0,         // Right ascension (deg)
     XA_TOPO_DEC   = 1,         // Declination (deg)
     XA_TOPO_AZ    = 2,         // Azimuth (deg)
     XA_TOPO_EL    = 3,         // Elevation (deg)
     XA_TOPO_RANGE = 4,         // Range (km)
     XA_TOPO_RADOT = 5,         // Right ascension dot (deg/s)
     XA_TOPO_DECDOT= 6,         // Declincation dot (deg/s)
     XA_TOPO_AZDOT = 7,         // Azimuth dot (deg/s)
     XA_TOPO_ELDOT = 8,         // Elevation dot (deg/s)
     XA_TOPO_RANGEDOT = 9,      // Range dot (km/s)   
     XA_TOPO_SIZE  = 10;   
     
     
  // Indexes for RAE components
  static const int  
     XA_RAE_RANGE   = 0,        // Range (km)
     XA_RAE_AZ      = 1,        // Azimuth (deg)
     XA_RAE_EL      = 2,        // Elevation (deg)
     XA_RAE_RANGEDOT= 3,        // Range dot (km/s)   
     XA_RAE_AZDOT   = 4,        // Azimuth dot (deg/s)
     XA_RAE_ELDOT   = 5,        // Elevation dot (deg/s)
     XA_RAE_SIZE    = 6;
     
     
  // Year of Equinox indicator
  static const int  
     YROFEQNX_OBTIME = 0,       // Date of observation
     YROFEQNX_CURR   = 1,       // 0 Jan of Date
     YROFEQNX_2000   = 2,       // J2000
     YROFEQNX_1950   = 3;       // B1950
     
// AstroFuncDll's function pointers declaration
extern fnPtrAstroFuncInit                  AstroFuncInit;
extern fnPtrAstroFuncGetInfo               AstroFuncGetInfo;
extern fnPtrKepToEqnx                      KepToEqnx;
extern fnPtrKepToPosVel                    KepToPosVel;
extern fnPtrKepToUVW                       KepToUVW;
extern fnPtrClassToEqnx                    ClassToEqnx;
extern fnPtrEqnxToClass                    EqnxToClass;
extern fnPtrEqnxToKep                      EqnxToKep;
extern fnPtrEqnxToPosVel                   EqnxToPosVel;
extern fnPtrPosVelToEqnx                   PosVelToEqnx;
extern fnPtrPosVelMuToEqnx                 PosVelMuToEqnx;
extern fnPtrPosVelToKep                    PosVelToKep;
extern fnPtrPosVelMuToKep                  PosVelMuToKep;
extern fnPtrPosVelToUUVW                   PosVelToUUVW;
extern fnPtrPosVelToPTW                    PosVelToPTW;
extern fnPtrSolveKepEqtn                   SolveKepEqtn;
extern fnPtrCompTrueAnomaly                CompTrueAnomaly;
extern fnPtrNToA                           NToA;
extern fnPtrAToN                           AToN;
extern fnPtrKozaiToBrouwer                 KozaiToBrouwer;
extern fnPtrBrouwerToKozai                 BrouwerToKozai;
extern fnPtrKepOscToMean                   KepOscToMean;
extern fnPtrXYZToLLH                       XYZToLLH;
extern fnPtrXYZToLLHTime                   XYZToLLHTime;
extern fnPtrLLHToXYZ                       LLHToXYZ;
extern fnPtrLLHToXYZTime                   LLHToXYZTime;
extern fnPtrEFGToECI                       EFGToECI;
extern fnPtrEFGToECITime                   EFGToECITime;
extern fnPtrECIToEFG                       ECIToEFG;
extern fnPtrECIToEFGTime                   ECIToEFGTime;
extern fnPtrECRToEFG                       ECRToEFG;
extern fnPtrECRToEFGTime                   ECRToEFGTime;
extern fnPtrEFGToECR                       EFGToECR;
extern fnPtrEFGToECRTime                   EFGToECRTime;
extern fnPtrEFGPosToLLH                    EFGPosToLLH;
extern fnPtrLLHToEFGPos                    LLHToEFGPos;
extern fnPtrRotJ2KToDate                   RotJ2KToDate;
extern fnPtrRotDateToJ2K                   RotDateToJ2K;
extern fnPtrCompSunMoonPos                 CompSunMoonPos;
extern fnPtrCompSunPos                     CompSunPos;
extern fnPtrCompMoonPos                    CompMoonPos;
extern fnPtrAstroConvFrTo                  AstroConvFrTo;
extern fnPtrRADecToLAD                     RADecToLAD;
extern fnPtrAzElToLAD                      AzElToLAD;
extern fnPtrECIToTopoComps                 ECIToTopoComps;
extern fnPtrRaDecToAzEl                    RaDecToAzEl;
extern fnPtrRaDecToAzElTime                RaDecToAzElTime;
extern fnPtrAzElToRaDec                    AzElToRaDec;
extern fnPtrAzElToRaDecTime                AzElToRaDecTime;
extern fnPtrRAEToECI                       RAEToECI;
extern fnPtrGetInitialDrag                 GetInitialDrag;
extern fnPtrCovMtxPTWToUVW                 CovMtxPTWToUVW;
extern fnPtrCovMtxUVWToPTW                 CovMtxUVWToPTW;
extern fnPtrEarthObstructionAngles         EarthObstructionAngles;
extern fnPtrIsPointSunlit                  IsPointSunlit;
extern fnPtrRotRADecl                      RotRADecl;
extern fnPtrRotRADec_DateToEqnx            RotRADec_DateToEqnx;
extern fnPtrRotRADec_EqnxToDate            RotRADec_EqnxToDate;
extern fnPtrCovMtxEqnxToUVW                CovMtxEqnxToUVW;
extern fnPtrCovMtxUVWToEqnx                CovMtxUVWToEqnx;
extern fnPtrCovMtxECIToUVW                 CovMtxECIToUVW;
extern fnPtrCovMtxUVWToECI                 CovMtxUVWToECI;
extern fnPtrCovMtxECIToEFG                 CovMtxECIToEFG;
extern fnPtrCovMtxEFGToECI                 CovMtxEFGToECI;
extern fnPtrMtx6x6ToLTA21                  Mtx6x6ToLTA21;
extern fnPtrLTA21ToMtx6x6                  LTA21ToMtx6x6;
extern fnPtrMtx9x9ToLTA45                  Mtx9x9ToLTA45;
extern fnPtrLTA45ToMtx9x9                  LTA45ToMtx9x9;
extern fnPtrPropCovFrState                 PropCovFrState;
extern fnPtrCovMtxECIToEqnx                CovMtxECIToEqnx;
extern fnPtrCovMtxEqnxToECI9x9             CovMtxEqnxToECI9x9;
extern fnPtrCovMtxEqnxToUVW9x9             CovMtxEqnxToUVW9x9;
extern fnPtrCovMtxUpdate                   CovMtxUpdate;
extern fnPtrAberrationAnnual               AberrationAnnual;
extern fnPtrAberrationDiurnal              AberrationDiurnal;
extern fnPtrJplSetParameters               JplSetParameters;
extern fnPtrJplGetParameters               JplGetParameters;
extern fnPtrJplReset                       JplReset;
extern fnPtrJplCompSunMoonVec              JplCompSunMoonVec;
extern fnPtrJplCompSunMoonPos              JplCompSunMoonPos;
extern fnPtrRemoveJpl                      RemoveJpl;



void LoadAstroFuncDll();
void FreeAstroFuncDll();




#endif
// ========================= End of auto generated code ==========================
