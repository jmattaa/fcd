#include "include/dirs.h"
#include <pthread.h>

void GetSubDirs(const char *path, ListNode **head, pthread_mutex_t *mutex) 
{
    DIR *dir = opendir(path);
    if (!dir) 
    {
        //printf("Error opening directory: %s\n\r", path);
        //perror("\rError");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // make sure the entry is a directory not a file
        if (entry->d_type == DT_DIR)
        {
            // skip the '.' and '..' directories
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char subdirpath[2048];
                sprintf(subdirpath, "%s/%s", path, entry->d_name);

                pthread_mutex_lock(mutex);
                ListNode_AddNode(head, subdirpath);
                pthread_mutex_unlock(mutex);

                GetSubDirs(subdirpath, head, mutex);
            }
        }
    }

    closedir(dir);
}

