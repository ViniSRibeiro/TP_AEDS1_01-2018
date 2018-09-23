//
// Created by viniciuslrangel on 22/09/18.
//

#include "terminal.h"

int (*readCh)() = NULL;
int cols, rows;

void color(enum Attributes attr, enum FColors fore, enum BColors back) {
#ifdef _WIN32
    SetConsoleTextAttribute(hStdout, attr | fore | back);
#else
    PF("\033[%d;%d;%dm", attr, fore, back);
#endif
}

void pos(int line, int column) {
#ifdef _WIN32
    SetConsoleCursorPosition(hStdout, (COORD) {
        .X = line,
        .Y = column
    });
#else
    PF("\033[%d;%dH", column, line);
#endif
}
