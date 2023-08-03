#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int ListSubDirs(const char *path) 
{
    DIR *dir = opendir(path);
    if (!dir) 
    {
        printf("Error opening directory: %s\n", path);
        perror("Error opening directory");
        exit(1);
        return 1;
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
                printf("%s/%s\n", path, entry->d_name);
                char subdirpath[512];
                sprintf(subdirpath, "%s/%s", path, entry->d_name);
                ListSubDirs(subdirpath);
            }
        }
    }

    closedir(dir);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) 
    {
        printf("Usage: fcd <directory>\n");
        return 1;
    }

    ListSubDirs(argv[1]);

    return 0;
}
