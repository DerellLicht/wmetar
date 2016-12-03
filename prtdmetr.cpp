/*
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
*/

#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#include <common.h>
#include "resource.h"
#include "wmetar.h"     /* standard header file */
#include "metar_structs.h"

//****************************************************************************
static float c2f(float degsC)
{
   float degsF = ((9.0 * degsC) / 5.0) + 32.0 ;
   return degsF;
}

//****************************************************************************
// static void sprint_metar (char * string, Decoded_METAR *Mptr)
void prtDMETR (Decoded_METAR *Mptr)
{
   station_data_p sdata ;
   int i;
   // char temp[100];
 
   termout("/*******************************************/");
   termout("/*    DECODED METAR REPORT");
   termout("/*******************************************/");
 
   if ( Mptr->codeName[ 0 ] != '\0' ) {
      termoutf("REPORT CODE NAME    : %s\n",Mptr->codeName);
   }
 
   if ( Mptr->stnid[ 0 ] != '\0' ) {
      sdata = lookup_station_name(Mptr->stnid);
      if (sdata == NULL)
         termoutf("STATION ID          : %s\n",Mptr->stnid);
      else
         termoutf("STATION ID          : %s: %s, %s, loc %s, %s, elev %u meters\n", 
            sdata->icao, sdata->station, sdata->state,
            sdata->longitude, sdata->latitude, sdata->elevation) ;
      // termout(temp);
   }
 
   if ( Mptr->ob_date   != MAXINT  &&
        Mptr->ob_hour   != MAXINT  &&
        Mptr->ob_minute != MAXINT ) {
      termoutf("OBSERVATION DATE    : %dth, %d%d\n",Mptr->ob_date, Mptr->ob_hour, Mptr->ob_minute);
   }
 
   if ( Mptr->NIL_rpt ) {
      termoutf("NIL REPORT          : TRUE\n");
   }
 
   if ( Mptr->AUTO ) {
      termoutf("AUTO REPORT         : TRUE\n");
   }
 
   if ( Mptr->COR ) {
      termoutf("CORRECTED REPORT    : TRUE\n");
   }
 
   if ( Mptr->winData.windVRB ) {
      termoutf("WIND DIRECTION VRB  : TRUE\n");
   }
 
   if ( Mptr->winData.windDir != MAXINT ) {
      termoutf("WIND DIRECTION      : %d\n",Mptr->winData.windDir);
   }
 
   if ( Mptr->winData.windSpeed != MAXINT ) {
      termoutf("WIND SPEED          : %d\n",Mptr->winData.windSpeed);
   }
 
   if ( Mptr->winData.windGust != MAXINT ) {
      termoutf("WIND GUST           : %d\n",Mptr->winData.windGust);
   }
 
   if ( Mptr->winData.windUnits[ 0 ] != '\0' ) {
      termoutf("WIND UNITS          : %s\n",Mptr->winData.windUnits);
   }
 
   if ( Mptr->minWnDir != MAXINT ) {
      termoutf("MIN WIND DIRECTION  : %d\n",Mptr->minWnDir);
   }
 
   if ( Mptr->maxWnDir != MAXINT ) {
      termoutf("MAX WIND DIRECTION  : %d\n",Mptr->maxWnDir);
   }
 
   if ( Mptr->prevail_vsbyM != (float) MAXINT ) {
      termoutf("PREVAIL VSBY (M)    : %f\n",Mptr->prevail_vsbyM);
   }
 
   if ( Mptr->prevail_vsbyKM != (float) MAXINT ) {
      termoutf("PREVAIL VSBY (KM)   : %f\n",Mptr->prevail_vsbyKM);
   }
 
   if ( Mptr->prevail_vsbySM != (float) MAXINT ) {
      termoutf("PREVAIL VSBY (SM)   : %.3f\n",Mptr->prevail_vsbySM);
   }
/*
   if ( Mptr->charPrevailVsby[0] != '\0' ) {
      sprintf(temp, "PREVAIL VSBY (CHAR) : %s\n",Mptr->charPrevailVsby);
      strcat(string, temp);
   }
*/
   if ( Mptr->vsby_Dir[ 0 ] != '\0' ) {
      termoutf("VISIBILITY DIRECTION: %s\n",Mptr->vsby_Dir);
   }
 
   if ( Mptr->RVRNO ) {
      termoutf("RVRNO               : TRUE\n");
   }
 
   for ( i = 0; i < 12; i++ )
   {
      if( Mptr->RRVR[i].runway_designator[0] != '\0' ) {
         termoutf("RUNWAY DESIGNATOR   : %s\n", Mptr->RRVR[i].runway_designator);
      }
 
      if( Mptr->RRVR[i].visRange != MAXINT ) {
         termoutf("R_WAY VIS RANGE (FT): %d\n", Mptr->RRVR[i].visRange);
      }
 
      if ( Mptr->RRVR[i].vrbl_visRange ) {
         termoutf("VRBL VISUAL RANGE   : TRUE\n");
      }
 
      if ( Mptr->RRVR[i].below_min_RVR ) {
         termoutf("BELOW MIN RVR       : TRUE\n");
      }
 
      if ( Mptr->RRVR[i].above_max_RVR ) {
         termoutf("ABOVE MAX RVR       : TRUE\n");
      }
 
      if( Mptr->RRVR[i].Max_visRange != MAXINT ) {
         termoutf("MX R_WAY VISRNG (FT): %d\n", Mptr->RRVR[i].Max_visRange);
      }
 
      if( Mptr->RRVR[i].Min_visRange != MAXINT ) {
         termoutf("MN R_WAY VISRNG (FT): %d\n", Mptr->RRVR[i].Min_visRange);
      }
   }
 
   if( Mptr->DVR.visRange != MAXINT ) {
      termoutf("DISPATCH VIS RANGE  : %d\n", Mptr->DVR.visRange);
   }
 
   if ( Mptr->DVR.vrbl_visRange ) {
      termoutf("VRBL DISPATCH VISRNG: TRUE\n");
   }
 
   if ( Mptr->DVR.below_min_DVR ) {
      termoutf("BELOW MIN DVR       : TRUE\n");
   }
 
   if ( Mptr->DVR.above_max_DVR ) {
      termoutf("ABOVE MAX DVR       : TRUE\n");
   }
 
   if( Mptr->DVR.Max_visRange != MAXINT ) {
      termoutf("MX DSPAT VISRNG (FT): %d\n", Mptr->DVR.Max_visRange);
   }
 
   if( Mptr->DVR.Min_visRange != MAXINT ) {
      termoutf("MN DSPAT VISRNG (FT): %d\n", Mptr->DVR.Min_visRange);
   }
 
   i = 0;
   while (i < MAXWXSYMBOLS  && Mptr->WxObstruct[i][0] != '\0')
   {
      termoutf("WX/OBSTRUCT VISION  : %s\n", Mptr->WxObstruct[i] );
      i++;
   }
 
   if ( Mptr->PartialObscurationAmt[0][0] != '\0' ) {
      termoutf("OBSCURATION AMOUNT  : %s\n", &(Mptr->PartialObscurationAmt[0][0]));
   }
 
   if ( Mptr->PartialObscurationPhenom[0][0] != '\0' ) {
      termoutf("OBSCURATION PHENOM  : %s\n", &(Mptr->PartialObscurationPhenom[0][0]));
   }
 
 
   if ( Mptr->PartialObscurationAmt[1][0] != '\0' ) {
      termoutf("OBSCURATION AMOUNT  : %s\n", &(Mptr->PartialObscurationAmt[1][0]));
   }
 
   if ( Mptr->PartialObscurationPhenom[1][0] != '\0' ) {
      termoutf("OBSCURATION PHENOM  : %s\n", &(Mptr->PartialObscurationPhenom[1][0]));
   }
 
   i = 0;
   while ( Mptr->cldTypHgt[ i ].cloud_type[0] != '\0' && i < 6 ) {  //lint !e662
      if ( Mptr->cldTypHgt[ i ].cloud_type[0] != '\0' ) {
         termoutf("CLOUD COVER         : %s\n", Mptr->cldTypHgt[ i ].cloud_type);
      }
 
      if ( Mptr->cldTypHgt[ i ].cloud_hgt_char[0] != '\0' ) {
         termoutf("CLOUD HGT (CHARAC.) : %s\n", Mptr->cldTypHgt[ i ].cloud_hgt_char);
      }
 
      if ( Mptr->cldTypHgt[ i ].cloud_hgt_meters != MAXINT) {
         termoutf("CLOUD HGT (METERS)  : %d\n", Mptr->cldTypHgt[ i ].cloud_hgt_meters);
      }
 
      if ( Mptr->cldTypHgt[ i ].other_cld_phenom[0] != '\0' ) {
         termoutf("OTHER CLOUD PHENOM  : %s\n", Mptr->cldTypHgt[ i ].other_cld_phenom);
      }
      i++;
   }
 
   if ( Mptr->temp != MAXINT ) {
      if (use_fahrenheit == IDC_TEMP_DEGSF)
         termoutf("TEMP. (degsF)       : %d\n", (int) c2f(Mptr->temp)); //lint !e747
      else
         termoutf("TEMP. (degsC)       : %d\n", Mptr->temp);
   }
 
   if ( Mptr->dew_pt_temp != MAXINT ) {
      if (use_fahrenheit == IDC_TEMP_DEGSF)
         termoutf("Dewpoint (degsF)    : %d\n", (int) c2f(Mptr->dew_pt_temp)); //lint !e747
      else
         termoutf("Dewpoint (degsC)    : %d\n", Mptr->dew_pt_temp);
   }
 
   if ( Mptr->A_altstng ) {
      termoutf("ALTIMETER (INCHES)  : %.2f\n", Mptr->inches_altstng );
   }
 
   if ( Mptr->Q_altstng ) {
      termoutf("ALTIMETER (PASCALS) : %d\n", Mptr->hectoPasc_altstng );
   }
 
   if ( Mptr->TornadicType[0] != '\0' ) {
      termoutf("TORNADIC ACTVTY TYPE: %s\n", Mptr->TornadicType );
   }
 
   if ( Mptr->BTornadicHour != MAXINT ) {
      termoutf("TORN. ACTVTY BEGHOUR: %d\n", Mptr->BTornadicHour );
   }
 
   if ( Mptr->BTornadicMinute != MAXINT ) {
      termoutf("TORN. ACTVTY BEGMIN : %d\n", Mptr->BTornadicMinute );
   }
 
   if ( Mptr->ETornadicHour != MAXINT ) {
      termoutf("TORN. ACTVTY ENDHOUR: %d\n", Mptr->ETornadicHour );
   }
 
   if ( Mptr->ETornadicMinute != MAXINT ) {
      termoutf("TORN. ACTVTY ENDMIN : %d\n", Mptr->ETornadicMinute );
   }
 
   if ( Mptr->TornadicDistance != MAXINT ) {
      termoutf("TORN. DIST. FROM STN: %d\n", Mptr->TornadicDistance );
   }
 
   if ( Mptr->TornadicLOC[0] != '\0' ) {
      termoutf("TORNADIC LOCATION   : %s\n", Mptr->TornadicLOC );
   }
 
   if ( Mptr->TornadicDIR[0] != '\0' ) {
      termoutf("TORNAD. DIR FROM STN: %s\n", Mptr->TornadicDIR );
   }
 
   if ( Mptr->TornadicMovDir[0] != '\0' ) {
      termoutf("TORNADO DIR OF MOVM.: %s\n", Mptr->TornadicMovDir );
   }
 
   if ( Mptr->autoIndicator[0] != '\0' ) {
      termoutf("AUTO INDICATOR      : %s\n", Mptr->autoIndicator);
   }
 
   if ( Mptr->PKWND_dir !=  MAXINT ) {
      termoutf("PEAK WIND DIRECTION : %d\n",Mptr->PKWND_dir);
   }
   if ( Mptr->PKWND_speed !=  MAXINT ) {
      termoutf("PEAK WIND SPEED     : %d\n",Mptr->PKWND_speed);
   }
   if ( Mptr->PKWND_hour !=  MAXINT ) {
      termoutf("PEAK WIND HOUR      : %d\n",Mptr->PKWND_hour);
   }
   if ( Mptr->PKWND_minute !=  MAXINT ) {
      termoutf("PEAK WIND MINUTE    : %d\n",Mptr->PKWND_minute);
   }
 
   if ( Mptr->WshfTime_hour != MAXINT ) {
      termoutf("HOUR OF WIND SHIFT  : %d\n",Mptr->WshfTime_hour);
   }
   if ( Mptr->WshfTime_minute != MAXINT ) {
      termoutf("MINUTE OF WIND SHIFT: %d\n",Mptr->WshfTime_minute);
   }
   if ( Mptr->Wshft_FROPA != FALSE ) {
      termoutf("FROPA ASSOC. W/WSHFT: TRUE\n");
   }
 
   if ( Mptr->TWR_VSBY != (float) MAXINT ) {
      termoutf("TOWER VISIBILITY    : %.2f\n",Mptr->TWR_VSBY);
   }
   if ( Mptr->SFC_VSBY != (float) MAXINT ) {
      termoutf("SURFACE VISIBILITY  : %.2f\n",Mptr->SFC_VSBY);
   }
 
   if ( Mptr->minVsby != (float) MAXINT ) {
      termoutf("MIN VRBL_VIS (SM)   : %.4f\n",Mptr->minVsby);
   }
   if ( Mptr->maxVsby != (float) MAXINT ) {
      termoutf("MAX VRBL_VIS (SM)   : %.4f\n",Mptr->maxVsby);
   }
 
   if( Mptr->VSBY_2ndSite != (float) MAXINT ) {
      termoutf("VSBY_2ndSite (SM)   : %.4f\n",Mptr->VSBY_2ndSite);
   }
   
   if( Mptr->VSBY_2ndSite_LOC[0] != '\0' ) {
      termoutf("VSBY_2ndSite LOC.   : %s\n",
                   Mptr->VSBY_2ndSite_LOC);
   }
 
   if ( Mptr->OCNL_LTG ) {
      termoutf("OCCASSIONAL LTG     : TRUE\n");
   }
 
   if ( Mptr->FRQ_LTG ) {
      termoutf("FREQUENT LIGHTNING  : TRUE\n");
   }
 
   if ( Mptr->CNS_LTG ) {
      termoutf("CONTINUOUS LTG      : TRUE\n");
   }
 
   if ( Mptr->CG_LTG ) {
      termoutf("CLOUD-GROUND LTG    : TRUE\n");
   }
 
   if ( Mptr->IC_LTG ) {
      termoutf("IN-CLOUD LIGHTNING  : TRUE\n");
   }
 
   if ( Mptr->CC_LTG ) {
      termoutf("CLD-CLD LIGHTNING   : TRUE\n");
   }
 
   if ( Mptr->CA_LTG ) {
      termoutf("CLOUD-AIR LIGHTNING : TRUE\n");
   }
 
   if ( Mptr->AP_LTG ) {
      termoutf("LIGHTNING AT AIRPORT: TRUE\n");
   }
 
   if ( Mptr->OVHD_LTG ) {
      termoutf("LIGHTNING OVERHEAD  : TRUE\n");
   }
 
   if ( Mptr->DSNT_LTG ) {
      termoutf("DISTANT LIGHTNING   : TRUE\n");
   }
 
   if ( Mptr->LightningVCTS ) {
      termoutf("L'NING W/I 5-10(ALP): TRUE\n");
   }
 
   if ( Mptr->LightningTS ) {
      termoutf("L'NING W/I 5 (ALP)  : TRUE\n");
   }
 
   if ( Mptr->VcyStn_LTG ) {
      termoutf("VCY STN LIGHTNING   : TRUE\n");
   }
 
   if ( Mptr->LTG_DIR[0] != '\0' ) {
      termoutf("DIREC. OF LIGHTNING : %s\n", Mptr->LTG_DIR);
   }
 
   i = 0;
   while( i < 3 && Mptr->ReWx[ i ].Recent_weather[0] != '\0' )
   {
      termoutf("RECENT WEATHER      : %s", Mptr->ReWx[i].Recent_weather);
 
      if ( Mptr->ReWx[i].Bhh != MAXINT ) {
         termoutf(" BEG_hh = %d",Mptr->ReWx[i].Bhh);
      }
      if ( Mptr->ReWx[i].Bmm != MAXINT ) {
         termoutf(" BEG_mm = %d",Mptr->ReWx[i].Bmm);
      }
 
      if ( Mptr->ReWx[i].Ehh != MAXINT ) {
         termoutf(" END_hh = %d",Mptr->ReWx[i].Ehh);
      }
      if ( Mptr->ReWx[i].Emm != MAXINT ) {
         termoutf(" END_mm = %d",Mptr->ReWx[i].Emm);
      }
 
      // strcat(string, "\n");
      termout(" ");
      i++;
   }
 
   if ( Mptr->minCeiling != MAXINT ) {
      termoutf("MIN VRBL_CIG (FT)   : %d\n",Mptr->minCeiling);
   }
   if ( Mptr->maxCeiling != MAXINT ) {
      termoutf("MAX VRBL_CIG (FT))  : %d\n",Mptr->maxCeiling);
   }
 
   if ( Mptr->CIG_2ndSite_Meters != MAXINT ) {
      termoutf("CIG2ndSite (FT)     : %d\n",Mptr->CIG_2ndSite_Meters);
   }
   if ( Mptr->CIG_2ndSite_LOC[0] != '\0' ) {
      termoutf("CIG @ 2nd Site LOC. : %s\n",Mptr->CIG_2ndSite_LOC);
   }
 
   if ( Mptr->PRESFR ) {
      termoutf("PRESFR              : TRUE\n");
   }
   if ( Mptr->PRESRR ) {
      termoutf("PRESRR              : TRUE\n");
   }
 
   if ( Mptr->SLPNO ) {
      termoutf("SLPNO               : TRUE\n");
   }
 
   if ( Mptr->SLP != (float) MAXINT ) {
      termoutf("SLP (hPa)           : %.1f\n", Mptr->SLP);
   }
 
   if ( Mptr->SectorVsby != (float) MAXINT ) {
      termoutf("SECTOR VSBY (MILES) : %.2f\n", Mptr->SectorVsby );
   }
 
   if ( Mptr->SectorVsby_Dir[ 0 ] != '\0' ) {
      termoutf("SECTOR VSBY OCTANT  : %s\n", Mptr->SectorVsby_Dir );
   }
 
   if ( Mptr->TS_LOC[ 0 ] != '\0' ) {
      termoutf("THUNDERSTORM LOCAT. : %s\n", Mptr->TS_LOC );
   }
 
   if ( Mptr->TS_MOVMNT[ 0 ] != '\0' ) {
      termoutf("THUNDERSTORM MOVMNT.: %s\n", Mptr->TS_MOVMNT);
   }
 
   if ( Mptr->GR ) {
      termoutf("GR (HAILSTONES)     : TRUE\n");
   }
 
   if ( Mptr->GR_Size != (float) MAXINT ) {
      termoutf("HLSTO SIZE (INCHES) : %.3f\n",Mptr->GR_Size);
   }
 
   if ( Mptr->VIRGA ) {
      termoutf("VIRGA               : TRUE\n");
   }
 
   if ( Mptr->VIRGA_DIR[0] != '\0' ) {
      termoutf("DIR OF VIRGA FRM STN: %s\n", Mptr->VIRGA_DIR);
   }
 
   for( i = 0; i < 6; i++ ) {
      if( Mptr->SfcObscuration[i][0] != '\0' ) {
         termoutf("SfcObscuration      : %s\n", &(Mptr->SfcObscuration[i][0]) );
      }
   }
 
   if ( Mptr->Num8thsSkyObscured != MAXINT ) {
      termoutf("8ths of SkyObscured : %d\n",Mptr->Num8thsSkyObscured);
   }
 
   if ( Mptr->CIGNO ) {
      termoutf("CIGNO               : TRUE\n");
   }
 
   if ( Mptr->Ceiling != MAXINT ) {
      termoutf("Ceiling (ft)        : %d\n",Mptr->Ceiling);
   }
 
   if ( Mptr->Estimated_Ceiling != MAXINT ) {
      termoutf("Estimated CIG (ft)  : %d\n",Mptr->Estimated_Ceiling);
   }
 
   if ( Mptr->VrbSkyBelow[0] != '\0' ) {
      termoutf("VRB SKY COND BELOW  : %s\n",Mptr->VrbSkyBelow);
   }
 
   if ( Mptr->VrbSkyAbove[0] != '\0' ) {
      termoutf("VRB SKY COND ABOVE  : %s\n",Mptr->VrbSkyAbove);
   }
 
   if ( Mptr->VrbSkyLayerHgt != MAXINT ) {
      termoutf("VRBSKY COND HGT (FT): %d\n",Mptr->VrbSkyLayerHgt);
   }
 
   if ( Mptr->ObscurAloftHgt != MAXINT ) {
      termoutf("Hgt Obscur Aloft(ft): %d\n",Mptr->ObscurAloftHgt);
   }
 
   if ( Mptr->ObscurAloft[0] != '\0' ) {
      termoutf("Obscur Phenom Aloft : %s\n",Mptr->ObscurAloft);
   }
 
   if ( Mptr->ObscurAloftSkyCond[0] != '\0' ) {
      termoutf("Obscur ALOFT SKYCOND: %s\n",Mptr->ObscurAloftSkyCond);
   }
 
   if ( Mptr->NOSPECI ) {
      termoutf("NOSPECI             : TRUE\n");
   }
 
   if ( Mptr->LAST ) {
      termoutf("LAST                : TRUE\n");
   }
 
   if ( Mptr->synoptic_cloud_type[ 0 ] != '\0' ) {
      termoutf("SYNOPTIC CLOUD GROUP: %s\n",Mptr->synoptic_cloud_type);
   }
 
   if ( Mptr->CloudLow != '\0' ) {
      termoutf("LOW CLOUD CODE      : %c\n",Mptr->CloudLow);
   }
 
   if ( Mptr->CloudMedium != '\0' ) {
      termoutf("MEDIUM CLOUD CODE   : %c\n",Mptr->CloudMedium);
   }
 
   if ( Mptr->CloudHigh != '\0' ) {
      termoutf("HIGH CLOUD CODE     : %c\n",Mptr->CloudHigh);
   }
 
   if ( Mptr->SNINCR != MAXINT ) {
      termoutf("SNINCR (INCHES)     : %d\n",Mptr->SNINCR);
   }
 
   if ( Mptr->SNINCR_TotalDepth != MAXINT ) {
      termoutf("SNINCR(TOT. INCHES) : %d\n",Mptr->SNINCR_TotalDepth);
   }
 
   if ( Mptr->snow_depth_group[ 0 ] != '\0' ) {
      termoutf("SNOW DEPTH GROUP    : %s\n",Mptr->snow_depth_group);
   }
 
   if ( Mptr->snow_depth != MAXINT ) {
      termoutf("SNOW DEPTH (INCHES) : %d\n",Mptr->snow_depth);
   }
 
   if ( Mptr->WaterEquivSnow != (float) MAXINT ) {
      termoutf("H2O EquivSno(inches): %.2f\n",Mptr->WaterEquivSnow);
   }
 
   if ( Mptr->SunshineDur != MAXINT ) {
      termoutf("SUNSHINE (MINUTES)  : %d\n",Mptr->SunshineDur);
   }
 
   if ( Mptr->SunSensorOut ) {
      termoutf("SUN SENSOR OUT      : TRUE\n");
   }
 
   if ( Mptr->hourlyPrecip != (float) MAXINT ) {
      termoutf("HRLY PRECIP (INCHES): %.2f\n",Mptr->hourlyPrecip);
   }
 
   if( Mptr->precip_amt != (float) MAXINT) {
      termoutf("3/6HR PRCIP (INCHES): %.2f\n", Mptr->precip_amt);
   }
 
   if( Mptr->Indeterminant3_6HrPrecip ) {
      termoutf("INDTRMN 3/6HR PRECIP: TRUE\n");
   }
 
   if( Mptr->precip_24_amt !=  (float) MAXINT) {
      termoutf("24HR PRECIP (INCHES): %.2f\n",
         Mptr->precip_24_amt);
   }
 
   if ( Mptr->Indeterminant_24HrPrecip ) {
      termoutf("INDTRMN 24 HR PRECIP: TRUE\n");
   }
 
   if ( Mptr->Temp_2_tenths != (float) MAXINT ) {
      if (use_fahrenheit == IDC_TEMP_DEGSF)
         termoutf("Temp (degsF/10)     : %.1f\n",c2f(Mptr->Temp_2_tenths));
      else
         termoutf("Temp (degsC/10)     : %.1f\n",Mptr->Temp_2_tenths);
   }
 
   if ( Mptr->DP_Temp_2_tenths != (float) MAXINT ) {
      if (use_fahrenheit == IDC_TEMP_DEGSF)
         termoutf("Dewpoint (degsF/10) : %.1f\n",c2f(Mptr->DP_Temp_2_tenths));
      else
         termoutf("Dewpoint (degsC/10) : %.1f\n",Mptr->DP_Temp_2_tenths);
   }
 
   if ( Mptr->maxtemp !=  (float) MAXINT) {
      if (use_fahrenheit == IDC_TEMP_DEGSF)
         termoutf("MAX TEMP (degsF)    : %.1f\n", c2f(Mptr->maxtemp));
      else
         termoutf("MAX TEMP (degsC)    : %.1f\n", Mptr->maxtemp);
   }
 
   if ( Mptr->mintemp !=  (float) MAXINT) {
      if (use_fahrenheit == IDC_TEMP_DEGSF)
         termoutf("MIN TEMP (degsF)    : %.1f\n", c2f(Mptr->mintemp));
      else
         termoutf("MIN TEMP (degsC)    : %.1f\n", Mptr->mintemp);
   }
 
   if ( Mptr->max24temp !=  (float) MAXINT) {
      if (use_fahrenheit == IDC_TEMP_DEGSF)
         termoutf("24HrMAXTMP (degsF)  : %.1f\n", c2f(Mptr->max24temp));
      else
         termoutf("24HrMAXTMP (degsC)  : %.1f\n", Mptr->max24temp);
   }
 
   if ( Mptr->min24temp !=  (float) MAXINT) {
      if (use_fahrenheit == IDC_TEMP_DEGSF)
         termoutf("24HrMINTMP (degsF)  : %.1f\n", c2f(Mptr->min24temp));
      else
         termoutf("24HrMINTMP (degsC)  : %.1f\n", Mptr->min24temp);
   }
 
   if ( Mptr->char_prestndcy != MAXINT) {
      termoutf("CHAR PRESS TENDENCY : %d\n", Mptr->char_prestndcy );
   }
 
   if ( Mptr->prestndcy != (float) MAXINT) {
      termoutf("PRES. TENDENCY (hPa): %.1f\n",
         Mptr->prestndcy );
   }
 
   if ( Mptr->PWINO ) {
      termoutf("PWINO               : TRUE\n");
   }
 
   if ( Mptr->PNO ) {
      termoutf("PNO                 : TRUE\n");
   }
 
   if ( Mptr->CHINO ) {
      termoutf("CHINO               : TRUE\n");
   }
 
   if ( Mptr->CHINO_LOC[0] != '\0' ) {
      termoutf("CHINO_LOC           : %s\n",Mptr->CHINO_LOC);
   }
 
   if ( Mptr->VISNO ) {
      termoutf("VISNO               : TRUE\n");
   }
 
   if ( Mptr->VISNO_LOC[0] != '\0' ) {
      termoutf("VISNO_LOC           : %s\n",Mptr->VISNO_LOC);
   }
 
   if ( Mptr->FZRANO ) {
      termoutf("FZRANO              : TRUE\n");
   }
 
   if ( Mptr->TSNO ) {
      termoutf("TSNO                : TRUE\n");
   }
 
   if ( Mptr->DollarSign) {
      termoutf("DOLLAR $IGN INDCATR : TRUE\n");
   }
 
   if ( Mptr->horiz_vsby[ 0 ] != '\0' ) {
      termoutf("HORIZ VISIBILITY    : %s\n",Mptr->horiz_vsby);
   }
 
   if ( Mptr->dir_min_horiz_vsby[ 0 ] != '\0' ) {
      termoutf("DIR MIN HORIZ VSBY  : %s\n",Mptr->dir_min_horiz_vsby);
   }
 
   if ( Mptr->CAVOK ) {
      termoutf("CAVOK               : TRUE\n");
   }
 
 
   if( Mptr->VertVsby != MAXINT ) {
      termoutf("Vert. Vsby (meters) : %d\n", Mptr->VertVsby );
   }
 
 /*
   if( Mptr->charVertVsby[0] != '\0' )
      sprintf(temp, "Vert. Vsby (CHAR)   : %s\n",
                  Mptr->charVertVsby );
 */
 
   if ( Mptr->QFE != MAXINT ) {
      termoutf("QFE                 : %d\n", Mptr->QFE);
   }
 
   if ( Mptr->VOLCASH ) {
      termoutf("VOLCANIC ASH        : TRUE\n");
   }
 
   if ( Mptr->min_vrbl_wind_dir != MAXINT ) {
      termoutf("MIN VRBL WIND DIR   : %d\n",Mptr->min_vrbl_wind_dir);
   }
   if ( Mptr->max_vrbl_wind_dir != MAXINT ) {
      termoutf("MAX VRBL WIND DIR   : %d\n",Mptr->max_vrbl_wind_dir);
   }
}

