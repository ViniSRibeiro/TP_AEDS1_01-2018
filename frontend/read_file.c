#include "read_file.h"
#include "../base.h"

int parse_file(char *fileName) {

    char *buffer;
    {
        FILE *f;
        if ((f = fopen(fileName, "r")) == NULL) {
            ERRORLN("Could not open %s for reading", fileName);
            return 1;
        }
        fseek(f, 0, SEEK_END);
        unsigned long length = (unsigned long) ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if (buffer == NULL)
            FATAL("Could not allocate memory for file reading");
        fread(buffer, 1, length, f);
        fclose(f);
    }
    //  file reading

    return 0;
}
