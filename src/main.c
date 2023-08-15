#include <curses.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <ncurses.h>
#include <pthread.h>

#include "include/dirs.h"
#include "include/list_node.h"
#include "include/thread_data.h"

void *getSubDirsInBackground(void *arg) 
{
    ThreadData *threadData = (ThreadData *)arg;
    GetSubDirs(threadData->path, &(threadData->Head), &(threadData->mutex));
    return NULL;
}

int main(int argc, char **argv) 
{
    pthread_t backgroundThread;

    struct passwd *pw = getpwuid(getuid());

    ThreadData threadData = 
    {
        .Head = NULL,
        .path = pw->pw_dir,
        .mutex = PTHREAD_MUTEX_INITIALIZER
    };

    if (pthread_create(&backgroundThread, NULL, getSubDirsInBackground, &threadData) != 0) 
    {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }



    // MainRun

    // init ncurses
    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);

    // get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Calculate dimensions for main section and search bar
    int padding = 2;
    int win_width = max_x - padding; 
    int search_height = 3;
    int search_y = max_y - search_height;
    int search_x = padding / 2; // divide by 2 so there is same amount of space on both sides
    int main_height = max_y - search_height;

    // Create main section window
    WINDOW *main_win = newwin(main_height, win_width, 0, padding / 2);

    // Create the search bar window 
    WINDOW *search_win = newwin(search_height, win_width, search_y, search_x);

    // Initialize variables
    char search_text[512] = "";
    int ch;

    int selected_index = 1;
    int max_index = 0;
    ListNode *selected_dir = NULL;

    // hacky solution to show bar because it only shows when a key is pressed for some weird reason
    ungetch(KEY_BACKSPACE);
    while (1) 
    {
        ch = getch();

        if (ch == KEY_BACKSPACE) 
        {
            int len = strlen(search_text);
            if (len > 0) 
            {
                search_text[len - 1] = '\0';
            }
            wclear(search_win);
        } 
        else if (ch >= 32 && ch <= 126) 
        {
            int len = strlen(search_text);
            if (len < sizeof(search_text) - 1) 
            {
                search_text[len] = (char)ch;
                search_text[len + 1] = '\0';
            }
        }
        if (ch == KEY_UP) 
        {
            if (selected_index > 1) 
            {
                selected_index--;
            }
        } 
        else if (ch == KEY_DOWN) 
        {
            if (selected_index < max_index - 1) 
            {
                selected_index++;
            }
        }
        else if (ch == '\n' && selected_index > 0) 
        {
            if (selected_dir != NULL)
            {
                FILE *outputFile = fopen("./output.txt", "w");
                if (outputFile == NULL) 
                {
                    perror("Error opening file");
                    break;
                }
                fprintf(outputFile, "%s", selected_dir->data); 
                break;
            }
        }

        if (selected_index > max_index - 1)
            selected_index = 1;

        werase(main_win);

        pthread_mutex_lock(&(threadData.mutex));
        ListNode *search = ListNode_Search(threadData.Head, search_text);
        pthread_mutex_unlock(&(threadData.mutex));

        int current_index = 1;
        while (search != NULL && current_index < main_height) // only show what can be shown on screen
        {
            // move the cursor to the correct position
            wmove(main_win, current_index, 1);
            if (current_index == selected_index)
            {
                // move text?? cool effect?? idk
                wmove(main_win, current_index, padding * 2);
                // print full string with highlight and set it to variable
                PrintFullStringHighlight(search->data, main_win);
                selected_dir = search;
            }
            else
                // display normally 
                wprintw(main_win, "%s", search->data);

            search = search->next;
            current_index++;
        }
        max_index = current_index;

        wborder(main_win, 
                    ACS_VLINE, ACS_VLINE, 
                    ACS_HLINE, ACS_HLINE,
                    ACS_ULCORNER, ACS_URCORNER, 
                    ACS_LLCORNER, ACS_LRCORNER
            );
        mvwprintw(main_win, 0, 0, "%s", search_text);
        wrefresh(main_win);

        // Draw search bar
        wborder(search_win, 
                ACS_VLINE, ACS_VLINE, 
                ACS_HLINE, ACS_HLINE,
                ACS_ULCORNER, ACS_URCORNER, 
                ACS_LLCORNER, ACS_LRCORNER
        );
        mvwprintw(search_win, 1, 1, "Search: %s", search_text);
        wrefresh(search_win);

        refresh();
    }


    // cleanup
    delwin(main_win);
    delwin(search_win);
    endwin();




    // Free memory
    ListNode_RemoveAll(threadData.Head);

    return 0;
}
