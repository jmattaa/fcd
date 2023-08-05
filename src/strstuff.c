#include "include/strstuff.h"
#include <curses.h>

const char *HighlightSubstr(const char *source, const char *substring) 
{
    const char *start = strstr(source, substring);

    if (start != NULL) 
    {
        size_t substringLength = strlen(substring);
        size_t prefixLength = start - source;

        char *highlighted = (char *)malloc(strlen(source) + 16 + 1); // 16 for escape codes, +1 for null terminator
        // me very smart
        // \x1Bo = on 
        // \x1Bn = off
        sprintf(highlighted, "%.*s\x1Bo%.*s\x1Bn%s\n",
                (int)prefixLength, source, (int)substringLength, start, start + substringLength);

        return highlighted;
    }

    return source; // return original string if not found
    // but it must be found
}


void PrintHighlightedString(const char *ansiString, WINDOW *win)
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
 
    // it ain't really ansi it's just me 
    // me smart
    for (int i = 0; ansiString[i] != '\0'; i++)
    {
        if (ansiString[i] == '\x1B')
        {
            i++;
            if (ansiString[i] == 'o')
                wattron(win, COLOR_PAIR(1));
            else 
                wattroff(win, COLOR_PAIR(1));
        }
        else 
        {
            wprintw(win, "%c", ansiString[i]);
        }
    }
}

void PrintFullStringHighlight(const char *str, WINDOW *win)
{
    init_pair(1, COLOR_RED, COLOR_BLACK);

    wattron(win, COLOR_PAIR(1));
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\x1B')
        {
            i++;
        }
        else 
        {
            wprintw(win, "%c", str[i]);
        }
    }
    wattroff(win, COLOR_PAIR(1));
}
