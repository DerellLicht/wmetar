//***************************************************************************************
//  Copyright (c) 2013  Daniel D Miller
//  Project: metar.exe (derived from mdsplib package on Sourceforge)
//  station_name.c - look up station name from station ID,
//  using Greg Thompson's stations.txt file.
//***************************************************************************************
// ! Author: Greg Thompson  NCAR/RAP
// !         please mail corrections to gthompsn (at) ucar (dot) edu
// ! Date: 22 Mar 2012
// ! This file is continuously maintained at:
// ! http://www.rap.ucar.edu/weather/surface/stations.txt
// !
// ! This file is organized by state alphabetically, then by Canadian
// ! province and then all other stations.  The file was compiled from lists
// ! of the following:
// !      METAR sites
// !      NEXRADs
// !      rawinsonde sites
// !      wind profilers
// !      WFOs, RFCs, NCEP-Centers
// !      AIRMET/SIGMET station list (VORs?)
// !      ARTCCs (Air Route Traffic Control Centers - FAA)
// !      old SAO sites for archive data access  (flagged in a special manner)
// !
// !   Country abbreviations from ISO 3166
// !   source:  ftp://ftp.fu-berlin.de/doc/iso/iso3166-countrycodes.txt
// !   another: http://www.iso.org/iso/en/prods-services/iso3166ma/02iso-3166-code-lists/list-en1.html
// !
// !   CD = 2 letter state (province) abbreviation
// !   STATION = 16 character station long name
// !   ICAO = 4-character international id
// !   IATA = 3-character (FAA) id
// !   SYNOP = 5-digit international synoptic number
// !   LAT = Latitude (degrees minutes)
// !   LON = Longitude (degree minutes)
// !   ELEV = Station elevation (meters)
// !   M = METAR reporting station.   Also Z=obsolete? site
// !   N = NEXRAD (WSR-88D) Radar site
// !   V = Aviation-specific flag (V=AIRMET/SIGMET end point, A=ARTCC T=TAF U=T+V)
// !   U = Upper air (rawinsonde=X) or Wind Profiler (W) site
// !   A = Auto (A=ASOS, W=AWOS, M=Meso, H=Human, G=Augmented) (H/G not yet impl.)
// !   C = Office type F=WFO/R=RFC/C=NCEP Center
// !   Digit that follows is a priority for plotting (0=highest)
// !   Country code (2-char) is last column
//***************************************************************************************
// !23456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
// ALASKA             30-DEC-11                                                  
// CD  STATION         ICAO  IATA  SYNOP   LAT     LONG   ELEV   M  N  V  U  A  C
// AK ADAK NAS         PADK  ADK   70454  51 53N  176 39W    4   X     T          7 US
//***************************************************************************************
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <common.h>
#include "wmetar.h"

#define  MAX_LINE_LEN   260

static char stations_file[PATH_MAX+1] = "" ;

//***************************************************************************************
station_data_p lookup_station_name(char *icao)
{
   char inpstr[MAX_LINE_LEN+1] ;
   static station_data_t station_data ;

   if (strlen(stations_file) == 0) {
      derive_file_path(stations_file, "stations.txt") ;
      // exec_fname=C:\SourceCode\win32\metar\metar.exe
      // syslog("found %s\n", stations_file) ;
   }
   // char stations_file[PATH_MAX] = "stations.txt" ; //  later, use source path as reference
   FILE *fd = fopen(stations_file, "rt") ;
   if (fd == NULL) {
      syslog("%s: %s\n", stations_file, get_system_message()) ;
      return NULL;
   }
   bool target_found = false ;
   // uint lcount = 0 ;
   // uint gcount = 0 ;
   while (fgets(inpstr, MAX_LINE_LEN, fd) != NULL) {
      // lcount++ ;
      if (inpstr[0] == '!')
         continue;
      strip_newlines(inpstr) ;
      if (strlen(inpstr) == 0)
         continue;
      if (strlen(inpstr) < 44)
         continue;
      if (strncasecmp(inpstr, "CD  STATION", 11) == 0)
         continue;
      // gcount++ ;
      //  okay, we seem to have found a data line; let's parse it.
      // 0         1         2         3         4         5         6
      // 0123456789012345678901234567890123456789012345678901234567890123456789
      // AK ADAK NAS         PADK  ADK   70454  51 53N  176 39W    4   X     T          7 US
      if (strncasecmp(icao, &inpstr[20], 4) == 0) {
         char *hd, *tl, *temp ;
         // printf("L%u: [%s]\n", lcount, inpstr) ;
         memset((char *) &station_data, 0, sizeof(station_data_t)) ;

         //  get state
         inpstr[2] = 0 ;
         strcpy(station_data.state, inpstr) ;

         //  station name
         hd = &inpstr[3] ;
         tl = &inpstr[19] ;
         *tl = 0 ;
         strip_trailing_spaces(hd) ;
         strcpy(station_data.station, hd) ;

         strcpy(station_data.icao, icao) ;

// CD  STATION         ICAO  IATA  SYNOP   LAT     LONG   ELEV   M  N  V  U  A  C
// AK ADAK NAS         PADK  ADK   70454  51 53N  176 39W    4   X     T          7 US
         //  get latitude
         hd = &inpstr[39] ;   
         //  hd is now pointing to latitude
         tl = next_field(hd) ;   //  skip first part
         tl = next_field(tl) ;   //  skip second part
         //  tl is now pointing to longitude
         *(tl-1) = 0 ;  //  terminate LAT string
         strip_trailing_spaces(hd) ;
         temp = strchr(hd, ' ') ;
         if (temp != NULL) {
            *temp = '.' ;
         }
         strcpy(station_data.longitude, hd) ;

         //  get longitude
         hd = tl ;
         tl = next_field(hd) ;   //  skip first part
         tl = next_field(tl) ;   //  skip second part
         //  tl is now pointing to elevation
         station_data.elevation = atoi(tl) ;
         *(tl-1) = 0 ;  //  terminate LONG string
         strip_trailing_spaces(hd) ;
         temp = strchr(hd, ' ') ;
         if (temp != NULL) {
            *temp = '.' ;
         }
         strcpy(station_data.latitude, hd) ;

         // printf("%s found at %s, %s, at %s, %s, elevation %u meters\n", 
         //    station_data.icao, station_data.station, station_data.state,
         //    station_data.longitude, station_data.latitude, station_data.elevation   ) ;
        
         target_found = true ;
         break;
      }
   }
   fclose(fd) ;
   // printf("processed %u total lines, %u data lines\n", lcount, gcount) ;
   if (!target_found)
      return NULL;
   return &station_data ;
}

