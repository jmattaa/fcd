#include "include/strstuff.h"

const char *HighlightSubstr(const char *source, const char *substring) 
{
    const char *start = strstr(source, substring);

    if (start != NULL) 
    {
        size_t substringLength = strlen(substring);
        size_t prefixLength = start - source;

        char *highlighted = (char *)malloc(strlen(source) + 16 + 1); // 16 for escape codes, +1 for null terminator
        sprintf(highlighted, "%.*s\x1B[1;31m%.*s\x1B[0m%s",
                (int)prefixLength, source, (int)substringLength, start, start + substringLength);

        return highlighted;
    }

    return source; // return original string if not found
    // but it must be found
}
