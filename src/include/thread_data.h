#ifndef FCD_THREADDATA_H
#define FCD_THREADDATA_H

#include <pthread.h>
#include "list_node.h"

typedef struct 
{
    ListNode *Head;
    const char *path;
    pthread_mutex_t mutex;
} ThreadData;

#endif
