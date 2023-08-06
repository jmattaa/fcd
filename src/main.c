#include <curses.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <ncurses.h>

#include "include/dirs.h"
#include "include/list_node.h"
#include "include/mainrun.h"

// BUG the selected directory contains escape characters that turn on and off coloring 

int main(int argc, char **argv)
{
    //! do not forget to initialize with NULL!!!!!!
    //! I HATE SIGSEGV
    ListNode *Head = NULL;

    if (argc < 2)
    {
        // if no arguments, use home directory
        struct passwd *pw = getpwuid(getuid());
        GetSubDirs(pw->pw_dir, &Head);
    }
    else
        GetSubDirs(argv[1], &Head);

    MainRun(Head);


    // free memory
    ListNode_RemoveAll(Head);

    return 0;
}
