#ifndef FCD_DIRS_H
#define FCD_DIRS_H

#include "list_node.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void GetSubDirs(const char *path, ListNode **head);

#endif
