#ifndef MY_SEARCHTABLE_DOTH_
#define MY_SEARCHTABLE_DOTH_


#include <sys/types.h>

typedef struct searchtable_t {
    size_t amount_of_lines;
    off_t* offsets;
    off_t* lengths;
} searchtable;

searchtable build_searchtable(int file_id);

void delete_searchtable(searchtable* cur);

#endif
