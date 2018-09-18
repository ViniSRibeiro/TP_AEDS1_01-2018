#include "interactive.h"
#include <stdio.h>
#include <string.h>
#include "interactive_actions.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

#endif

#define P(x) fputs(x, stdout)
#define PC(x) fputc(x, stdout)
#define ESC(x) P("\e["x)
#define PF(x, ...) printf(x, ##__VA_ARGS__)

int cols, rows, centerX, centerY, selected = 0;
int nOfActions;
int maxLength = 0;
int halfY, halfX;

int (*readCh)();

enum Attributes {
    A_OFF = 0,
    A_BOLD = 1,
    A_UNDERSCORE = 4,
    A_BLINK_ON = 5,
    A_REVERSE_VIDEO = 7,
    A_CONCEALED_ON = 8
};

enum FColors {
    F_BLACK = 30,
    F_RED = 31,
    F_GREEN = 32,
    F_YELLOW = 33,
    F_BLUE = 34,
    F_MAGENTA = 35,
    F_CYAN = 36,
    F_WHITE = 37
};

enum BColors {
    B_BLACK = 40,
    B_RED = 41,
    B_GREEN = 42,
    B_YELLOW = 43,
    B_BLUE = 44,
    B_MAGENTA = 45,
    B_CYAN = 46,
    B_WHITE = 47
};
#define CLEAR() ESC("2J")
#define CLEAR_LINE() ESC("K")
#define DEFAULT_COLOR() color(A_BOLD, F_WHITE, B_YELLOW)
#define DEFAULT_COLOR_SELECTED() color(A_BOLD, F_WHITE, B_MAGENTA)
#define DEFAULT_COLOR_RUNNING() color(A_BOLD, F_WHITE, B_BLACK)

void color(enum Attributes attr, enum FColors fore, enum BColors back) {
    PF("\e[%d;%d;%dm", attr, fore, back);
}

void pos(int line, int column) {
    PF("\e[%d;%dH", column, line);
}

void drawActions() {
    DEFAULT_COLOR();
    CLEAR();
    for (int i = 4; i < cols - 4; ++i) {
        pos(i, 4);
        PC('-');
        pos(i, rows - 4);
        PC('-');
    }
    for (int i = 4; i < rows - 3; ++i) {
        pos(4, i);
        PC('|');
        pos(cols - 4, i);
        PC('|');
    }
    for (int i = 0; i < nOfActions; ++i) {
        struct Action ac = actions[i];
        pos(centerX - halfX, centerY - halfY + i);
        if (i == selected) {
            DEFAULT_COLOR_SELECTED();
        }
        PF("%-*s", maxLength, ac.name);
        if (i == selected) {
            DEFAULT_COLOR();
        }
    }
    pos(cols, rows);
}

int interactive() {

#ifdef _WIN32
    readCh = _getch;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    readCh = getchar;
    system("/bin/stty raw");
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    cols = w.ws_col;
    rows = w.ws_row;
#endif

    centerX = cols / 2;
    centerY = rows / 2;

    nOfActions = numOfActions();

    maxLength = cols - 24;

    halfY = nOfActions / 2;
    halfX = maxLength / 2;

    while (drawActions(), 1) {
        int c = readCh();
        if (c == 4 || c == 3)
            return 0;
        switch (c) {
            case '\e': {
                if (readCh() == '[') {
                    c = readCh();
                    if (c == 'A') {
                        if (selected > 0) {
                            selected--;
                        }
                    } else if (c == 'B') {
                        if (selected < nOfActions - 1) {
                            selected++;
                        }
                    }
                }
            };
                break;
            case '\r': {
                DEFAULT_COLOR_RUNNING();
                CLEAR();
                pos(1, 1);
                actions[selected].action();
                readCh();
            }
            break;
        }
    }
}
