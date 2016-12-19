/*
 * $Id: message.h,v 1.32 2003/03/14 01:58:06 epi Exp $
 */

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "com_types.h"
#include "kvlist.h"

typedef enum {MSG_PACK_MODE_STANDARD, MSG_PACK_MODE_ENHANCED} msg_pack_mode_t; 
typedef enum {attr_int, 
              attr_string, 
              attr_bstring, 
              attr_long,
              attr_binary} msg_attr_type_t;

struct attrib {
    unsigned long attr_id;
    msg_attr_type_t attr_type;
    union {
	unsigned long _attr_int_value;
	ulong64_t _attr_long_value;
	char *_attr_string_value;
	unsigned char *_attr_bstring_value;
	unsigned char *_attr_binary_value;
    } _attr_value_union;
    struct attrib *attr_next;
};

#define attr_int_value _attr_value_union._attr_int_value
#define attr_long_value _attr_value_union._attr_long_value
#define attr_string_value _attr_value_union._attr_string_value
#define attr_bstring_value _attr_value_union._attr_bstring_value
/*
 * attr_binary_value is missed intentionally, to discourage hacking into
 * internal structures
 */

struct message {
    unsigned int msg_id;
    struct attrib *msg_attr_list;
#ifdef MSG_ATTR_HASH
    unsigned int msg_am_attrs;
    struct attrib *msg_attrs[1]; /* actual size is msg_am_attrs */
#endif
};

typedef struct attrib attrib_t;
typedef struct message message_t;

#ifdef __cplusplus
extern "C" {
#define _PRIVATE_ private:
#else
#define _PRIVATE_
#endif

ComENTRY int msg_pack(message_t *msg, unsigned char *buffer, int length);
/*
 * Function 'msg_unpack' is DEPRECATED - it is not possible to process dirty
 * (corrupted) buffer if the length of the data is not known. Please use
 * 'msg_unpack0' instead:
 */
ComENTRY message_t *msg_unpack (unsigned char *buffer);
ComENTRY message_t *msg_unpack0(unsigned char *buffer, int real_length);
ComENTRY int msg_get_packed_size(message_t *msg);

ComENTRY message_t *msg_create(int msg_id), *msg_copy(message_t *msg);
ComENTRY void msg_delete(message_t *msg);
ComENTRY void 
  msg_add_int_attrib(message_t *msg, int id, long value),
  msg_add_long_attrib(message_t *msg, int id, ulong64_t value),
  msg_add_string_attrib(message_t *msg, int id, const char *value),
  msg_add_string_with_length(message_t *msg, int id, const char *val, int len),
  msg_add_string_attrib_from_int(message_t *msg, int id, int value);

#define msg_add_string_attrib_if_not_null msg_add_string_attrib

ComENTRY void msg_add_kvlist(message_t *msg, int attr, TKVList *tkvl);
#define msg_add_kvlist_attrib msg_add_kvlist /* to be consistent */

ComENTRY attrib_t *msg_find_attrib(message_t *msg, int id);
ComENTRY void
  msg_delete_attrib(message_t *msg, int id),
  msg_copy_attrib(message_t *src, message_t *dst, int id);
ComENTRY int msg_copy_all_attribs(message_t *src, message_t *dst);

ComENTRY long msg_get_int_attrib_value(message_t *msg, int id);
#ifndef _NO_LONG_LONG
  ComENTRY ulong64_t msg_get_long_attrib_value(message_t *msg, int id);
#endif
ComENTRY char *msg_get_string_attrib_value(message_t *msg, int id);
ComENTRY TKVList 
  *msg_get_kvlist_value(const attrib_t *attr),
  *msg_get_kvlist_attrib_value(message_t *msg, int id);

ComENTRY void
  hton_long64(const void *src, void *dst); /* host-to-network conversion */
                                           /* for long64, such as ConnID */
#define ntoh_long64(X,Y) hton_long64(X, Y) /* network-to-host (the same) */
/*
 * Note: _bstring_ functions are DEPRECATED..
 */
ComENTRY void 
  msg_add_bstring_attrib(message_t *msg, int id, const unsigned char *value);
ComENTRY unsigned char *msg_get_bstring_attrib_value(message_t *msg, int id);
/*
 * ..in favor of _binary_ set of functions (which are fully compatible for
 * messages shorter than 64Kb):
 */
ComENTRY void 
  msg_add_binary_attrib(message_t *msg, int id, const unsigned char *value,
                                                            int value_len);
ComENTRY unsigned char
            *msg_get_binary_attrib_value(message_t *msg, int id, int *len),
            *msg_get_binary_value (const attrib_t *attr);
ComENTRY int msg_get_binary_length(const attrib_t *attr);
/*
 * NOTE: size of encoded length is NOT included into binary attrib length!
 */

#ifdef MSG_ATTR_HASH
  ComENTRY unsigned int msg_set_hash_size(unsigned int hash_size);/* returns */
#endif                                                            /* old size*/
/*---------------------------------------------------------------------------*/
typedef struct msg_iter_tag {
_PRIVATE_
  message_t *_msg;
  attrib_t _attr;
  long _reserved[2];
#if defined(ComENTRY_LOCAL) && defined(__cplusplus)
  friend ComENTRY void  msg_iter_init (message_t *msg, struct msg_iter_tag *t);
  friend ComENTRY int             msg_iter_next_id    (struct msg_iter_tag *t);
  friend ComENTRY const attrib_t *msg_iter_next_attrib(struct msg_iter_tag *t);
#endif
} msg_iter_t;

ComENTRY void  msg_iter_init (message_t *msg, msg_iter_t *it);
ComENTRY int             msg_iter_next_id    (msg_iter_t *it); /* not yet */
ComENTRY const attrib_t *msg_iter_next_attrib(msg_iter_t *it);
/*---------------------------------------------------------------------------*/
typedef struct linkable_message { /* class linkable_msg_t : public message_t */
  struct message msg;
  struct linkable_message *prev, *next;
}
linkable_message_t;
ComENTRY linkable_message_t *msg_make_linkable(message_t *msg);

#undef _PRIVATE_
#ifdef __cplusplus
}
#endif
#endif /*_MESSAGE_H */

