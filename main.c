#include <stdio.h>
#include <unistd.h>

#include "searchtable.h"

int main(){
    searchtable table = build_searchtable("/home/valmit/Documents/QtProjects/searchtable/text.txt");
    short input = 1;
    while (input != 0) {
        read(STDOUT_FILENO, &input, 1);
        if (input < table.amount_of_lines) {

        }
    }
}
