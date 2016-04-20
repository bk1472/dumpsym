#ifndef __DEF_H__
#define __DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include	"symtypes.h"

#define FATAL   				1
#define HEX     				0
#define OCTAL   				1
#define DECIMAL 				2

#define TROUBLE 				-1L
#define MAXLEN  				512

#define	MAX_BIN_SIZE	0x06400000	/* 100M byte	for binary image        */
#define MAX_SYM_BUFF	0x01E00000	/*  30M byte for symbol strings & dwarf */
#define MAX_SYM_COUNT	  0x300000	/* Maximum number of symbols            */
#define MAX_DWARF_PKT	   0x20000 	/* No dwarf packets for debug           */

#define	MAX_VER_LEN            128	/* Maximum length of version field      */
#define	PRINT(x...)		if (verbose == 1) { printf(x); fflush(stdout); usleep(100);}

#define DEBUG			1


extern char				versionBuf[MAX_VER_LEN];	/* Buffer space for version			*/
extern char				tmStampBuf[MAX_VER_LEN];
extern unsigned int		dwarfLst[2*MAX_DWARF_PKT];	/* Pointer to dwarf pkts*/
extern unsigned int		nDwarfLst;					/* Number of dwarf pkts	*/

extern ulong_t			verbose;
extern ulong_t			debug_level;


#ifdef __cplusplus
}
#endif

#endif/*__DEF_H__*/
