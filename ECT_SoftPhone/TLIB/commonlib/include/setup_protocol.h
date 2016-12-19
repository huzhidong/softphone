/*
 * $Id: setup_protocol.h,v 1.15 2002/07/30 21:05:29 epi Exp $
 */

#ifndef _SETUP_PROTOCOL_H_
#define _SETUP_PROTOCOL_H_

#include "connection.h"
#include "config.h"
#include "xkvlist.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct protocol setup_protocol;

ComENTRY int setup_client_protocol_configure(const char *server_name),
             setup_server_protocol_configure(const char *server_name);

ComENTRY int setup_protocol_from_xkvlist(struct connection *cp, 
                                         XKVList *proto_params);
/*
 * MultiThreaded application should use the following function (which is also
 * available in non-MTSafe version of connection layer):
 */
ComENTRY int setup_protocol_by_fd(int fd, XKVList *proto_params);
/*
 * Static variable to pass parameters from setup_client_protocol_configure
 * to conn_connect[_XXX] - obviously, not MT-Safe:
 */
extern XKVList *conn_default_proto_params;
ComENTRY XKVList *conn_get_default_proto_params(void);
/*
 * Function that may be used to change protocol on-the-fly:
 */
int setup_proto_packet_length(struct connection *cp,
                              unsigned char *buffer, int length);
#ifdef __cplusplus
}
#endif
#endif /* _SETUP_PROTOCOL_H_ */

