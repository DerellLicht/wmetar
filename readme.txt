METAR Decoder utility for Windows
dan7miller@comcast.net
Last update: 08/19/13

The original source code for this project was obtained from:
http://mdsplib.sourceforge.net/
on August 14, 2013.

My modified package has the same licensing rules as the original package, 
which is listed thus:

   Of benefit to users, Open Source software is licensed so you can download 
   and use the software free-of-charge. The source code for this software is 
   made available free-of-charge, you (or a programmer you hire) can make 
   changes to this software to better meet your needs, and you can release 
   your changed code back to the community passing the benefit on to other 
   users. 

//************************************************************
Sample output (via klvk.bat file, included in install directory)

*****************************************************
INPUT METAR REPORT:
   METAR KLVK 141853Z 30009KT 10SM CLR 28/09 A2996 RMK AO2 SLP140 T02830094

/*******************************************/
/*    DECODED METAR REPORT
/*******************************************/
REPORT CODE NAME    : METAR
STATION ID          : KLVK: LIVERMORE, CA, loc 37.42N, 121.49W, elev 117 meters
OBSERVATION DATE    : 14th, 1853
WIND DIRECTION      : 300
WIND SPEED          : 9
WIND UNITS          : KT
PREVAIL VSBY (SM)   : 10.000
CLOUD COVER         : CLR
TEMP. (degsF)       : 82
D.P. TEMP. (degsF)  : 48
ALTIMETER (INCHES)  : 29.96
AUTO INDICATOR      : AO2
SLP (hPa)           : 1014.0
TMP2TENTHS (degsF)  : 82.9
DPT2TENTHS (degsF)  : 48.9

//***********************************************************************
Build/modification notes from Derell Licht:

The source code that I obtained from the mdsplib site was not buildable
using the MinGW C compiler, Version 'gcc (GCC) 3.4.5 (mingw special)'.
So my first job was to get it to build, using a Makefile, with all
warnings turned on.
My second task was to get it to lint clean, using PcLint V9.00j.

Having accomplished this, I made the following modifications:

- Allow user to pass a METAR string (enclosed in quotes) on the 
  command line.  In the absence of any METAR string arguments, it will
  evaluate a long list of test vectors, which are now stored separately.

- add command-line switch to specify temperatures in Fahrenheit vs Celsius.

- added a module to convert the station ID into location information,
  using the stations.txt file from Greg Thompson :
! Author: Greg Thompson  NCAR/RAP
! Date: 22 Mar 2012
! This file is continuously maintained at:
! http://www.rap.ucar.edu/weather/surface/stations.txt


