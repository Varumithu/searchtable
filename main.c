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
    while (input != 0) {
        if (scanf("%d", &input) != 1) {
            printf("unrecognized input\n");
            scanf("%*s");
            continue;
        }
        if ((input <= table.amount_of_lines) && (input != 0)) {
            char* buf = malloc(sizeof(char) * (size_t)(table.lengths[input - 1]));
            pread(file_id, buf, table.lengths[input - 1], table.offsets[input - 1]);
            write(STDOUT_FILENO, buf, (size_t)(table.lengths[input - 1]));
            buf[0] = '\n';
            free(buf);
        }
        else if (input > table.amount_of_lines) {
            printf("amount of lines exceeded\n");
        }
    }
    delete_searchtable(&table);
}
