#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "include/dirs.h"
#include "include/list_node.h"

int main(int argc, char **argv)
{
    //! do not forget to initialize with NULL!!!!!!
    //! I HATE SIGSEGV
    ListNode *Head = NULL;

    if (argc < 2)
    {
        char cwd[256];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            GetSubDirs(cwd, &Head);
        else
            GetSubDirs(".", &Head);
    }
    else
        GetSubDirs(argv[1], &Head);

    ListNode_PrintAll(Head);
    
    // Remove free memory
    ListNode_RemoveAll(Head);

    return 0;
}
