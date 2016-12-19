/*
 * $Id: tlib_msg.h,v 1.4 2003/03/10 20:06:10 epi Exp $
 */

TConnectionID t_msg_get_conn_id(message_t *msg, int id);
void t_msg_add_conn_id(message_t *msg, int id, TConnectionID conn_id);

void hton_connid(const void *src, void *dst); /* host-to-network conn_id conv */
#define ntoh_connid(src, dst) hton_connid(src, dst)     /* reverse conversion */

