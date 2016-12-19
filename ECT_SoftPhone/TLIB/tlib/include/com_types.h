/*
 * $Id: com_types.h,v 1.12 2002/10/08 18:41:57 epi Exp $
 * -Id: ttypes.h,v 1.6 1997/08/16 00:02:01 lexa Exp -
 */
#ifndef _COM_TYPES_H_
#define _COM_TYPES_H_
/*
 *   Encapsulation of "standard" types
 */
#include <sys/types.h>

#if !defined(__osf__) && !defined(_AIX)
  typedef unsigned char uchar;
# if !defined(__SVR4) && !defined(_SYS_TYPES_H)
    typedef unsigned long ulong;
# endif
#endif
#ifdef _WIN32
  typedef unsigned int   uint;
  typedef unsigned short ushort;
#endif
#ifdef _NO_LONG_LONG

  typedef struct {unsigned char _d[8];}	  ulong64_t;

#else

#if defined(__osf__)
  typedef unsigned long	     ulong64_t;
#elif defined(_WIN32)
  typedef unsigned __int64   ulong64_t;
#else
  typedef unsigned long long ulong64_t;
#endif

#endif /* _NO_LONG_LONG */

#define TABLE_SIZE(a)      (sizeof(a) / sizeof(*a))
#ifndef STRUCT_OFFSET
#define STRUCT_OFFSET(t,f) ((unsigned)(&(((t *)NULL)->f)))
#endif

#ifndef extern_C               /* OSF C++ compiler requires additional */
# ifdef __cplusplus            /* extern"C" before function definition */
#   define extern_C extern "C" /* if one of parameters is callback;    */
# else                         /* doesn't hurt on other platforms      */
#   define extern_C
# endif
#endif

#if defined(_WIN32) && defined(_DLL) && defined(ComENTRY_LOCAL)
# define ComENTRY __declspec(dllexport)
#else
# define ComENTRY
#endif
#endif /* _COM_TYPES_H_ */

