/*
 * $Id: conn_select.h,v 1.3 2000/10/12 00:53:34 epi Exp $
 */

/* select hooks for the integration with HP SS7 */

# define HOOKED_S_ADDR &

/* select hooks. added for HP Opencall integration */

typedef int (*conn_preselect_proc_t)(int num_fd,
			      fd_set *read_mask,
			      fd_set *write_mask,
			      fd_set *exception_mask, struct timeval **time);

typedef int (*conn_postselect_proc_t)(int num_fd,
			      fd_set *read_mask,
			      fd_set *write_mask,
			      fd_set *exception_mask);

/* we will call these hooks only at main select,
   since select in conn_scan_input is called only from libraries,
   and conn_flush_input is never called */

#ifdef __cplusplus
extern "C"
#endif
void conn_set_select_hooks(conn_preselect_proc_t preproc,
			   conn_postselect_proc_t postproc);

