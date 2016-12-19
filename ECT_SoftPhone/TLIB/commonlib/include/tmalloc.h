/*
 * $Id: tmalloc.h,v 1.16 2003/04/24 00:39:29 epi Exp $
 */

#ifndef _TMALLOC_H
#define _TMALLOC_H

#include "com_types.h"

#ifdef __cplusplus
extern "C" {
#endif

ComENTRY char *tmalloc(int length);
ComENTRY void *tcalloc(int length, int elem_size);

/*
 * The following 3 functions are NULL-safe:
 */
ComENTRY char *tstrdup(const char *string);
ComENTRY char *tstrncpy(char *dst, const char *src, int len);
ComENTRY char *tmemdup(const char *value, int length);

/*
 * Exception handler will be called whenever attempt to allocate memory fails
 * (with requested length as parameter); it should return 0 if the problem
 * is believed to be corrected (and it makes sense to try again), or -1
 * otherwise (then abort will be called immediately). All other values are
 * reserved for future extensions.
 */
ComENTRY int (* tmalloc_set_exc_handler
                 (int (*handler)(int len_requested, const char *func_name))
             )(int, const char *);
/*
 * Case-insensitive compare: by default underscore '_' is treated as upper-case
 * version of dash/minus '-', but it can be changed by calling tstrcasecmp_init
 * (where every 2*j-th character in jlist will be converted into (2*j+1)-th
 * before comaprison; i.e. default rule is "AaBbCc...XxYyZz_-"):
 */
ComENTRY int tstrcasecmp(const char *s1, const char *s2);
ComENTRY void tstrcasecmp_init(const char *jlist);

/*
 * Safe string compare: doesn't crash on NULL strings (such strings is assumed
 * to be less than any non-NULL string)
 */
ComENTRY int tstrsafecmp(const char *s1, const char *s2);

/*
 * 'Q' set of functions support "quoted" strings, where all quote characters Q 
 * are masked, i.e. represented as \Q (usually Q='"', but it may be any other 
 * character as well)
 */
ComENTRY int tstrQlen(const char *str, char Q);/* length after Qs are masked */
ComENTRY char *tstpQcpy(char *dest, const char *src, char Q); /* mask all Qs */
ComENTRY char *tstpQunmask(char *dest, const char *src, const char *src_end);
/*
 * Misc:
 */
ComENTRY int tstrlen_itoa(int i, int radix);/* length of i converted to text */

#ifdef __cplusplus
}
#endif
#endif /* _TMALLOC_H */

