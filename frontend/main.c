#include <stdlib.h>
#include <time.h>
#include "read_file.h"
#include "interactive.h"

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));

    if (argc > 1) {
        return ParseFile(argv[1]);
    } else {
        Interactive(VooSchedule_new());
    }
}