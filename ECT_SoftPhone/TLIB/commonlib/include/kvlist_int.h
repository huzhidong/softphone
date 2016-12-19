/*
 * $Id: kvlist_int.h,v 1.17 2003/04/24 22:30:19 epi Exp $
 */

#ifndef _KVLIST_INT_H
#define _KVLIST_INT_H

#include "com_types.h"

#define KVTYPE_HUGE_DATA 0x80

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Functions pack/unpack_kv_list are DEPRECATED; please use TKVList[Un]Pack
 * from kvlist.h instead (they don't have 64K limitations and fully compatible
 * for shorter data)
 */
ComENTRY
  unsigned char *pack_kv_list(TKVList *udata); /* data must be < 64K packed */
ComENTRY
  int pack_kv_list_to_buf(TKVList *udata, unsigned char *buffer, int buflen);
ComENTRY
  unsigned char *kv_dup_packed_data(const unsigned char *data); /* <64K only */
ComENTRY TKVList *unpack_kv_list(const unsigned char *buffer);

ComENTRY int add_kv_pair_to_kv_list(TKVList *udata, const char *key,
                                    TKVType type, const void *val, int len);
/* private: */
void tkvlist_insert_kv_pair(TKVList *udata, TKVPair *kvp);
/*---------------------------------------------------------------------------*/

ComENTRY void merge_kv_list (TKVList *udata, const TKVList *added_data),
              update_kv_list(TKVList *udata, const TKVList *new_data);
/*
 * NOTE: all operations with packed data work in assumption that first 2 bytes 
 * of the data is its length, so it will not work with TKVLists larger than 64K
 */
ComENTRY unsigned char
  *kv_merge_packed_data (const unsigned char *d1, const unsigned char *d2),
  *kv_update_packed_data(const unsigned char *d1, const unsigned char *d2);

ComENTRY TKVList *dup_kv_list(TKVList *udata);/* deprecated, use TKVListDup  */
ComENTRY int kv_list_free    (TKVList *udata);/* deprecated, use TKVListFree */

extern int kv_list_max_bin_printable;
ComENTRY int kv_list_set_max_bin_printable(int new_value); /* returns old */

#ifdef __cplusplus
}
#endif
#endif /* _KVLIST_INT_H */

