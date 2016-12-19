/*
 * $Id: kpl_proto.h,v 1.4 2000/07/25 17:48:02 epi Exp $
 */

#ifndef _KPL_PROTO_H
#define _KPL_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

extern struct protocol kpl_protocol;

void kpl_proto_initialize();
int kpl_configure(const char *server_name);
#ifdef _XKVLIST_H
  int kpl_xconfig(struct connection *cp, XKVList *proto_params);
#endif

int kpl_set_protocol(struct connection *cp, uchar *buf, int len);
int kpl_detect      (struct connection *cp, uchar *buf, int len);

#ifdef __cplusplus
}
#endif
#endif /* _KPL_PROTO_H */

