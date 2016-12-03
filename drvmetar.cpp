//********************************************************************************************
//  Copyright (c) 2013  Daniel D Miller
//  Modified the package to build under Gnu gcc, added some functionality.
//  The licensing for this modified package remains the same as Eric McCarthy's distribution,
//  as documented below.
//********************************************************************************************
//  Version    date        comments
//  1.00       08/15/13    Initial distribution
//  1.01       08/16/13    Add version number, Makefile now detects Windows vs Linux
//********************************************************************************************

/********************************************************************************************
METAR Decoder Software Package Library: Parses Aviation Routine Weather Reports
Copyright (C) 2003  Eric McCarthy

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*********************************************************************************************/

//********************************************************************************************
//*  Title:         dRVMETAR                                         
//*  Organization:  W/OSO242 - GRAPHICS AND DISPLAY SECTION          
//*  Date:          28 Oct 1994                                      
//*  Programmer:    CARL MCCALLA                                     
//*  Language:      C/370                                            
//*                                                                  
//*  DRVMETAR is a main routine that acts a driver for testing the METAR Decoder function.    
//*                                                                  
//********************************************************************************************

#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#include "wmetar.h"     /* standard header file */
#include "metar_structs.h"

static char const * const Version = "Metar report decoder, V1.01" ;

int DcdMETAR( char *, Decoded_METAR * );
void prtDMETR( Decoded_METAR *);
 
//  from test_cases.c
//lint -esym(843, string)  variable could be declared as const
extern char *string[] ;

//********************************************************************************************
static void process_metar_string(char *metar_str)
{
   Decoded_METAR Metar;

   /*-- PRINT INPUT METAR REPORT ----------------------------*/
   puts("") ;
   puts("*****************************************************") ;
   puts("INPUT METAR REPORT:") ;
   printf("   %s\n", metar_str );
 
   /*-- DECODE INPUT REPORT ---------------------------------*/
   int ErReturn = DcdMETAR(metar_str, &Metar) ;
   if (ErReturn != 0 ) {
      printf("DcdMETAR:  Error Return Number: %d\n",ErReturn);
      return ;
   }
   /*-- PRINT DECODED METAR REPORT ELEMENTS -----------------*/
   puts("") ;
   prtDMETR(&Metar);
   //@@@  included test code that was here, has been moved to synoptic.cxx
}

//********************************************************************************************
static void usage(void)
{
   puts("Usage: metar [options] [optional METAR string]") ;
   puts("Options:") ;
   puts(" -f  show temperatures in Fahrenheit vs Celsus") ;
   puts(" -t  run the build-in test vectors") ;
   puts("") ;
   puts("NOTE: settings options *must* precede a METAR string!") ;
}

//********************************************************************************************
// "METAR KLVK 141853Z 30009KT 10SM CLR 28/09 A2996 RMK AO2 SLP140 T02830094",
//********************************************************************************************
uint use_fahrenheit = FALSE ;

int main(int argc, char **argv)
{
   uint use_test_vectors = FALSE ;
   //  parse command line
   uint found_metar_arg = FALSE ;
   puts(Version) ;
   int idx ;
   for (idx=1; idx<argc; idx++) {
      char *arg = argv[idx] ;
      if (*arg == '-') {
         arg++ ;
         switch (*arg) {
         case 'f':
            use_fahrenheit = TRUE ;
            break;

         case 't':
            use_test_vectors = TRUE ;
            break;

         // case 'h':
         default:
            usage() ;
            return 0;
         }

      } else {
         process_metar_string(arg) ;
         found_metar_arg = TRUE ;
      }
   }

   //  if no strings are found on command line, process our test cases
   if (use_test_vectors) {
      for (idx=0; string[idx] != NULL; idx++) {
         process_metar_string(string[idx]) ;
      }
   }

   if (!use_test_vectors  &&  !found_metar_arg) {
      usage() ;
   }
   return 0;
}

