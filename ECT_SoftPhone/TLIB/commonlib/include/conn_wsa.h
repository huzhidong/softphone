#ifndef __conn_wsa_h
#define __conn_wsa_h
/**
 * Copyright (c) 2005 Genesys Telecommunications Labs, Inc, All Rights Reserved
 * File: conn_wsa.h
 * Project: Genesys Common library
 * Creation date: April 21, 2005
 * Description:
 *  Windows WSAAsyncSelect support for common library
 *
 */
#include <connection.h>
#include <conn_socket.h>

#ifdef __cplusplus
extern "C"{
#endif
typedef enum _CONN_WSA_STARTUP_FLAGS
{
	CONN_WSA_DEBUG				=	1,			/* Debug tracing related to this functionality */
	CONN_WSA_DEBUG_EVENTS		=	2			/* Trace window message (can be too much)  */
}CONN_WSA_STARTUP_FLAGS;


#define CONN_WSA_TIMER_RATE 10

#define CONN_WSA_NO_TIMER   		-1
#define CONN_WSA_DEFAULT_TIMER_RATE	0

typedef struct _CONN_WSA_STARTUP
{
	int 	flags;                 /* IN 		Combination of CONN_WSA_STARTUP_FLAGS */
	int 	timerid;               /* IN 		Timer id or 0 for default, (default library timer id is 1) */
	int 	timerRate;             /* IN 		Timer processing rate or 0, (default library rate is 10ms) */
	HWND 	hWnd;                  /* IN/OUT 	Window for socket related messages */
	UINT 	wMsg;                  /* IN 		Windows message number, default WM_USER+1 */
}CONN_WSA_STARTUP;

/**
 * Initilize network layer according to startup arguments
 * \param startup - optional startup parameters, when 0 libary will use defaults
 *
 *	1. hWnd
 *		a. 	If hWnd specified, then library will use provided hWnd
 *    	b. 	If hWnd specified and wMsg != 0, then library will use specified message id
 *    	c. 	If hWnd not specified, library will register window class and create window
 *      	for Windows Socket notification handling. Window handle will be stored into 
 *      	CONN_WSA_STARTUP hWnd field
 *	2. timerRate
 *		a.	When timerRate is CONN_WSA_DEFAULT_TIMER_RATE, library will use default timer processing rate.
 *		b. 	When timerRate is CONN_WSA_NO_TIMER, library will not install timer, 
 *			and it is application responsibility to call conn_process_timers.
 *  3. timerid 
 *		a. Ignored when window created by library
 *		b. Used as is when hWnd provided by application and timerRate is not CONN_WSA_NO_TIMER
 *  4. wMsg
 *		a. Ignored when window created by library
 *		b. Used as is when hWnd provided by application
 *  5. flags - see CONN_WSA_STARTUP_FLAGS description
 *
 * \return 0 - on success, -1 on error
 */
int conn_wsa_startup(CONN_WSA_STARTUP* startup);

/**
 * Poll messages, mostly used for debugging purpose
 * \param flags 	- reserverd must be 0
 * \param timeout   - pool timeout, 0 - infinite
 * \return 0 - on success, -1 on error
 */
int conn_wsa_poll(int flags,int timeout);

/**
 * Handle result of WSAAsyncSelect
 * Function shall be used in case when application hWnd is specified
 * \param hWnd	 	- window parameter of application WindowProc
 * \param wParam	- wParam parameter of application WindowProc
 * \param lParam	- lParam parameter of application WindowProc
 */
int conn_wsa_handle_event(HWND hWnd,WPARAM wParam,LPARAM lParam);

/**
 * Cleanup network layer
 * \return 0 - on success, -1 on error
 * When neccessary 
 * 		CloseWindow
 * 		Unregister window class
 *      Kill timer
 */
int conn_wsa_cleanup(void);

#ifdef __cplusplus
}
#endif
#endif
