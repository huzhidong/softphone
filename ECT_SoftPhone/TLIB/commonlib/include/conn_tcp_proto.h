/*
 * $Id: conn_tcp_proto.h /main/1 14-Jun-2004.12:37:34 PST tikin $
 */

#ifndef __CONN_TCP_PROTO_H
#define __CONN_TCP_PROTO_H
#include <connection.h>
/**
 * TCP protocol
 * Simple stream protocol without headers encoding
 * Recommended for use as underlaying protocol for TCP, UDP, HTTP, Telnet implementations, etc..
 */ 
#ifdef __cplusplus
extern "C" {
#endif
extern struct protocol conn_tcp_protocol;
#ifdef __cplusplus
}
#endif
#endif

