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
#define ESC(x) P("\033["x)
#define PF(x, ...) printf(x, ##__VA_ARGS__)

int cols, rows, centerX, centerY, selected = 0;
int nOfActions;
int maxLength = 0;
int halfY, halfX;

int (*readCh)();

#ifdef _WIN32

HANDLE hStdout;

enum Attributes {
	A_OFF = 0,
	A_BOLD = FOREGROUND_INTENSITY,
	A_UNDERSCORE = COMMON_LVB_UNDERSCORE,
	A_BLINK_ON = 0,
	A_REVERSE_VIDEO = COMMON_LVB_REVERSE_VIDEO,
	A_CONCEALED_ON = 0
};

enum FColors {
	F_BLACK = 0,
	F_RED = FOREGROUND_RED,
	F_GREEN = FOREGROUND_GREEN,
	F_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	F_BLUE = FOREGROUND_BLUE,
	F_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
	F_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	F_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
};

enum BColors {
	B_BLACK = 0,
	B_RED = BACKGROUND_RED,
	B_GREEN = BACKGROUND_GREEN,
	B_YELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
	B_BLUE = BACKGROUND_BLUE,
	B_MAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
	B_CYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
	B_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
};

#else

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

#endif

#ifdef _WIN32
#define CLEAR() system("cls")
#else
#define CLEAR() ESC("2J")
#endif
#define DEFAULT_COLOR() color(A_BOLD, F_WHITE, B_YELLOW)
#define DEFAULT_COLOR_SELECTED() color(A_BOLD, F_WHITE, B_MAGENTA)
#define DEFAULT_COLOR_RUNNING() color(A_BOLD, F_WHITE, B_BLACK)

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

void upArrow() {
	if (selected > 0) {
		selected--;
	}
}

void downArrow() {
	if (selected < nOfActions - 1) {
		selected++;
	}
}

int interactive() {

#ifdef _WIN32
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    readCh = _getch;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
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
#ifdef _WIN32
			case 224: {
				c = readCh();
				if(c == 72) {
					upArrow();
				} else if(c == 80) {
					downArrow();
				}
			};
				break;
#else
            case '\033': {
                if (readCh() == '[') {
                    c = readCh();
                    if (c == 'A') {
						upArrow();
                    } else if (c == 'B') {
						downArrow();
                    }
                }
            };
                break;
#endif
            case '\r': {
                DEFAULT_COLOR_RUNNING();
                CLEAR();
                pos(1, 1);
                actions[selected].action();
                readCh();
            }
				break;
			default:
				break;			
        }
    }
}
