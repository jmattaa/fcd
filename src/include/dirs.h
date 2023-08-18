#ifndef FCD_DIRS_H
#define FCD_DIRS_H

#include "list_node.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

void GetSubDirs(const char *path, ListNode **head, pthread_mutex_t *mutex);

#endif
