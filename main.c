#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "searchtable.h"

int main(){
    int file_id = open("/home/valmit/Documents/misc/text.txt", O_RDONLY);
    if (file_id < 0) {
        exit(1);
    }
    searchtable table = build_searchtable(file_id);
    int input = 1;
    int dump;
    while (input != '0' ) {
        if (scanf("%d", &input) != 1) {
            dump = getc(stdin);
            continue;
        }
        if ((input <= table.amount_of_lines) && (input != 0)) {
            char* buf = malloc(sizeof(char) * table.array_of_line_lengths[input - 1]);
            pread(file_id, buf, table.array_of_line_lengths[input - 1], table.array_of_line_offsets[input - 1]);
            write(STDOUT_FILENO, buf, table.array_of_line_lengths[input - 1]);
            buf[0] = '\n';
            write(STDOUT_FILENO, "\n", 1);
            free(buf);
        }
    }
    delete_searchtable(&table);
}
