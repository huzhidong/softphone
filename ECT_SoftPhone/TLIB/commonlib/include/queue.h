/*
 * $Id: queue.h,v 1.1 1995/11/10 19:20:14 green Exp $
 */

#define INSERT_QUEUE(QUEUE, ELEM, PREV, NEXT) \
{ \
  if (QUEUE == NULL) { \
    ELEM->NEXT = ELEM->PREV = NULL; \
    QUEUE = ELEM; \
  } else { \
    ELEM->NEXT = QUEUE; \
    ELEM->PREV = NULL; \
    ELEM->NEXT->PREV = QUEUE = ELEM; \
  } \
}

#define DELETE_QUEUE(QUEUE, ELEM, PREV, NEXT) \
{ \
  if (QUEUE == ELEM) { \
    QUEUE = ELEM->NEXT; \
    if (QUEUE != NULL) \
      QUEUE->PREV = NULL; \
  } else { \
    ELEM->PREV->NEXT = ELEM->NEXT; \
    if (ELEM->NEXT != NULL) \
      ELEM->NEXT->PREV = ELEM->PREV; \
  } \
}

#define INSERT_TAILED_QUEUE_AT_TOP(TOP, TAIL, ELEM, PREV, NEXT) \
{ \
  if (TOP == NULL) { \
    ELEM->NEXT = ELEM->PREV = NULL; \
    TOP = TAIL = ELEM; \
  } else { \
    ELEM->NEXT = TOP; \
    ELEM->PREV = NULL; \
    ELEM->NEXT->PREV = TOP = ELEM; \
  } \
}

#define INSERT_TAILED_QUEUE_AT_TAIL(TOP, TAIL, ELEM, PREV, NEXT) \
{ \
  if (TOP == NULL) { \
    ELEM->NEXT = ELEM->PREV = NULL; \
    TOP = TAIL = ELEM; \
  } else { \
    ELEM->NEXT = NULL; \
    ELEM->PREV = TAIL; \
    ELEM->PREV->NEXT = TAIL = ELEM; \
  } \
}

#define DELETE_TAILED_QUEUE(TOP, TAIL, ELEM, PREV, NEXT) \
{ \
  if (TAIL == ELEM) \
    TAIL = ELEM->PREV; \
  if (TOP == ELEM) { \
    TOP = ELEM->NEXT; \
    if (TOP != NULL) \
      TOP->PREV = NULL; \
  } else { \
    ELEM->PREV->NEXT = ELEM->NEXT; \
    if (ELEM->NEXT != NULL) \
      ELEM->NEXT->PREV = ELEM->PREV; \
  } \
}
