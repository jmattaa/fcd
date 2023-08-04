#include "include/dirs.h"

void GetSubDirs(const char *path, ListNode **head) 
{
    DIR *dir = opendir(path);
    if (!dir) 
    {
        printf("Error opening directory: %s\n", path);
        perror("Error");
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
                char subdirpath[512];
                sprintf(subdirpath, "%s/%s", path, entry->d_name);

                ListNode_AddNode(head, subdirpath);
                GetSubDirs(subdirpath, head);
            }
        }
    }

    closedir(dir);
}
