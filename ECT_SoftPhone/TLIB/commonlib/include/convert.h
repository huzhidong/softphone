/*
 * $Id: convert.h,v 1.9 2002/06/20 00:26:34 epi Exp $
 */

#ifndef _CONVERT_H
#define _CONVERT_H

#include "cmntypes.h"
#include "com_types.h"

#ifdef __cplusplus
extern "C" {
#endif

ComENTRY char *connid_to_str    (TConnectionID connid),
              *connid_to_decimal(TConnectionID connid);

ComENTRY TConnectionID str_to_connid    (const char *str),
                       decimal_to_connid(const char *str);

#ifdef __cplusplus
}
#endif

#endif
