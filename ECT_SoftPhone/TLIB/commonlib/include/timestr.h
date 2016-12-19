/*
 * $Id: timestr.h,v 1.11 2003/01/31 23:43:41 epi Exp $
 */

#ifndef _TIMESTR_H
#define _TIMESTR_H

#include <time.h>

#ifndef _WIN32
#include <sys/time.h>
#else
#include <windows.h>
#include <sys/timeb.h>
#endif
#include "com_types.h"

#ifdef __cplusplus
extern "C" {
#endif

ComENTRY struct timeval usectime(void);
ComENTRY struct timeval usectime_ex(ulong timeout_msecs);
#ifdef _WIN32
  ComENTRY void usectime_p(struct timeval *tv);
#else
# define usectime_p(_stv) gettimeofday((_stv),0)
#endif

ComENTRY char *date__str(void);
ComENTRY char *time__str(void);

ComENTRY char *time__stamp(void);
ComENTRY char *time__stamp_from_timeval(struct timeval ptv);

ComENTRY int time__stamp_UTC(int UTC); /* UTC=1 set, UTC=0 reset to local   */
                                       /* function returns previous setting */
/*
 * The following structure and functions are OBSOLETE and should NOT be used:
 */
struct _time_value {
    int tv_sec;
    int tv_usec;
};
typedef struct _time_value time_val_t;

void get_usec_time(time_val_t *);
ComENTRY char *time_stamp_str(void);

#ifdef __cplusplus
}
#endif
#endif /* _TIMESTR_H */

