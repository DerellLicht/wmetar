//  prototypes ported from local.h

//lint -esym(760, FALSE, TRUE)

#define FALSE  0
#define TRUE   1
#define MAXINT       INT_MAX           /* maximum integer */

#define MAX_METAR_LEN   2048
 
//****************************************************************************
//  debug: message-reporting data
//****************************************************************************

#define  DBG_VERBOSE       0x01
#define  DBG_WINMSGS       0x02
#define  DBG_RX_DEBUG      0x04
#define  DBG_CTASK_TRACE   0x08
#define  DBG_POLLING       0x20
#define  DBG_ETHERNET      0x40

extern unsigned dbg_flags ;
//****************************************************************************

typedef unsigned short int MDSP_BOOL;

//  wmetar.cpp
extern int use_fahrenheit ;
void termout(char *outstr);
int termoutf(const char *fmt, ...);
void process_metar_string(char *metar_str);

//  stspack2.c
int nisalnum(char *, int);
int nisalpha(char *, int);
int nisdigit(char *, int);

//  stspack3.c
char *nxtalpha(char *);

//  antoi.c
int antoi(char *, int);

//  charcmp.c
MDSP_BOOL charcmp( char *, char * );

//  station_name.c
typedef struct station_data_s {
   char state[3] ;
   char station[17] ;
   char icao[5] ;
   char longitude[10] ;
   char latitude[10] ;
   unsigned elevation ;
} station_data_t, *station_data_p ;

station_data_p lookup_station_name(char *icao);

//  fracpart.cpp
float fracPart( char *string );

