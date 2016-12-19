/*
 * $Id: conn_socket.h,v 1.14 2003/04/24 00:44:44 epi Exp $
 */
#ifndef _CONN_SOCKET_H
#define _CONN_SOCKET_H

/* Supported platforms:
 *
 *   Solaris = defined(__sun) &&  defined(__SVR4)
 *   SunOS   = defined(__sun) && !defined(__SVR4)
 *
 *   AIX                        = defined(_AIX)
 *   OSF (Digital UNIX, True64) = defined(__osf__)
 *   HP-UX = defined(__hpux) or defined(__HP_aCC)
 *
 *   WinNT = defined(_WIN32)
 *   Linux = defined(__linux)
 */
#include "conn_fdset.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#  include <sys/timeb.h>
#else /* not WIN32, i.e. UNIX */

#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h> /* umask() defined here */
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#ifndef _OS2
# include <sys/un.h>
# include <sys/time.h>
#endif
#include <netdb.h> /* gethostbyname */
#include <fcntl.h>
#include <errno.h>
#ifdef _AIX
# include <sys/select.h>
#endif

#endif /* not WIN32 */

#ifdef __sun
/*
 * On Solaris, select(3C) man page says: "The poll(2) function is preferred
 * over this function", and, as you can guess from section names, 'select'
 * is a function that's implemented by using 'poll' system call (while on
 * other platforms 'select' is a system call by itself):
 */
#define USE_POLL_INSTEAD_SELECT
#endif
#ifdef USE_POLL_INSTEAD_SELECT /* may be used on other Unix platforms too */
#include <sys/poll.h>

#define POLL_SET(_fd,_pollfds,mask)   ((_pollfds[_fd].events |= (mask)) ? \
                    (_pollfds[_fd].fd = _fd) : (_pollfds[_fd].fd = -1))

#define POLL_CLEAR(_fd,_pollfds,mask)  ((_pollfds[_fd].events &= ~(mask)) ? \
                      (_pollfds[_fd].fd = _fd) : (_pollfds[_fd].fd = -1))
#endif

#if defined(__linux) || defined(_AIX43)
  typedef socklen_t  sock_addr_len_t; /* POSIX standard */
#elif defined(_AIX)
  typedef size_t sock_addr_len_t; /* AIX versions 4.1 and 4.2 use size_t */
#else                             /* for specifying sockaddr_in length;  */
  typedef int sock_addr_len_t;    /* on all other platform it's int      */
#endif
/*---------------------------------------------------------------------------*/
#if defined(_WIN32) || defined(_OS2)

#define SOCKET_READ(A, B, C)	recv(A, (char *)(B), C, 0)
#define SOCKET_WRITE(A, B, C)	send(A, (const char *)(B), C, 0)
#ifdef _OS2
# define SOCKET_CLOSE(A)	soclose(A)
#else
# define SOCKET_CLOSE(A)	closesocket(A)
#endif
#define IS_INVALID_SOCKET(X)    (X) == INVALID_SOCKET
#define GET_SOCKET_ERROR        WSAGetLastError()
#define CONN_EINTR              WSAEINTR
#define CONN_EBADF              WSAENOTSOCK
#define CONN_EINPROGRESS        WSAEWOULDBLOCK
#define CONN_EWOULDBLOCK        WSAEWOULDBLOCK

#else /* UNIX */

#define SOCKET_READ(A, B, C)	read(A, B, C)
#define SOCKET_WRITE(A, B, C)	write(A, B, C)
#define SOCKET_CLOSE(A)		close(A)

#define IS_INVALID_SOCKET(X)    (X) < 0
#define GET_SOCKET_ERROR        errno
#define CONN_EINTR              EINTR
#define CONN_EBADF              EBADF
#define CONN_EINPROGRESS        EINPROGRESS
#define CONN_EWOULDBLOCK        EAGAIN /* == EWOULDBLOCK */

#endif
#endif /* _CONN_SOCKET_H */
