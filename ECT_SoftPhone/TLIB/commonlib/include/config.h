/*
 * $Id: config.h,v 1.17 2002/06/20 00:47:22 epi Exp $
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "com_types.h"

#ifdef __cplusplus
extern "C" {
#endif

ComENTRY int conf_read_file       (const char *file_name),
             conf_re_read_file    (const char *file_name),
             conf_set_current_file(const char *file_name);

ComENTRY char *conf_get_current_file(void);
ComENTRY char 
  *conf_get_option     (const char *server_name, const char *option_name),
  *conf_get_next_option(const char *server_name, const char *option_name);
ComENTRY char 
  *conf_get_next_server(const char *server_name),
  *conf_get_next_num_server(int num),
  *conf_find_server_name(const char *home_location, const char *server_type);

ComENTRY int conf_is_server_exist(const char *server_name),
             conf_walk_server(const char *server_name,
                       int (*callback)(char *opt_name, char *opt_value));

ComENTRY void conf_clear_all(void);
ComENTRY void 
  conf_clear_option(const char *server_name, const char *option_name),
  conf_set_option  (const char *server_name, const char *option_name,
                                             const char *option_value);
#ifdef _XKVLIST_H
  ComENTRY XKVList *conf_to_xkvlist(const char *server_name);
#endif
ComENTRY void conf_print_options(void *f_void);
ComENTRY int conf_write_file(const char *file_name);

#ifdef __cplusplus
}
#endif
#endif /* __CONFIG_H */

