METAR Decoder utility for Windows  
by Derell Licht

This project is licensed under _Creative Commons CC0 1.0 Universal_   

See the [License](LICENSE.txt) file for detailed information about this license
<hr>

See [Changelog](CHANGELOG.md) for the full revision history.  

***
Sample output 
<code>
INPUT METAR REPORT:
   METAR KLVK 141853Z 30009KT 10SM CLR 28/09 A2996 RMK AO2 SLP140 T02830094
  
//*******************************************
//*    DECODED METAR REPORT
//*******************************************
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
</code>

***
The original source code for this project was obtained from:  
https://sourceforge.net/projects/mdsplib/  
on August 14, 2013.

the *heavy lifting* of this program was done by `chopperd`  
http://sourceforge.net/users/chopperd  
who developed the "METAR Decoder Software Package Library"
that I wrapped the WinAPI interface around.  Much of that library I *still*
don't actually understand, but it works beautifully!!!  

***
Build/modification notes from Derell Licht:

The source code that I obtained from the mdsplib site was not buildable
using the current version of the MinGW compiler.  
So my first job was to get it to build, using a Makefile, with all
warnings turned on.

Having accomplished this, I made the following modifications:

- Allow user to pass a METAR string (enclosed in quotes) on the 
  command line.  In the absence of any METAR string arguments, it will
  evaluate a long list of test vectors, which are now stored separately.

- add command-line switch to specify temperatures in Fahrenheit vs Celsius.

- added a module to convert the station ID into location information,
  using the stations.txt file from Greg Thompson :
> Author: Greg Thompson  NCAR/RAP  
> Date: 22 Mar 2012  
> This file is continuously maintained at:  
> http://www.rap.ucar.edu/weather/surface/stations.txt  


