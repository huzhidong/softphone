/* $Id: avltree.h /main/6 16-Sep-2003.11:04:27 PST epi $
 */
#ifndef _AVLTREE_H
#define _AVLTREE_H

#include "com_types.h"

#ifdef __cplusplus
extern "C" {
#endif
struct avlt_node_struct; typedef struct avlt_node_struct avlt_node_t;
struct avlt_tree_struct; typedef struct avlt_tree_struct avlt_tree_t;
/*
 * The key in our AVL trees may be either integer or pointer to some field
 * iside data structure; in either case, it shall fit into 'long' on all
 * supported platforms, and doesn't require any memory deallocation (but may
 * require user-supplied comparison function):
 */
typedef long avlt_key_t;
typedef int (*avlt_compare_key_f)(avlt_key_t k1, avlt_key_t k2);
/*
 * The data is supposed to be always allocated by user, but deallocation will
 * be done automatically in functions avlt_delete and avlt_destoy_tree, so the
 * deallocator function shall be supplied:
 */
typedef void *avlt_data_t;
typedef void (*avlt_destroy_data_f)(avlt_data_t data);
/*
 * The following function creates empty tree with any type of key/data:
 */
ComENTRY avlt_tree_t *avlt_create_tree(avlt_compare_key_f  compare_key_func,
                                       avlt_destroy_data_f destroy_data_func);
/*
 * For convinience, two most common cases are covered by the following tree
 * creation function:
 */
ComENTRY avlt_tree_t 
  *avlt_tree_with_int_key   (avlt_destroy_data_f destroy_data_func),
  *avlt_tree_with_string_key(avlt_destroy_data_f destroy_data_func);
/*
 * To avoid memory leaks, any non-static tree must be deleted by using the
 * following function:
 */
ComENTRY void avlt_destroy_tree(avlt_tree_t *tree);
/*
 * LIMITATIONS: (1) If integer keys are used, they're supposed not to spread
 * over the whole range of 'long' type (the difference between any two keys
 * shall not cause overflow).
 *
 * (2) Because back references to the parent in the tree is not kept for
 * performance reasons, the maximum height of the tree has to be limited
 * (insert/delete algorythms need to keep path to the node from the root):
 */
#define AVL_MAX_TREE_HEIGHT 64

/*-----------------------------------------------------------------------------
 * Insert function returns pointer to the new node... which is not very useful,
 * besides the fact that NULL indicates error condition (won't happen unless
 * parameters are incorrect - if there's such key already in the tree, pointer
 * to existing node will be returned, and data will be REPLACED):
 */
ComENTRY avlt_node_t *avlt_insert(avlt_tree_t *tree, avlt_key_t key, 
                                                     avlt_data_t data);
/*
 * Delete functions returns 0 to indicate error condition, and some positive
 * integer in case of success; in the latter case the associated data will
 * be destroyed by calling deallocator supplied when tree was created:
 */
ComENTRY int avlt_delete(avlt_tree_t *tree, avlt_key_t key);
/*
 * Data may be retrieved from the tree by using:
 */
ComENTRY avlt_data_t avlt_find_data(avlt_tree_t *tree, avlt_key_t key);
/*
 * The tree may be walked through (in order of ascendance) by using functions
 * that take callback as an argument (the walk will be stopped when callback
 * returns non-zero value; this value will be returned as result):
 */
typedef int (*avlt_walk_callback_f)(avlt_data_t item, avlt_data_t addtl_param);
ComENTRY int avlt_tree_walk(avlt_tree_t *tree,
                avlt_walk_callback_f callback, avlt_data_t addtl_param);

typedef int (*avlt_walk_ex_callback_f)(avlt_key_t item_key,
                     avlt_data_t item, avlt_data_t addtl_param);
ComENTRY int avlt_tree_walk_ex(avlt_tree_t *tree,
                avlt_walk_ex_callback_f callback, avlt_data_t addtl_param);
/*
 * Next function also walks the tree, but it returns the data of the first node
 * for which callback function returns non-zero value:
 */
ComENTRY avlt_data_t avlt_find_by_func (avlt_tree_t *tree,
                            avlt_walk_callback_f callback, avlt_data_t param);
/*
 * Finally, the following function prints the tree structure (along with keys
 * and balancing information, but without data) into specified stream (or into
 * standard CommonLib output, if 'thru_comlib' - defined in cmnlog.h - is used)
 */
ComENTRY void avlt_print_tree(void *stream, const char *title,
                         avlt_tree_t *tree, const char *fmt_for_key_printout);

#ifdef __cplusplus
}
#endif
#endif /* _AVLTREE_H */

