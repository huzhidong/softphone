/*
 * $Id: addproto.h /main/9 14-Jun-2004.12:42:20 PST tikin $
 */

#ifndef _ADDPROTO_H
#define _ADDPROTO_H

#include "com_types.h"
#include "xkvlist.h"

#define ADDP_MAX_TIMEOUT_SEC 3600 /* 1 hour */
#define ADDP_XOFF_MAX_TIMEOUT 3600 /* 1 hour  #78833*/

extern struct protocol addp_protocol;

#ifdef __cplusplus
extern "C" {
#endif

int addp_detect      (struct connection *cp, uchar *buf, int len),
    addp_set_protocol(struct connection *cp, uchar *buf, int len);

int addp_configure(const char *server_name); /* obsolete, not used anymore */

int addp_xconfig(struct connection *cp, XKVList *proto_params);

#define ADDP_KEYLIST "`addp-timeout`addp-remote-timeout`addp-trace;"

int addp_xoff(int fd, int timeout_sec);
int addp_xon (int fd);

#ifdef __cplusplus
}
#endif
#endif /* _ADDPROTO_H */

