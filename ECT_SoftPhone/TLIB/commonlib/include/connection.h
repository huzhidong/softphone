/*
 * $Id: connection.h /main/94 15-Oct-2003.16:37:01 PST tikin $
 */

#ifndef _TCONNECTION_H
#define _TCONNECTION_H
#define TCONNECTION_VERSION 70200 /* version 7.0.200+ */

#include "conn_fdset.h" /* fd_set, struct timeval & FD_SETSIZE */
#include "com_types.h"  /* defines standard types and ComENTRY */
#include "xkvlist.h"
#include "kvlist.h"

#define MAXPACKETLENGTH (1024*16)
#define MAXDATALENGTH (MAXPACKETLENGTH - 4)

struct request {
  unsigned char *req_data;
  int req_length;
  int req_socket;
  unsigned long req_timestamp;
  struct request *req_next;
  struct request *req_prev;
};
struct conn_queue {
  struct request *q_head;
  struct request *q_tail;
};
                   /* Public access to connection layer internals is not */
struct connection; /* available anymore; use conn_intern.h header if you */
                   /* really need it (and know what you're doing)        */

/**
 * Reference to the multithreaded version of library
 * \return 1
 * \note - functions is not defined in not multithreaded version of library
 */
ComENTRY int conn_multithreaded(void);


struct protocol {
  int (*proto_init)(struct connection *cp);
  int (*proto_dispose)(struct connection *cp);
  int (*proto_packet_length)(struct connection *cp,
			     unsigned char *buffer, int length);
  int (*proto_process_input)(struct connection *cp,
		 unsigned char *buffer, int length,
  		 unsigned char **result_buffer, int *result_buffer_length);
  int (*proto_process_output)(struct connection *cp,
                 unsigned char *buffer, int length, 
                 unsigned char **result_buffer, int *result_buffer_length);
  int (*proto_configure)(struct connection *cp, XKVList *proto_param);
/*
 * Replacement for proto_process_output - first funstion return output length,
 * second one copies data (or part of it) into provided buffer:
 */
  int (*proto_output_length)(struct connection *cp,
                        unsigned char *orig_buffer, int orig_length);
  int (*proto_output_copy)(struct connection *cp,
                      unsigned char *orig_buffer, int orig_length,
                      unsigned char *dest_buffer, int orig_offset, int len);
  int pkt_header_len;
};

#ifdef __cplusplus
extern "C" {
#endif

ComENTRY int conn_startup (void);

ComENTRY int conn_adjust_rlimit(void);

/**
 * Configure various parameters of communication layer
 * \param app_name - application name
 * \param options  - application options
 * \param anex     - user_properties
 * \param reserved - reserved should be zero
 * \note - function called automatically for Genesys server applications.
 */
ComENTRY void conn_configure(const char* app_name,TKVList* options,TKVList* anex,const void* reserved);

ComENTRY void conn_cleanup(void);
     
enum conn_global_params {
  CONN_PARAM_CLOSE_AT_EXCEPT   = 1, /* values: true(1)/false(0), default: 1 */
  CONN_PARAM_MAX_SELECT_TOUT   = 2, /* values: timeout in msecs, default: 0 */
  CONN_PARAM_BKGND_TIMERS_TOUT = 3, /* values: timeout in msecs, default: 0 */
  CONN_PARAM_MAX
};
ComENTRY int conn_set_global_param(enum conn_global_params param, long value);

ComENTRY void conn_set_max_timeout(unsigned long timeout);
ComENTRY void conn_set_max_packet_length(int); /* obsolete, does nothing now */
ComENTRY                                            /* returns no. of blocks */
  int conn_set_buffer_cache_limit(int max_blocks);  /* currenctly allocated  */
#define CONN_DEFAULT_CACHE_LIMIT 64    /* <- blocks of MAXPACKETLENGCTH each */
/*
 * Creating connection on server side (passive open) --------------------------
 */
ComENTRY int conn_new_server(int mode, XKVList *server_param,
        int (*new_connection_handler)(int fd),
        int (*exception_handler)(int fd), struct conn_queue *input_queue);

ComENTRY int
  conn_cfg_add_inet_socket(XKVList *conn_param, int         port, int backlog),
  conn_cfg_add_unix_socket(XKVList *conn_param, const char *path, int backlog);

ComENTRY int   conn_cfg_get_port(XKVList *conn_param);
ComENTRY char *conn_cfg_get_path(XKVList *conn_param);

#ifdef _CONN_SOCKET_H
/*
 * In order to use the following function, please include "conn_socket.h"
 * before "connection.h" (or define _CONN_SOCKET_H if you already included
 * system headers that declare 'struct sockaddr')
 */
ComENTRY int conn_create_server_ex(struct sockaddr *local, int backlog,
               int (*new_handler)(int fd),
               int (*exception_handler)(int fd),
               struct protocol *proto, struct conn_queue *input_queue);
#endif
/*
 *  Legacy interface (still supported, but deprecated):
 */
ComENTRY int conn_create_server(int port, int backlog,
	void (*new_handler)(int fd),
	void (*exception_handler)(int fd), struct conn_queue *input_queue);

#if !defined _WIN32 && !defined _OS2

int conn_create_unix_server(char *path, int backlog,
	void (*new_handler)(int fd),
	void (*exception_handler)(int fd), struct conn_queue *input_queue);
#endif
/*
 * Creating connection on client side (active open) ---------------------------
 */
ComENTRY int conn_connect(int mode, XKVList *conn_param,
     int (*connect_handler)(int fd),
     int (*exception_handler)(int fd), struct conn_queue *input_queue);
/*
 *  'mode' is a combination of the following flags:
 */
#define C2K_MODE_SYNC  0 /* default */
#define C2K_MODE_ASYNC 1
                                /* do not include socket into list of */
#define C2K_EXCLUDE_FROM_LIST 2 /* all connections for conn_main_loop */

#define C2K_DOMAIN_INET 0x00 /* default - uses Internet protocol family  */
#define C2K_DOMAIN_UNIX 0x10 /* - UNIX protocols for local communication */

#define C2K_PROTO_TCP 0x000 /* default - TCP protocol (SOCK_STREAM) */
#define C2K_PROTO_UDP 0x100 /* -- UDP (SOCK_DGRAM) - not supported  */

#define C2K_MODE_FLAGS 0xFFF
#define C2K_TIMEOUT(X)     (((X)&0x1fFfFf)<<10) /* connect timeout (msec) */
#define C2K_GET_TIMEOUT(X) (((X)>>10)&0x1fFfFf)
/*
 * Negative value returned by conn_connect[_to] indicates one of the following
 * error condition:
 */
#define C2K_ERR_NO_RESOURCES       -20 /* resources exhausted   */
#define C2K_ERR_UNKNOWN_HOST       -21 /* hostname not resolved */
#define C2K_ERR_CONNECT_FAILED     -22 /* connect(3N) failed    */
#define C2K_ERR_CANT_BIND_SOCKET   -23 /* error in bind(3N)     */
#define C2K_ERR_CANT_CREATE_SOCKET -24 /* error in socket(3N)   */

ComENTRY int
  conn_cfg_add_inet_addr  (XKVList *conn_param, const char *host, int port),
  conn_cfg_add_unix_addr  (XKVList *conn_param, const char *path),
  conn_cfg_add_timeout    (XKVList *conn_param, int timeout);

   ComENTRY char *conn_cfg_get_host(XKVList *conn_param);
/* ComENTRY int   conn_cfg_get_port(XKVList *conn_param); declared */
/* ComENTRY char *conn_cfg_get_path(XKVList *conn_param);    above */

#define C2K_CONN_PARAM_KEYLIST "`hostname`port`timeout`protocol;"

ComENTRY int conn_connect_to(int mode, const char *addr, int port,
	int (*connect_handler)(int fd),
	int (*exception_handler)(int fd), struct protocol   *proto,
                                          struct conn_queue *input_queue);
#ifdef _CONN_SOCKET_H
/*
 * In order to use the following function, please include "conn_socket.h"
 * before "connection.h" (or define _CONN_SOCKET_H if you already included
 * system headers that declare 'struct sockaddr')
 */
ComENTRY int conn_connect_ex(int mode, struct sockaddr *local,
                                       struct sockaddr *remote,
               int (*connect_handler)(int fd),
               int (*exception_handler)(int fd),
               struct protocol *proto, struct conn_queue *input_queue);
#endif
/*
 *  Legacy interface (still supported, but deprecated):
 */
ComENTRY int conn_connect_to_server(const char *host, int port,
        void (*exception_handler)(int fd), struct conn_queue *input_queue);

ComENTRY int conn_async_connect_to_server(const char *host, int port,
	void (*connect_handler)(int fd),
	void (*exception_handler)(int fd), struct conn_queue *input_queue);

#if !defined _WIN32 && !defined _OS2

int conn_connect_to_unix_server(char *path,
        void (*exception_handler)(int fd), struct conn_queue *input_queue);

int conn_async_connect_to_unix_server(char *path,
	void (*connect_handler)(int fd),
	void (*exception_handler)(int fd), struct conn_queue *input_queue);
#endif
/*
 * General operation with connections -----------------------------------------
 */
ComENTRY int conn_protocol_reconfig(int fd, XKVList *proto_param),
             conn_set_protocol     (int fd, struct protocol *pp);
extern struct protocol conn_simple_protocol;

ComENTRY void 
  conn_set_default_protocol       (struct protocol *pp), /* DEPRECATED  */
  conn_set_server_default_protocol(struct protocol *pp); /* not MT-Safe */

typedef void (*conn_request_handler_t)(struct conn_queue *);
ComENTRY int
  conn_set_request_handler(int fd, conn_request_handler_t req_handler),
  conn_change_request_handler(int fd,
         conn_request_handler_t req_handler, struct conn_queue *new_q);

typedef void (*conn_ioctl_handler_t)(int fd);
ComENTRY int
  conn_register_input_handler(int fd, conn_ioctl_handler_t input_handler),
  conn_set_input_handler     (int fd, conn_ioctl_handler_t input_handler),
  conn_set_exception_handler (int fd, conn_ioctl_handler_t exception_handler),
  conn_unregister_input_handler(int fd);
/*
 * Output handler can be added only for connections previously registered with
 * conn_register_input_handler:
 */
ComENTRY int
  conn_register_output_handler(int fd, conn_ioctl_handler_t output_handler),
  conn_enable_output(int fd),
  conn_disable_output(int fd),
  conn_unregister_output_handler(int fd);

ComENTRY int conn_is_valid(int fd), 
             conn_connected(int fd), conn_alive(int fd);
#define conn_is_registered(_fd)      conn_alive(_fd)

ComENTRY int conn_output_queue_status(int fd), /* 0: empty; 1: not empty */
             conn_output_queue_length(int fd); /* length in bytes        */

ComENTRY void conn_close   (int fd);
ComENTRY int  conn_close_ex(int fd, int close_mode); /* 0: not closed yet */
/*
 * conn_close(x) == conn_close_ex(x, CONN_CLOSE_NOW);
 */
#define CONN_CLOSE_NOW       0 /* do not try to flush, just close socket */
#define CONN_CLOSE_TRY_FLUSH 1 /* try to flush, but close even if unsent */
#define CONN_CLOSE_WHEN_DONE 2 /* close later, on write completion       */

ComENTRY void conn_set_mode(int fd, int mode);
#define CONN_MODE_EXTENDED_PACKETS    0x001 /* default for 617+ */
#define CONN_MODE_DISABLE_EXT_PACKETS 0x801

ComENTRY int conn_set_socket_mode(int fd, int new_mode, int timeout_msec);
/*
 * Read/Write operations ------------------------------------------------------
 */
ComENTRY int conn_read(int fd); /* always puts data into input queue */
ComENTRY int conn_write    (int fd, unsigned char *data, int length),
             conn_write_now(int fd, unsigned char *data, int length);
/*
 * When conn_read/write returns -1 indicating error condition, it also stores
 * error code in the conn_errno; positive values go from OS (errno on UNIX,
 * WSAGetLastError() on WinNT), negative codes have the following meaning:
 */
#define C2K_ERRNO_WRONG_FD  -2 /* incorrect fd              */
#define C2K_ERRNO_CONN_TYPE -3 /* incorrect connection type */
#define C2K_ERRNO_NO_QUEUE  -4 /* i/o queue not set         */
#define C2K_ERRNO_CORRUPTED -5 /* i/o queue corrupted       */
#define C2K_ERRNO_CLOSED    -6 /* connection closed         */
#define C2K_ERRNO_TOO_BIG   -7 /* packet too big            */
#define C2K_ERRNO_PROTO_ERR -8 /* session protcol error     */
#define C2K_ERRNO_MT_LOCKED -9 /* locked by another thread  */

/* Define conn_errno entry */

int* conn_get_errno();

#define conn_errno (*conn_get_errno())

ComENTRY int conn_errno_mt();

ComENTRY struct request *conn_add_data_to_queue(struct conn_queue *q,
                unsigned char *data, int length, int socket, int reallocate);
/*
 * The following 4 functions are protected in MT-Safe mode by MIQ mutex:
 */
ComENTRY struct request *conn_get_request_from_queue(struct conn_queue *q);
ComENTRY void
  conn_add_request_to_queue(struct conn_queue *q, struct request *req),
  conn_clear_queue(struct conn_queue *q, int fd),
  conn_move_queue(struct conn_queue *destination_q,
                  struct conn_queue *source_q, int fd);

ComENTRY int conn_queue_is_empty(struct conn_queue *q);
ComENTRY void conn_free_request(struct request *req),
              conn_free_queue(struct conn_queue *q);
ComENTRY int
  conn_flush_socket(int fd),
  conn_flush_all_out(int addtl_scan_modes);
/*
 * Support for Asynchronous (aka multiplexing) mode ---------------------------
 */
ComENTRY int
  conn_scan_input(int fd, int timeout_sec), /* 'sec' for compatibility */
  conn_scan_socket(int fd, int timeout_sec, int mode),
  conn_scan_socket_msec(int fd, int timeout_msec, int mode),
  conn_scan_socket_stv (int fd, struct timeval *stop_time, int mode);

#ifdef FD_SET
  ComENTRY int
    conn_multi_scan    (fd_set *fd_mask, int timeout_msec, int mode),
    conn_multi_scan_stv(fd_set *fd_mask, struct timeval *stop_time, int mode);
#endif

#define CONN_SCAN_MODE_READ    1
#define CONN_SCAN_MODE_WRITE   2
#define CONN_SCAN_MODE_EXCEPT  4
#define CONN_SCAN_MODE_ALL     7 /* scan all types of activity    */
#define CONN_SCAN_MODE_CONNECT 7 /* wait for connection/exception */

#define CONN_SCAN_MODE_PROCESS 0x10 /* process all activity */
#define CONN_SCAN_MODE_FLUSH   0x40 /* - only flush outputs */
#define CONN_SCAN_MODE_TIMERS  0x80 /* perform timers       */
/*
 * This processing mode may be used to keep connections alive when application
 * is very busy and doesn't like to be disturbed -- read data from socket (and 
 * process KPL/ADDP messages), but don't call request_handler immediately:
 */
#define CONN_SCAN_MODE_KEEP_ALIVE 0x1000

/* CONN_SCAN_MODE_xxx_ALL modea overrides corresponding CONN_SCAN_MODE_xxx
 * mode (mask will be set to all sockets, registered in connection module):
 */
#define CONN_SCAN_MODE_READ_ALL   0x100 /* read mask := ALL   */
#define CONN_SCAN_MODE_WRITE_ALL  0x200 /* write mask := ALL  */
#define CONN_SCAN_MODE_EXCEPT_ALL 0x400 /* except mask := ALL */
#define CONN_SCAN_MODE_EVERYTHING 0x700 /* all masks := ALL   */
/* 
 * Verify whether it's alive - have to test READ bit first; if this bit is set,
 * but attempt to read returns 0, then connection is already closed (recv with
 * flag == MSG_PEEK is used, to prevent data from being read from socket); this
 * mode works only in conn_scan_socket (ignored in conn_multi_scan):
 */
#define CONN_SCAN_MODE_IS_ALIVE 0x21

ComENTRY void conn_main_loop(void), conn_shutdown    (void),
                                    conn_do_clearance(void);

ComENTRY int conn_disable_input(int fd),
             conn_enable_input(int fd);
/*
 * Timers and time processing -------------------------------------------------
 */
#define conn_compare_time(A, B) \
  ((A)->tv_sec < (B)->tv_sec ? -1 : \
  ((A)->tv_sec > (B)->tv_sec ?  1 : ((A)->tv_usec < (B)->tv_usec ? -1 : \
 				    ((A)->tv_usec > (B)->tv_usec ?  1 : 0))))
#define conn_diff_time(X, A, B)  \
  if ((A)->tv_usec < (B)->tv_usec) { \
    (X)->tv_sec  = (A)->tv_sec  - (B)->tv_sec  - 1;       \
    (X)->tv_usec = (A)->tv_usec - (B)->tv_usec + 1000000; \
  }      \
  else { \
    (X)->tv_sec  = (A)->tv_sec  - (B)->tv_sec;  \
    (X)->tv_usec = (A)->tv_usec - (B)->tv_usec; \
  }
#define conn_timeval_to_msec(X) ((X)->tv_sec*1000 + (X)->tv_usec/1000)

typedef void (*conn_timer_handler_t)(ulong arg);

ComENTRY unsigned long conn_add_timer(unsigned long msecs,
               		    conn_timer_handler_t callback, ulong arg);

ComENTRY unsigned long conn_add_mt_timer(int associated_fd,
                                       unsigned long msecs,
                	     conn_timer_handler_t callback, ulong arg);

ComENTRY void conn_delete_timer(unsigned long id);
ComENTRY long conn_process_timers(void *reserved);
ComENTRY unsigned long
              conn_add_bkgnd_timer(conn_timer_handler_t callback, ulong arg);
ComENTRY void conn_delete_bkgnd_timer(unsigned long id);
/*
 * Miscellaneous --------------------------------------------------------------
 */
ComENTRY int conn_get_sock_name  (int fd,             int *port),
             conn_get_peer_name  (int fd, char *host, int *port),
             conn_get_parent_sock(int fd);
/*
 * The following function should be used to compare two host names (instead
 * of strcmp) - because of aliases etc, two different strings may refer to
 * the same host:
 */
ComENTRY int conn_hostcmp(const char *host1, const char *host2);

ComENTRY void conn_print_stats(void);
ComENTRY XKVList *conn_stats_xkvlist(int fd);

ComENTRY int conn_exception_cause_mt();

/* Define entry for exception cause */
int* conn_get_exception_cause();

#define conn_exception_cause (*conn_get_exception_cause())

#define CONN_XCAUSE_EXTERNAL 0 /* exception caused by external condition   */
#define CONN_XCAUSE_TOO_SLOW 1 /* other party is too slow (packet remained */
                               /* unsent longer than specified timeout)    */
/*
 * Async connection: when conn_connect returns fd, but later it's found that
 * connection is not possible (usual case when connecting to remote host),
 * exception will be generated with one if the following reasons:
 */
#define CONN_XCAUSE_CANT_CONNECT 2 /* TCP stack reported failure */
#define CONN_XCAUSE_TIMED_OUT    3 /* connection timeout expired */
/*
 * The following XCAUSE is used when connection is dropped during the recovery
 * from EDABF error (either network glitch, or socket was not closed properly)
 */
#define CONN_XCAUSE_EBADF_RECOVERY 4
/*
 * conn_close_ex(fd, CONN_CLOSE_WHEN_DONE) completed:
 */
#define CONN_XCAUSE_WRITE_COMPLETED 5
/*---------------------------------------------------------------------------*/
#if defined(EXPERIMENTAL) && !defined(ConnMTSafe)
  void conn_set_empty_hook(int fd, void (*empty_hook)(int fd));
#endif
typedef int (*conn_ioctl_proc_t)(struct connection *cp);
typedef int (*conn_opened_proc_t)(struct connection *cp, 
                                       const char *addr, int port);
conn_opened_proc_t conn_set_opened_callback(conn_opened_proc_t callback);
conn_ioctl_proc_t  conn_set_closed_callback(conn_ioctl_proc_t  callback);

#ifdef FD_SET
/*
 * The same as select(3C), but supports hooks (see conn_select.h) and debug
 * printout (set by environment variable GCTI_CONN_DEBUG_SELECT):
 */
ComENTRY int
   conn_hooked_select(int nfds, fd_set *readfds,
 	      fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
ComENTRY void conn_print_fd_set(int nfds, fd_set *fdset, const char *title);
#endif

#ifdef __cplusplus
}
#endif
#endif /* _TCONNECTION_H */
