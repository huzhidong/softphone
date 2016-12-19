/*
 * $Id: conn_udp.h /main/1 14-Jun-2004.12:37:41 PST tikin $
 */

#ifndef __CONN_UDP_H
#define __CONN_UDP_H
/**
 * Copyright (c) 2004 Genesys Telecommunications Labs, Inc, All Rights Reserved
 * File: conn_udp.h
 * Project: Genesys Common library
 * Creation date: Mar 22 2004
 * Description:
 *  Common library UDP interface
 */

#include <connection.h>
#ifdef __cplusplus
extern "C"{
#endif
/**
 * Retrive address for received udp packet
 * \param req  - received request
 * \param addr - result address
 * \return 0 - succes, -1 or invalid arguments
 */
int conn_udp_get_addr(struct request* req,struct sockaddr_in* addr);
/**
 * Retrive remote address for current exception. 
 * For valid result function can be invoked only from exception handler.
 * \param fd   - socket descriptor
 * \param addr - result address
 * \return 0 - succes, -1 on invalid descriptor/addrs
 * \note - UDP socket can generate multiple exception, connection will not be closed, and will be in valid state
 * \note - In case when address unknown, function will return 0 and set addr->sin_family to AF_UNSPEC
 * \note - address available only inside exception handler
 */
int conn_get_exception_addr(int fd,struct sockaddr_in* addr);

/**
 * Send data to the udp connection
 * \param fd   - existing udp connection
 * \param data - data to send
 * \param size - size of data
 * \param addr - destination addrss
 * \return 0 - succes, -1 or invalid arguments
 */
int conn_sendto(int fd,const void* data,int size,struct sockaddr_in* addr);

/**
 * Create new udp connection
 * \param local  - optional local IP address, If not present, port will be allocated dynamically
 * \param remote - optoinal remote IP address. In case when cpecified, socket will be connected to this address
 *                 (See connect function description for details)
 * \param exception_handler - exception handler
 * \param req_handler - incomming packet handler
 * \param input_queue - queue where data will stored
 * \return 0 - succes, -1 or invalid arguments, or binding error
 */
int conn_create_udp_connection(	struct sockaddr_in* local,
								struct sockaddr_in* remote,
								int (*exception_handler)(int fd),
								conn_request_handler_t req_handler,struct conn_queue* input_queue);
#ifdef __cplusplus
}
#endif
#endif
