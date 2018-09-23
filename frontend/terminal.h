//
// Created by viniciuslrangel on 22/09/18.
//

#ifndef AIRPORT_CONTROL_TERMINAL_H
#define AIRPORT_CONTROL_TERMINAL_H

#include <stdio.h>

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

extern int (*readCh)();
extern int cols, rows;

#ifdef _WIN32

HANDLE hStdout;

enum Attributes {
    A_OFF = 0,
    A_BOLD = FOREGROUND_INTENSITY,
    A_UNDERSCORE = 0x8000,
    A_BLINK_ON = 0,
    A_REVERSE_VIDEO = 0x4000,
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
#define RAW() (void)0
#define UNRAW() (void)0
#else
#define CLEAR() ESC("2J")
#define RAW() system("/bin/stty raw")
#define UNRAW() system("/bin/stty -raw")
#endif
#define DEFAULT_COLOR() color(A_BOLD, F_WHITE, B_YELLOW)
#define DEFAULT_COLOR_SELECTED() color(A_BOLD, F_WHITE, B_MAGENTA)
#define DEFAULT_COLOR_RUNNING() color(A_BOLD, F_WHITE, B_BLACK)

void color(enum Attributes attr, enum FColors fore, enum BColors back);

void pos(int line, int column);

#endif //AIRPORT_CONTROL_TERMINAL_H
