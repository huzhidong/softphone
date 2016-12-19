/*
 * $Id: cmntypes.h,v 1.5 1997/09/30 16:36:29 and Exp $
 */

#ifndef _CMNTYPES_H
#define _CMNTYPES_H

#define CONN_ID_SIZE 	8

typedef struct {
    unsigned char _d[CONN_ID_SIZE];
} TConnectionID;

#define CONN_ID_CMP(a,b) (memcmp(&(a), &(b), CONN_ID_SIZE))
#define NO_CONN_ID	{{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'}}

#endif

