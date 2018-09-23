#include "interactive.h"
#include <stdio.h>
#include <string.h>
#include "interactive_actions.h"

#include "terminal.h"

int centerX, centerY, selected = 0;
int nOfActions;
int maxLength = 0;
int halfY, halfX;

void drawActions() {

#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cols = w.ws_col;
	rows = w.ws_row;
#endif

	centerX = cols / 2;
	centerY = rows / 2;

	maxLength = cols - 24;

	halfY = nOfActions / 2;
	halfX = maxLength / 2;

    DEFAULT_COLOR();
    CLEAR();
    for (int i = 4; i < cols - 4; ++i) {
        pos(i, 4);
        PC('-');
        pos(i, rows - 4);
        PC('-');
    }
    for (int i = 5; i < rows - 4; ++i) {
        pos(4, i);
        PC('|');
        pos(cols - 4, i);
        PC('|');
    }
	for (int i = 0; i < 4; ++i) {
		pos(4 + (cols - 8) * (i / 2), 4 + (rows - 8) * (i % 2));
		PC('+');
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

int input() {
#ifdef _WIN32
	int first = _getch();
	return first == 0 || first == 0xE0 ? _getch() : first;
#else
    int c = getchar();
    if (c == 4 || c == 3) {
        UNRAW();
        DEFAULT_COLOR_RUNNING();
        CLEAR();
        exit(0);
    }
    return c;
#endif
}

void Interactive(VooSchedule schedule) {

#ifdef _WIN32
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
#else
    RAW();
#endif
	readCh = input;

    nOfActions = numOfActions();

    while (drawActions(), 1) {
        int c = readCh();
        switch (c) {
#ifdef _WIN32
			case 72:
				upArrow();
				break;
			case 80:
				downArrow();
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
                pos(0, 0);

                UNRAW();
                actions[selected].action(schedule);
                RAW();
				readCh();
            }
				break;
			default:
				break;			
        }
    }
}
