#ifndef MY_SEARCHTABLE_DOTH_
#define MY_SEARCHTABLE_DOTH_


#include <sys/types.h>

typedef struct searchtable_t {
    int amount_of_lines;
    off_t* array_of_line_offsets;
} searchtable;

searchtable build_searchtable(char* filename);

void delete_searchtable(searchtable* cur);

#endif
