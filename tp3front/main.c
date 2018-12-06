#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/VooScheduleContainer.h"
#include "container_generator.h"
#include "runner.h"

bool parse(int argc, char **argv) {
    int isReadingFile;

    if (argc < 5) {
        return false;
    } else if (!strcmp(argv[1], "-f") && argc < 6) {
        return false;
    } else if ((isReadingFile = !strcmp(argv[1], "-f")) == 0 && strcmp(argv[1], "-r") != 0) {
        return false;
    }

    char *p;
    errno = 0;
#define READ(x, y) do{ \
    x = strtoull(argv[(y) + isReadingFile], &p, 10);\
    if(*p != '\0' || errno != 0) {\
        ERRORLN("%s is not a valid number", p);\
        return false;\
    }\
} while(0)
    struct DataInfo info;
    READ(info.vectorSize, 2);
    READ(info.toFill, 3);
    READ(info.eachMatrix, 4);
#undef READ

    VSContainer container;

    if (strcmp(argv[1], "-f") == 0) { // READ FROM FILE
        FILE *f = fopen(argv[2], "r");
        if (!f) {
            ERRORLN("Invalid file name %s", argv[2]);
            return false;
        }
        if(!parse_file(info, f, &container)){
            fclose(f);
            return true;
        }
        fclose(f);
    } else {
        container = random_data(info);
    }

    allSortsAndPrint(container);
    VSContainer_delete(container);

    return true;
}

int main(int argc, char **argv) {
    if (!parse(argc, argv)) {
        printf(
                "Usage: %s ...\n\n"
                "\t\t -f file vector_size to_fill each_matrix:\n"
                "\t\t\t\tRead file, create vector of length [vector_size], get [to_fill]\n"
                "\t\t\t\tindexes and fill each index with [each_matrix] flights\n"
                "\n"
                "\t\t -r vector_size to_fill each_matrix]:\n"
                "\t\t\t\tSame as -f but instead of reading file for\n"
                "\t\t\t\tindexes and flights, fill it with random data\n",
                argv[0]
        );
    }
    return 0;
}