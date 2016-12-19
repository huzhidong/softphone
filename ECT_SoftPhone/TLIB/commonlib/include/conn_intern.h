/*
 * $Id: conn_intern.h /main/27 16-Aug-2004.14:15:06 PST tikin $
 */

#ifndef _CONN_INTERN_H
#define _CONN_INTERN_H

#include "com_types.h"  /* uchar etc   */
#include "conn_fdset.h" /* SOCKET_TYPE */

#ifdef ConnMTSafe
/* 
 * Platforms supported by gthread library:
 *   AIX     = defined(_AIX)
 *   HP-UX   = defined(__HP_aCC) -- only defined in C++ compiler
 *   OSF     = defined(__osf__)
 *   Solaris = defined(sun)      -- defined by compiler or in Make6.inc
 *   Unix    = defined(__unix__) -- generic Unix
 *   WinNT   = defined(_WIN32)
 */
#include "gos.h"

extern TGMutex MLAC[1], /* Mutex on List of All Connections  */
               MLT[1],  /* Mutex on global List of Timers    */
               MIQ[1],  /* Mutex on Input Queues (1 for all) */
               MGH[1],  /* Mutex for gethostname & getrlimit */
               MCP[1];  /* Mutex on buffer Cache Pool        */

#ifdef notdef_debug
#define Z_(x) #x
#define Z(_x) Z_(_x)

# define do_mutex_lock(X) \
    fprintf(stderr, "Lock("Z(X)")"__FILE__":%d[%d] ", \
          __LINE__, g_thread_get_id()); g_mutex_lock(X)
# define do_mutex_unlock(X) \
    fprintf(stderr, "Unlock("Z(X)")"__FILE__":%d[%d] ", \
          __LINE__, g_thread_get_id()); g_mutex_unlock(X)
#else
# define do_mutex_lock(X)   g_mutex_lock(X)  
# define do_mutex_unlock(X) g_mutex_unlock(X)  
#endif
#else /* not ConnMTSafe: disable all operation with mutexes */

#define do_mutex_lock(X)
#define do_mutex_unlock(X)

#endif

#ifdef __cplusplus
extern "C" {
#endif

enum conn_type {
  CONN_SERVER,
  CONN_SERVER_CLIENT,
  CONN_ASYNC_CLIENT,
  CONN_SYNC_CLIENT,
  CONN_EXTERNAL
};


  struct conn_queue;
  typedef void (*conn_ioctl_proc_int_t)(int fd);
  typedef void (*conn_request_proc_int_t)(struct conn_queue *);

#ifdef ConnMTSafe
  struct soft_lock_wait_list {
    TGSemaphore *TS;
    struct soft_lock_wait_list *prev, *next;
  };
#endif

struct connection {
  SOCKET_TYPE conn_socket;
  enum conn_type conn_type;
  int conn_wait_connection; /* non-zero (timer_id) if waiting for connection */

  struct protocol *conn_protocol;
  void *conn_protocol_private_data;

  struct conn_queue *conn_input_queue;
  struct conn_queue *conn_output_queue;
  unsigned char *conn_input_buffer;
  int conn_input_buffer_length;

  conn_ioctl_proc_int_t conn_input_handler;
  conn_ioctl_proc_int_t conn_new_handler;    /* used for CONN_SERVER only */
#define conn_output_handler conn_new_handler /* only for CONN_EXTERNAL    */
  conn_ioctl_proc_int_t conn_exception_handler;
  conn_ioctl_proc_int_t conn_connect_handler;
  conn_request_proc_int_t conn_request_handler;

  int conn_flags; /* conn_mode & CONN_REQUEST_TO_CLOSE/_CLOSE_AFTER_WRITE */
  struct conn_queue *conn_pending_queue;

  unsigned long conn_generation;
  unsigned long conn_bytes_received, conn_bytes_sent; /* ifdef CONN_STATS */

  SOCKET_TYPE parent_socket; /* for client connections: fd of server port */
  char  *server_description; /* for server connections: the description   */
#ifdef ConnMTSafe
  int                mt_locked; /* lock counter */
  TGThreadDescriptor mt_owner;  /* owner thread */
  int mt_soft_lock;
  struct soft_lock_wait_list *mt_wait_head, /* waiting list for soft lock */
                             *mt_wait_tail; /* (mt_soft_lock-1 elements)  */
  TGThreadDescriptor 
         mt_soft_lock_owner; /* - owner of the soft lock (for debug only) */
#endif
#ifdef EXPERIMENTAL
  void (*conn_empty_hook)(int fd);
#endif
  int dns_req;
};
#define CONN_REQUEST_TO_CLOSE   0x10
#define CONN_CLOSE_AFTER_WRITE  0x20
#define CONN_CLOSE_WHEN_FLUSHED 0x40
#define CONN_FLAGS_MODE_MASK    0x0F

/*---- file connection.c ----------------------------------------------------*/
struct connection *conn_create_locked(SOCKET_TYPE socket, int use_MLAC);
struct connection *conn_find_no_lock (SOCKET_TYPE socket);
int         conn_find_index_by_socket(SOCKET_TYPE socket);

#ifdef ConnMTSafe
struct connection *conn_find_and_lock(SOCKET_TYPE socket);
void conn_release_lock   (struct connection *cp),
     conn_release_lock_by_fd(SOCKET_TYPE socket);
/*
 * The following three functions work in assumtion MLAC is locked by caller;
 * fd_mask == CONN_FDSET_LOCK_ALL means master_lock shall be used:
 */
int conn_lock_it(struct connection *cp); /* returns negative value if can't */
                                         /* -2 if collided with master_lock */
int conn_set_lock_by_fd_set(fd_set *fd_mask, SOCKET_TYPE *bad_socket);
void conn_release_lock_by_fd_set(fd_set *fd_mask);

#define CONN_FDSET_LOCK_ONE ((fd_set *)1)
#define CONN_FDSET_LOCK_ALL ((fd_set *)2)

extern int conn_close_by_master_lock_release; /* set by conn_close */
/*
 * "Soft" lock is used to control write operations
 */
struct connection *conn_find_n_soft_lock(SOCKET_TYPE socket);
void conn_release_soft_lock(struct connection *cp);

int conn_soft_lock_it(struct connection *cp);/* MLAC shall be locked outside */
                                             /* and is always unlocked here  */
typedef struct {
  int _conn_errno;
  int _conn_exception_cause;
  int semaphore_inited;
  TGSemaphore TS[1]; /* Thread Semaphore controls soft lock waiting list */
}conn_layer_data_t;

conn_layer_data_t *conn_layer_get_TSD(void);

#define g_thread_set_var(_var,_data) conn_layer_get_TSD()->_var = (_data)
#define g_thread_get_var(_var)      (conn_layer_get_TSD()->_var)

#else /* not ConnMTSafe */

#define conn_find_by_socket(S)   conn_find_no_lock(S)
#define conn_find_and_lock(S)    conn_find_no_lock(S)
#define conn_find_n_soft_lock(S) conn_find_no_lock(S)
#define conn_release_lock(CP)
#define conn_release_soft_lock(FD)
#define conn_release_lock_by_fd(FD) /* nothing */

#define g_thread_set_var(_var,_data) _var = (_data)
#define g_thread_get_var(_var)      (_var)

#endif

void conn_remove_cp_from_list(struct connection *cp);
struct connection *conn_get_by_index(int conn_index);
extern int conn_max_sock_index, conn_rlimit_adjusted;

extern int conn_debug_open, conn_debug_select, 
                            conn_debug_timers, conn_debug_write;

void conn_print_n_test(int test);

/*---- file conn_open.c -----------------------------------------------------*/
int conn_accept_connection(struct connection *server_cp);
#ifdef _CONN_SOCKET_H
  int conn_gethostbyname(struct sockaddr_in *sin, const char *host, int port);
#endif
void conn_close_locked(struct connection *cp), /* locked by current thread */
     conn_final_close (struct connection *cp); /* no active "soft" locks   */

/*---- file conn_rw.c -------------------------------------------------------*/
unsigned char *conn_buffer_cache_get(void);  /* gives MAXPACKETLENGTH buffer */
void conn_buffer_cache_put(unsigned char *buffer),
     conn_buffer_cache_free_all(void);

int conn_flush_output(struct connection *cp);
int conn_read_internal(struct connection *cp);
int conn_write_small_data /* no more than 16K */
             (struct connection *cp, uchar *data, int length, int mute_proto),
    conn_write_big_data /* supports "extended packets" */
             (struct connection *cp, uchar *data, int length, int mute_proto);

/*---- file conn_scan.c -----------------------------------------------------*/
void conn_scan_startup(void);
int  conn_is_time_to_leave();
int  conn_check_socket_status(SOCKET_TYPE fd); /* returns 0 if Ok */
void conn_raise_exception(struct connection *cp, int cause);

void conn_global_masks_set  (SOCKET_TYPE fd, int masks_to_set),
     conn_global_masks_clear(SOCKET_TYPE fd, int masks_to_clear);

#ifdef USE_POLL_INSTEAD_SELECT
#define CONN_SCAN_MASK_READ  POLLIN
#define CONN_SCAN_MASK_WRITE POLLOUT
#define CONN_SCAN_MASK_BOTH  POLLIN|POLLOUT

  extern struct pollfd conn_global_poll_fds[];
  /*
   * Even if 'select' is not used for scanning, we still need some place to
   * keep waiting-for-write status of all connections:
   */
  extern fd_set conn_global_write_mask;
#else
#define CONN_SCAN_MASK_READ  1
#define CONN_SCAN_MASK_WRITE 2
#define CONN_SCAN_MASK_BOTH  3

  extern fd_set conn_global_read_mask, conn_global_write_mask;
#endif

/*---- file conn_timer.c ----------------------------------------------------*/
int conn_remove_all_timers(void);  /* returns total number of timers removed */
int conn_perform_timers(struct timeval *now);

void conn_perform_bkgnd(void); /* process until timeout expires */
extern int conn_param_bkgnd_timers_tout; /* default 0 (1 timer) */

struct conn_timer;
extern struct conn_timer *conn_timers_top, *bkgnd_timers_head;

#ifdef ConnMTSafe
  void conn_delete_all_mt_timers(void); /* called when TSD is destroyed */
  struct conn_timer *conn_get_first_timer(void);
#else
# define conn_get_first_timer() conn_timers_top
#endif

const struct timeval *conn_get_timer_expire_stv(struct conn_timer *tp);

#ifdef __cplusplus
};
#endif

#endif /* _CONN_INTERN_H */

