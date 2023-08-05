#include "include/mainrun.h"
#include "include/list_node.h"
#include "include/strstuff.h"

void MainRun(ListNode * head) 
{
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

    int selected_index = 0;
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
            if (selected_index < main_height - padding) 
            {
                selected_index++;
            }
        }
        else if (ch == '\n' && selected_index > 0) 
        {
            // cd into selected directory and exit loop
            if (selected_dir != NULL)
                break;
        }
        
        ListNode *search = ListNode_Search(head, search_text);
        ListNode *current = search;
        int current_index = 0;
        while (current != NULL && current_index < main_height) // only show what can be shown on screen
        {
            if (current_index == selected_index)
            {
                // print full string with highlight and set it to variable
                PrintFullStringHighlight(current->data, main_win);
                selected_dir = current;
            }
            else
                // display normally 
                PrintHighlightedString(current->data, main_win);

            current = current->next;
            current_index++;
        }

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
    }


    // cleanup
    delwin(main_win);
    delwin(search_win);
    endwin();
}
