/*
 * $Id: cmnlog.h,v 1.7 2002/06/20 00:45:05 epi Exp $
 */

#ifndef _CMNLOG_H_
#define _CMNLOG_H_

#include <stdarg.h>
#include "com_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _GENESYS_COMMON_MESSAGES_HEADER

#define GCTI_ADDP_NO_RESPONSE_FROM_SOCKET 7041
    /* Socket [%d] not responding (%d msec), remote socket [%d] */
#define GCTI_INTERNAL 9999

#endif /* _GENESYS_COMMON_MESSAGES_HEADER */

ComENTRY int comlib_printf (int msgId, const char *fmt, ...),
             comlib_vprintf(int msgId, const char *fmt, va_list ap);
/*
 * default implementation = f[v]printf(stderr, msgFmt, ...)
 */

#define thru_comlib ((void*)0) /* <- pseudostream used to redirect output of */
                               /* various print functions thru comlib_printf */
/*---------------------------------------------------------------------------*/
int comlib_fprintf(void *stream, const char *fmt, ...); /* internal function */

typedef int (*comlib_print_proc_t)(void *stream, int msgId, 
                             const char *msgFmt, va_list ap);
/* return value should be compatible with fprintf
 *
 * To disable output, call the following function with print_func=NULL:
 */
ComENTRY int
  comlib_set_print_func(void *stream, comlib_print_proc_t print_func);

ComENTRY const char *commonlib_get_version_info(void);

#ifdef __cplusplus
}
#endif
#endif /* _CMNLOG_H_ */

