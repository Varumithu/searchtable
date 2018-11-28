
#include "searchtable.h"


#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 100
#define INITIAL_SIZE 10


searchtable build_searchtable(char* filename) {
    ssize_t currently_allocated_for_offset_array = INITIAL_SIZE;
    searchtable res;
    res.array_of_line_offsets = malloc(INITIAL_SIZE * sizeof(off_t));
    int file_id = open(filename, O_RDONLY);

    if (file_id == -1 || res.array_of_line_offsets == NULL) {
        res.amount_of_lines = -1;
        return res;
    }
    char buf[BUF_SIZE];
    ssize_t amount_of_characters_read = BUF_SIZE;
    while (amount_of_characters_read == BUF_SIZE) {
        amount_of_characters_read = read(file_id, buf, BUF_SIZE);
        for (ssize_t i = 0; i < amount_of_characters_read; ++i) {
            if (buf[i] == '\n') {
                ++res.amount_of_lines;
                if (res.amount_of_lines > currently_allocated_for_offset_array) {
                    res.array_of_line_offsets = realloc(res.array_of_line_offsets, res.amount_of_lines + INITIAL_SIZE);
                    currently_allocated_for_offset_array = res.amount_of_lines + INITIAL_SIZE;
                    if (res.array_of_line_offsets == NULL) {
                        res.amount_of_lines = -1;
                        return res;
                    }

                }
            }
        }
        if (amount_of_characters_read < BUF_SIZE)
            break;
    }
    return res;
}






