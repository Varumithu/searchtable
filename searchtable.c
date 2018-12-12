
#include "searchtable.h"


#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 100
#define INITIAL_SIZE 10


void delete_searchtable(searchtable* cur) {
    free(cur->offsets);
    cur->offsets = NULL;
    free(cur->lengths);
    cur->offsets = NULL;
}


searchtable build_searchtable(int file_id) {
    size_t currently_allocated_for_offset_array = INITIAL_SIZE;
    searchtable res;
    res.amount_of_lines = 1;
    res.offsets = malloc(INITIAL_SIZE * sizeof(off_t));
    res.lengths = malloc(INITIAL_SIZE * sizeof(off_t));
    if (file_id == -1 || res.offsets == NULL || res.lengths == NULL) {
        res.offsets = NULL;
        res.lengths = NULL;
        return res;
    }
    res.offsets[0] = 0;
    char buf[BUF_SIZE];
    off_t cur_pos = 0;
    ssize_t amount_of_characters_read = BUF_SIZE;
    while (amount_of_characters_read == BUF_SIZE) {
        amount_of_characters_read = read(file_id, buf, BUF_SIZE);
        for (ssize_t i = 0; i < amount_of_characters_read; ++i) {
            if (buf[i] == '\n') {
                ++res.amount_of_lines;
                if (res.amount_of_lines > currently_allocated_for_offset_array) {
                    res.offsets = realloc(res.offsets, (res.amount_of_lines + INITIAL_SIZE) * sizeof (off_t));
                    res.lengths = realloc(res.lengths, (res.amount_of_lines + INITIAL_SIZE) * sizeof (off_t));
                    currently_allocated_for_offset_array = res.amount_of_lines + INITIAL_SIZE;
                    if (res.offsets == NULL || res.lengths == NULL) {
                        res.offsets = NULL;
                        res.lengths = NULL;
                        return res;
                    }
                }
                res.offsets[res.amount_of_lines - 1] = cur_pos + 1;
                res.lengths[res.amount_of_lines - 2] = res.offsets[res.amount_of_lines - 1] -
                                                       res.offsets[res.amount_of_lines - 2];

            }
            ++cur_pos;
        }
//        if (amount_of_characters_read < BUF_SIZE) {
//            res.lengths[res.amount_of_lines - 1] = amount_of_characters_read - res.offsets[res.amount_of_lines - 2];
//        }

    }
    if (res.amount_of_lines > 1) {
        -- res.amount_of_lines;
        res.lengths[res.amount_of_lines] = cur_pos - res.offsets[res.amount_of_lines];
    }

    return res;
}






