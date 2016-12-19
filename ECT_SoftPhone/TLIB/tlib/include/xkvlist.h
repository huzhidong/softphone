/*
 * $Id: xkvlist.h,v 1.14 2002/06/20 00:26:34 epi Exp epi $
 */

#ifndef _XKVLIST_H
#define _XKVLIST_H
#define XKVLIST_VERSION 70050 /* version 7.0.050 */

#include "com_types.h" /* uchar & ulong64_t */

typedef enum {
  XKVTypeString = 0, /* NULL-terminated string                           */
  XKVTypeInt    = 1, /* 32-bit integer                                   */
  XKVTypeBinary = 2, /* binary data (up to 4Gb - size must fit into int) */
  XKVTypeList   = 3, /* nested XKVList                                   */
  XKVTypeEmpty  = 4, /* no value at all (for empty XML elements: <abc/>) */
  XKVTypeUnicode= 5, /* Unicode (wide-char) string                       */
  XKVTypeLong   = 6, /* 64-bits int (ConnID), may be unpacked as Binary  */
  XKVTypeFloat  = 7, /* floating point number                            */
  XKVTypeEnum   = 8, /* reserved for future extension                    */
  XKVTypeIncorrect = -1
} XKVType;

typedef enum {
  XKVResultError      = -1,
  XKVResultNotFound   =  0,
  XKVResultWarning    =  0, /* synonym */
  XKVResultSuccessful = +1,
  XKVResultOk         = +1  /* synonym */
} XKVResult;

struct xkv_pair_tag; /* private structures */
struct xkv_list_tag; /* defined in .c file */

typedef struct xkv_pair_tag XKVPair;
typedef struct xkv_list_tag XKVList;

#define XKVL_DEFAULT     0        /* default format (let library cares)      */
#define XKVL_UNPACKED    0x100000 /* default unpacked format                 */
#define XKVL_PACKED      0x200000 /* default packed format                   */
#define XKVL_PACKED_TKVL 0x210000 /* packed format compatible with TKVList   */
#define XKVL_PACKED_MSG  0x220000 /* packed format compatible with message_t */
#define XKVL_PACKED_XKVL 0x240000 /* 'native' packed format                  */

#ifdef __cplusplus
  extern "C" {
#endif

/*----------------------------------------- Basic XKVList construction ------*/

ComENTRY XKVList *XKVListCreate(void),
                 *XKVListCreateEx(int fmt, int initial_size);

ComENTRY XKVResult XKVListFree(XKVList *kvl),
                   XKVPairFree(XKVPair *kvp);

ComENTRY XKVList *XKVListDup  (XKVList *kvl),
                 *XKVListDupEx(XKVList *kvl, int fmt);

ComENTRY XKVResult
  XKVListAddString(XKVList *kvl, const char *key, const char *value),
  XKVListAddInt   (XKVList *kvl, const char *key, int value),
  XKVListAddBinary(XKVList *kvl, const char *key, 
                                 const uchar *val, int length),
  XKVListAddList  (XKVList *kvl, const char *key, XKVList *data),
  XKVListAddEmpty (XKVList *kvl, const char *key),
  XKVListAddLong  (XKVList *kvl, const char *key, ulong64_t value),
  XKVListAddFloat (XKVList *kvl, const char *key, double value);
/*
  The following function doesn't make a copy of the list, but just add
  the pointer ('data' must not be used after calling this function!):
*/
ComENTRY XKVResult XKVListAddListPtr(XKVList *kvl, 
                                  const char *key, XKVList *data);

ComENTRY XKVResult XKVListRemovePair(XKVList *kvl, XKVPair *kvp),
                   XKVListDeletePair(XKVList *kvl, const char *key),
                   XKVListDeleteAll (XKVList *kvl);

/*--------------------------------------------- Access to XKVList data ------*/

ComENTRY XKVType XKVListType (XKVPair *kvp); /* value type */
ComENTRY XKVType XKVListKType(XKVPair *kvp); /* key type   */
ComENTRY char   *XKVListKey  (XKVPair *kvp);

ComENTRY char          *XKVListStringValue (XKVPair *kvp);
ComENTRY int            XKVListIntValue    (XKVPair *kvp);
ComENTRY unsigned char *XKVListBinaryValue (XKVPair *kvp);
ComENTRY int            XKVListBinaryLength(XKVPair *kvp);
ComENTRY XKVList       *XKVListListValue   (XKVPair *kvp);
ComENTRY ulong64_t      XKVListLongValue   (XKVPair *kvp);
ComENTRY double         XKVListFloatValue  (XKVPair *kvp);

ComENTRY XKVResult XKVListInitScanLoop(XKVList *kvl);
ComENTRY XKVPair  *XKVListNextPair    (XKVList *kvl);

ComENTRY XKVPair 
  *XKVListGetPair    (XKVList *kvl, const char *key, XKVResult *result),
  *XKVListGetNextPair(XKVList *kvl, const char *key, XKVResult *result);

ComENTRY char *XKVListGetStringValue(XKVList *kvl, const char *key,
                                                               XKVResult *res);
ComENTRY int XKVListGetIntValue(XKVList *kvl, const char *key, XKVResult *res);
ComENTRY uchar 
  *XKVListGetBinaryValue(XKVList *kvl, const char *key, XKVResult *, int *len);
ComENTRY XKVList
  *XKVListGetListValue(XKVList *kvl, const char *key, XKVResult *result);
ComENTRY ulong64_t
   XKVListGetLongValue(XKVList *kvl, const char *key, XKVResult *result);
ComENTRY double
   XKVListGetFloatValue(XKVList *kvl, const char *key, XKVResult *result);

/*---------------------------------------- Advanced XKVList operations ------*/

ComENTRY XKVPair *XKVPairString(const char *key, const char  *value),
                 *XKVPairInt   (const char *key, int          value),
                 *XKVPairBinary(const char *key, const uchar *value, int len),
                 *XKVPairList  (const char *key, XKVList     *value),
                 *XKVPairEmpty (const char *key),
                 *XKVPairLong  (const char *key, ulong64_t value),
                 *XKVPairFloat (const char *key, double    value),
                 *XKVPairListPtr(const char *key, XKVList *value);
/*
 * XKVPairXXX functions create unlinked pair that will be automatically cleared
 * when used as parameter to XKVListAddXXX functions
 */
ComENTRY XKVResult 
  XKVListAddPair      (XKVList *kvl, XKVPair *kvp),
  XKVListAddPairAfter (XKVList *kvl, XKVPair *kvp, XKVPair *where),
  XKVListAddPairBefore(XKVList *kvl, XKVPair *kvp, XKVPair *where);

ComENTRY XKVResult XKVListReplacePair(XKVList *kvl, XKVPair *old_pair,
                                                    XKVPair *new_pair),
  XKVListReplaceString(XKVList *kvl, const char *key, const char *value),
  XKVListReplaceInt   (XKVList *kvl, const char *key, int value);

ComENTRY XKVList *XKVListFindSublist(XKVList *kvl, XKVPair *filter);

/*------------------------------------------ Pairs with non-string key ------*/

ComENTRY int XKiVListKey(XKVPair *kvp);

ComENTRY XKVPair *XKiVPairString(int id, const char  *value),
                 *XKiVPairInt   (int id, int          value),
                 *XKiVPairBinary(int id, const uchar *value, int length),
                 *XKiVPairList  (int id, XKVList     *value),
                 *XKiVPairEmpty (int id),
                 *XKiVPairLong  (int id, ulong64_t value),
                 *XKiVPairFloat (int id, double    value),
                 *XKiVPairListPtr(int id, XKVList *value);

ComENTRY XKVPair *XKiVListGetPair    (XKVList *kvl, int id, XKVResult *res),
                 *XKiVListGetNextPair(XKVList *kvl, int id, XKVResult *res);

ComENTRY char  *XKiVListGetStringValue(XKVList *kvl, int id, XKVResult *res);
ComENTRY int    XKiVListGetIntValue   (XKVList *kvl, int id, XKVResult *res);
ComENTRY uchar *XKiVListGetBinaryValue(XKVList *kvl, int id, XKVResult *res,
                                                                    int *len);
ComENTRY XKVList  *XKiVListGetListValue(XKVList *kvl, int id, XKVResult *res);
ComENTRY ulong64_t XKiVListGetLongValue(XKVList *kvl, int id, XKVResult *res);
ComENTRY double   XKiVListGetFloatValue(XKVList *kvl, int id, XKVResult *res);

/*------------------------------------------- User-defined value types ------*/

ComENTRY XKVPair 
  *XKVuPairString(const char *key, int utype, const char  *value),
  *XKVuPairInt   (const char *key, int utype, int          value),
  *XKVuPairBinary(const char *key, int utype, const uchar *value, int length),
  *XKVuPairList  (const char *key, int utype, XKVList     *value),
  *XKVuPairEmpty (const char *key, int utype),
  *XKVuPairLong  (const char *key, int utype, ulong64_t value),
  *XKVuPairFloat (const char *key, int utype, double    value);

ComENTRY int XKVListUType(XKVPair *kvp);

/*-------------------------------------------------------- Conversions ------*/

ComENTRY unsigned char 
  *XKVListGetPacked(XKVList *kvl, int fmt, int *packed_len_here);

ComENTRY int XKVListPackedSize  (XKVList *kvl, int fmt);
ComENTRY int XKVListPackToBuffer(XKVList *kvl, int fmt,
                                uchar *buffer, int buffer_len);

ComENTRY XKVList *XKVListFromBuffer(const uchar *buffer, int len, int fmt);
/*
 * Unless explicitly requested, FromBuffer function will not attempt to unpack
 * the buffer (thus can't verify it contains valid data). If verification are
 * desired (e.g. to generate proper diagnostic), the following flag should be
 * added to fmt argument:
 */
#define XKVL_UNPACK_NOW 0x400000

ComENTRY XKVResult XKVListUpdate(XKVList *kv, XKVList *delta, int update_mode);

#define XKVL_MODE_MASK 0xF00 /* update mode:                                 */
#define XKVL_MERGE     0x000 /*   merge delta into the list, replacing pairs */
#define XKVL_UPDATE    0x100 /*   only update pairs that already exist       */
#define XKVL_APPEND    0x200 /*   append delta to the end of the list        */
#define XKVL_SUBTRACT  0x300 /*   _subtract_ delta from original list        */

#define XKVL_RECURSIVE 0x800000
#define XKVL_XML_MODE  0x000020

/*----------------------------------------------------- Input / Output ------*/

ComENTRY void XKVListPrint(void *f, XKVList *kvl, const char *header);

ComENTRY char *XKVListToString(XKVList *xkvl);
ComENTRY XKVList *XKVListFromString(const char *string);

ComENTRY int XKVListGetNumOfPairs(XKVList *xkvl);

/*-------------------------------------------------------- XML-ization ------*/

ComENTRY XKVPair 
  *XKVListGetElem    (XKVList *kvl, const char *tag, XKVResult *result),
  *XKVListGetNextElem(XKVList *kvl, const char *tag, XKVResult *result);

ComENTRY void XKVListPrintXML(void *f, XKVList *kvl, const char *header);

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _KVLIST_H */
