//  commented-out Synoptic code moved from main() to here

#ifdef SYNOPTIC
 
char *BldSynop( Decoded_METAR * , char * );
#endif
 
#ifdef OLDSTUFF
   static char *synopRTRN = NULL;
   char bltn_prefix[20];
      /************************************************/
      /*  Convert Decoded METAR into Synoptic format  */
      /************************************************/
      printf("Just after call to prtDMETR\n");
 
      sprintf( bltn_prefix, "AAXX YYGGi##," );
      synopRTRN = BldSynop( Mptr, bltn_prefix );
      printf("After BldSynop, SynopRep =:\n%s\n",synopRTRN);
            /**********************************************************/
            /*-- ENCODE SECTION 0 OF THE SYNTHETIC SYNOPTIC REPORT ---*/
            /**********************************************************/
      printf("Just before call to Sec0MeSM\n");
 
      if( (synopRTRN = Sec0MeSm( Mptr )) == NULL )
         printf("Sec0MeSm returned a NULL pointer\n");
      else
         printf("After Sec0MeSm: %s\n",synopRTRN);
 
            /**********************************************************/
            /*-- ENCODE SECTION 1 OF THE SYNTHETIC SYNOPTIC REPORT ---*/
            /**********************************************************/
      if( synopRTRN != NULL )
         synopRTRN = Sec1MeSm( Mptr,synopRTRN );
            printf("After Sec1MeSm: %s\n",synopRTRN);
 
            /**********************************************************/
            /*-- ENCODE SECTION 3 OF THE SYNTHETIC SYNOPTIC REPORT ---*/
            /**********************************************************/
 
      if( synopRTRN != NULL )
         synopRTRN = Sec3MeSm( Mptr,synopRTRN );
            printf("After Sec3MeSm: %s\n",synopRTRN);
 
            /**********************************************************/
            /*-- ENCODE SECTION 5 OF THE SYNTHETIC SYNOPTIC REPORT ---*/
            /**********************************************************/
 
      if( synopRTRN != NULL )
         synopRTRN = Sec5MeSm( Mptr,synopRTRN);
            printf("After Sec5MeSm: %s\n",synopRTRN);
 
            /**********************************************************/
            /*-- PRINT THE ENCODED SYNTHETIC SYNOPTIC REPORT ---------*/
            /**********************************************************/
 
      if( synopRTRN != NULL ) {
         printf("\n\nOutput Synoptic Report:  %s\n\n",synopRTRN);
         free( synopRTRN);
      }
 
#endif
 

