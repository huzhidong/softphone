/*
 * $Id: kvlist.h /main/34 30-Nov-2005.00:49:35 PST tikin $
 */
 
#ifndef _KVLIST_H
#define _KVLIST_H
#include <stdarg.h>

#include "com_types.h"

typedef enum {
  KVTypeString,
  KVTypeInt,
  KVTypeBinary,
  KVTypeList,
  KVTypeUnicode,
  KVTypeIncorrect = -1 /* used for error indication only */
} TKVType;

struct _kv_pair {
  TKVType type;
  char *key;
  int length;  /* length of the value (in packed format) */
  union {
    char *_string_value;
    int _int_value;
    unsigned char *_binary_value;
    struct kv_list *_list_value;
    void *_p;  /* details of Unicode representation are hidden */
  } _value;
#define string_value	_value._string_value
#define int_value	_value._int_value
#define binary_value	_value._binary_value
#define list_value	_value._list_value
  struct _kv_pair *kv_next;
  struct _kv_pair *kv_prev;
};
typedef struct _kv_pair TKVPair;

struct kv_list {
  struct _kv_pair *list;
  struct _kv_pair *current;
  struct _kv_pair *tail;
};
typedef struct kv_list TKVList;

typedef enum {
  KVResultError = -1,
  KVResultNotFound,
  KVResultSuccessful
} TKVResult;

#ifdef __cplusplus
extern "C" {
#endif

ComENTRY TKVList *TKVListCreate(void),
                 *TKVListDup(TKVList *tkvl);

ComENTRY TKVResult TKVListFree(TKVList *tkvl);
ComENTRY TKVResult
  TKVListAddString(TKVList *tkvl, const char *key, const char *value),
  TKVListAddInt   (TKVList *tkvl, const char *key, int value),
  TKVListAddBinary(TKVList *tkvl, const char *key,
                               unsigned char *val, int length);
/*
 * Attention: TKVListAddList function creates a copy of the list; use 'Insert'
 * if you want just to store pointer to the pre-created list:
 */
ComENTRY TKVResult
  TKVListAddList   (TKVList *tkvl, const char *key, TKVList *data),
  TKVListInsertList(TKVList *tkvl, const char *key, TKVList *data);
    
ComENTRY TKVResult
  TKVListDeletePair(TKVList *tkvl, const char *key),
  TKVListDeleteAll (TKVList *tkvl);

ComENTRY TKVResult TKVListInitScanLoop(TKVList *tkvl);
ComENTRY TKVPair  *TKVListNextPair    (TKVList *tkvl);

ComENTRY TKVType TKVListType(TKVPair *kvpair);
ComENTRY char   *TKVListKey (TKVPair *kvpair);

ComENTRY int            TKVListIntValue    (TKVPair *kvpair);
ComENTRY char          *TKVListStringValue (TKVPair *kvpair);
ComENTRY TKVList       *TKVListListValue   (TKVPair *kvpair);
ComENTRY unsigned char *TKVListBinaryValue (TKVPair *kvpair);
ComENTRY int            TKVListBinaryLength(TKVPair *kvpair);

ComENTRY TKVPair
  *TKVListGetPair  (TKVList *kvl, const char *key, TKVResult *result),
  *TKVListGetPairIC(TKVList *kvl, const char *key, TKVResult *result);
/*                     ^^
 * 'IC' in the name of means "Ignore Case" 
 */

ComENTRY int
  TKVListGetIntValue   (TKVList *tkvl, const char *key, TKVResult *result);
ComENTRY char *
  TKVListGetStringValue(TKVList *tkvl, const char *key, TKVResult *result);
ComENTRY unsigned char *
  TKVListGetBinaryValue(TKVList *tkvl, const char *key, TKVResult *result);
ComENTRY TKVList *
  TKVListGetListValue  (TKVList *tkvl, const char *key, TKVResult *result);

ComENTRY void TKVListPrint(void *f, TKVList *tkvl, const char *header);

/* T-library compatible printing */

typedef int (*kvlist_print_proc_t)(void* fp, const char* fmt,...);

ComENTRY void TKVListPrint2(void *f, kvlist_print_proc_t proc, TKVList *tkvl);
ComENTRY void TKVListPrint2Packed(void *f, kvlist_print_proc_t proc, void* data, int size);

/**
 * Setup kvlist print filter, predefined section names are:
 * log-filter - for options
 * log-filter-data - for filters
 */
ComENTRY void TKVListSetPrintFilter(TKVList* options,TKVList* data);

typedef enum KVLIST_FILTER_TYPE_tag
{
	KVLIST_FILTER_COPY,             /* Copy content */
	KVLIST_FILTER_ENCRYPT,          /* reserved */
	KVLIST_FILTER_SKIP,             /* skip key/pair */
	KVLIST_FILTER_HIDE,             /* hide with using '*' with fixed length */
	KVLIST_FILTER_TRUNCATE          /* reserved */
}KVLIST_FILTER_TYPE;

/**
 * return type of filter assigned for the string (KVLIST_FILTER_TYPE)
 * \param str  - key
 * \param size - length of the key
 */
ComENTRY int TKVListGetPrintFilterType(const char* str,int size);

/*
 * Convering TKVList to/from binary platform-independent format:
 */
ComENTRY unsigned char *TKVListPack(TKVList *tkvl, int *len_returned);
ComENTRY TKVList *TKVListUnpack(const unsigned char *buffer, int buf_len);
ComENTRY int TKVListPackedSize(TKVList *udata);

/*
 * Extracting pairs from list: get & delete in one operation (extracted pair
 * need to be freed explicitly later):
 */
ComENTRY TKVPair *TKVListExtract(TKVList *kvl,  const char *key);
ComENTRY TKVResult TKVListUnlinkPair(TKVList *kvl, TKVPair *kvp),
                    TKVListFreePair(TKVPair *kvp);
/*
 * Conversion to/from string (both functions allocate memory dynamically):
 */
ComENTRY char    *TKVListToString  (TKVList *tkvl);
ComENTRY TKVList *TKVListFromString(const char *str);

#ifdef __cplusplus
}
#endif

#endif /* _KVLIST_H */
