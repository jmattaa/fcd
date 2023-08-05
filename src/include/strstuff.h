#ifndef FCD_STRSTUFF_H
#define FCD_STRSTUFF_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

const char *HighlightSubstr(const char *source, const char *substring);
void PrintHighlightedString(const char *ansiString, WINDOW *win);
void PrintFullStringHighlight(const char *str, WINDOW *win);

#endif
