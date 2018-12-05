#ifndef MY_SEARCHTABLE_DOTH_
#define MY_SEARCHTABLE_DOTH_


#include <sys/types.h>

typedef struct searchtable_t {
    int amount_of_lines;
    off_t* array_of_line_offsets;
    off_t* array_of_line_lengths;
} searchtable;

searchtable build_searchtable(int file_id);

void delete_searchtable(searchtable* cur);

#endif
