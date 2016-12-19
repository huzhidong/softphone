/*
 * $Id: server.h,v 1.18 2002/07/19 21:34:13 epi Exp $
 */

#ifndef _SERVER_H
#define _SERVER_H

#include "com_types.h"
#include "xkvlist.h"

#ifdef __cplusplus
extern "C" {
#endif

struct server_info {
  int srv_fd;

#define SRV_FD_INIT -5

  char *srv_name;
  char *srv_appl_name;
  char *srv_appl_passwd;
/*
 * BACKUP_HOT support (OBSOLETE, please do not use):
 */
  char *host;     /* have to preverse server host/port (otherwise will not */
  int port;       /*                                 be able to reconnect) */
  int cluster_id; /* id of server "cluster" (primary with all its backups) */
  int srv_flags;

#define SRV_ROLE_MASK(X) (X&0xf) /* current server role */
#define SRV_ROLE_UNKNOWN    0x0
#define SRV_ROLE_PRIMARY    0x1
#define SRV_ROLE_BACKUP     0x2
#define SRV_SET_ROLE(X,V) X = (X&~0xf)|V

#define SRV_PREV_ROLE_MASK(X) (X&0xf0) /* previous server role */
#define SRV_PREV_ROLE_UNKNOWN    0x00
#define SRV_PREV_ROLE_PRIMARY    0x10
#define SRV_PREV_ROLE_BACKUP     0x20
#define SRV_PREV_ROLE_1ST_SERVER 0x40
#define SRV_SET_PREV_ROLE(X,V) X = (X&~0xf0)|V

  int status;

#define SRV_DISCONNECTED 0x000 /* totally disconnected              */
#define SRV_CONNECTED    0x100 /* connected, objects not registered */
#define SRV_WARM_STANDBY 0x200 /* - objects registered              */
#define SRV_HOT_STANDBY  0x300 /* - - HotStandby mode               */

  int rattempt; /* remaining reconnect attempts, = -1 after connection */
                /* established, to tell disconnect from failed attempt */

  unsigned long timer_id;
  struct timeval sync_timer;

  void (*dispatch_func)(void *arg);
  struct server_info *srv_next;
  struct server_info *srv_prev;

  XKVList *proto_param; /* protocol parameters from original connection */
};

ComENTRY
  struct server_info *server_info_set(int fd, /* starting from 6.0.001, it */
                        const char *srv_name, /* returns pointer to newly  */
                        const char *appl_name,/* created structure         */
                        const char *passwd, void (*dispatch_func)(void *arg));
ComENTRY
  void server_info_set_dispatch_func(int fd, void (*dispatch_func)(void *arg));
ComENTRY void (*server_info_get_dispatch(int fd))(void *arg);

ComENTRY struct server_info *server_info_create(int fd),
                            *server_info_find_by_fd(int fd);
ComENTRY void server_info_delete(int fd),
              server_info_delete_by_addr(struct server_info *si);

ComENTRY char *server_info_get_appl_name(int fd),
              *server_info_get_appl_passwd(int fd);

ComENTRY void server_info_print(struct server_info *si); /* NULL means 'all' */

/*
 * BACKUP_HOT support (OBSOLETE, please do not use):
 */
struct server_info *server_info_find_by_location
                         (char *host, int port, int cluster_id);
struct server_info *server_info_find_by_cluster(int cluster_id);

int server_info_set_role(struct server_info *si, int new_role);
void server_info_set_status(int fd, int stat);

int server_info_get_cluster_id( int fd );
int server_info_get_next(int cluster_id, int fd);
int server_info_find_primary(int cluster_id);

void server_info_set_sync_timer (struct server_info *si, int timeout_msec);
void server_info_set_async_timer(struct server_info *si, unsigned long id);
unsigned int server_info_get_async_timer(struct server_info *si);

int server_info_check_sync_timers(int cluster_id, /* returns interval to */
                void (*callback)(unsigned long)); /* next timer, or zero */

int server_info_is_redundant(int cluster_id);
/*
 * The following function returns status and role (srv_flags) of the server
 * specified by 'fd' and fills 'other_status' with info about other server
 * (from the same cluster), is applicable:
 */
int server_info_get_cluster_stat(int cluster_id, int fd, int *other_status);

#ifdef __cplusplus
}
#endif
#endif /* _SERVER_H */
