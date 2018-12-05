
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
    free(cur->array_of_line_offsets);
    cur->array_of_line_offsets = NULL;
    free(cur->array_of_line_lengths);
    cur->array_of_line_offsets = NULL;
}


searchtable build_searchtable(int file_id) {
    ssize_t currently_allocated_for_offset_array = INITIAL_SIZE;
    searchtable res;
    res.amount_of_lines = 1;
    res.array_of_line_offsets = malloc(INITIAL_SIZE * sizeof(off_t));
    res.array_of_line_lengths = malloc(INITIAL_SIZE * sizeof(off_t));
    if (file_id == -1 || res.array_of_line_offsets == NULL || res.array_of_line_lengths == NULL) {
        res.amount_of_lines = -1;
        return res;
    }
    res.array_of_line_offsets[0] = 0;
    char buf[BUF_SIZE];
    ssize_t amount_of_characters_read = BUF_SIZE;
    while (amount_of_characters_read == BUF_SIZE) {
        amount_of_characters_read = read(file_id, buf, BUF_SIZE);
        for (ssize_t i = 0; i < amount_of_characters_read; ++i) {
            if (buf[i] == '\n') {
                ++res.amount_of_lines;
                if (res.amount_of_lines > currently_allocated_for_offset_array) {
                    res.array_of_line_offsets = realloc(res.array_of_line_offsets, res.amount_of_lines + INITIAL_SIZE);
                    res.array_of_line_lengths = realloc(res.array_of_line_lengths, res.amount_of_lines + INITIAL_SIZE);
                    currently_allocated_for_offset_array = res.amount_of_lines + INITIAL_SIZE;
                    if (res.array_of_line_offsets == NULL || res.array_of_line_lengths == NULL) {
                        res.amount_of_lines = -1;
                        return res;
                    }
                }
                off_t cur_pos = lseek(file_id, 0, SEEK_CUR) + 1;
                res.array_of_line_offsets[res.amount_of_lines - 1] = cur_pos - (amount_of_characters_read - i);
                res.array_of_line_lengths[res.amount_of_lines - 2] = res.array_of_line_offsets[res.amount_of_lines - 1] - res.array_of_line_offsets[res.amount_of_lines - 2] - 1;

            }
        }
        if (amount_of_characters_read < BUF_SIZE) {
            res.array_of_line_lengths[res.amount_of_lines - 1] = amount_of_characters_read - res.array_of_line_offsets[res.amount_of_lines - 2];
        }
    }
    res.array_of_line_lengths[res.amount_of_lines - 1] = amount_of_characters_read - res.array_of_line_offsets[res.amount_of_lines - 2];
    return res;
}






