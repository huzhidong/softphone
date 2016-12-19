/*
 * $Id: conn_fdset.h /main/9 31-Jan-2005.15:59:33 PST tikin $
 */
#ifndef _CONN_FDSET_H
#define _CONN_FDSET_H

/* 
 * Supported platforms:
 *
 *   Solaris = defined(__sun)
 *     defined(_LP64)       -- 64bit (Solaris 2.7+) FD_SETSIZE = 65536
 *     defined(__SunOS_5_6) -- 32bit (Solaris 2.6)  FD_SETSIZE =  1024
 *     else                 -- 32bit (Solaris 2.7+) FD_SETSIZE -> 4096
 *
 *   AIX = defined(_AIX) FD_SETSIZE = 32767 (AIX 4.3.2+)
 *
 *   HP-UX = defined(__hpux) or defined(__HP_aCC) FD_SETSIZE -> 4096
 *   OSF (Digital UNIX, True64) = defined(__osf__) FD_SETSIZE = 4096
 *
 *   WinNT = defined(_WIN32) FD_SETSIZE -> 4096
 *   Linux = defined(__linux) FD_SETSIZE = 1024 (can't be changed)
 */
#if defined __sun
/* for solaris get FD_SETSIZE from limits */
#include <limits.h>
#endif

#ifndef FD_SETSIZE
# if defined(__hpux) || defined(_WIN32)
#   define FD_SETSIZE 4096
# elif defined(__sun) && !defined(_LP64) && !defined(__SunOS_5_6)
#   define FD_SETSIZE 4096               
# endif                                  
#endif /* notdef FD_SETSIZE */


/* 
 * Make sure 'fd_set' and 'struct timeval' are both defined:
 */
#ifdef _WIN32            /* Internally in CommonLib we need "winsock2.h",  */
# ifndef _WINSOCKAPI_    /* but it's Ok to use "winsock.h" too (structures */
#   include <winsock2.h> /* are the same, only new functions are missing & */
# endif                  /* FD_SET macro is a bit broken)                  */
#else
# include <sys/types.h>
# include <sys/time.h>
#endif
#ifdef _AIX              /* Non-standard header is required on AIX 4.x for */
# include <strings.h>    /* FD_ZERO to be correct (bzero function defined) */
#endif
/*
 * Parameter for FD_SET/CLR has different types on Unix and Windows, so the
 * following definitions added to make possible platform-independent code:
 */
#ifdef _WIN32
  typedef unsigned int SOCKET_TYPE;
# define SOCKET_TYPE_UNDEF ~0
#else
  typedef int SOCKET_TYPE;
# define SOCKET_TYPE_UNDEF -1
#endif
/*
 * Custom FD_COPY improves performance on Windows (it doesn't make sense to
 * copy elements of fd_array that are not used and may be not initialized):
 */
#ifdef _WIN32
#define FD_FAST_COPY(_from,_to) do {                 \
    u_int __i;                                       \
    (_to)->fd_count = (_from)->fd_count;             \
    for (__i=0; __i < (_from)->fd_count; __i++)      \
      (_to)->fd_array[__i] = (_from)->fd_array[__i]; \
  } while(0)
#define FD_COUNT(_fdset) (_fdset)->fd_count
#else
#define FD_FAST_COPY(_from,_to) *(_to) = *(_from)
#endif
#endif /* _CONN_FDSET_H */

