#include "interactive.h"
#include <stdio.h>
#include <string.h>
#include "interactive_actions.h"

#include "terminal.h"

int cols, rows, centerX, centerY, selected = 0;
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

int interactive(VooSchedule schedule) {

#ifdef _WIN32
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    readCh = _getch;
#else
    readCh = getchar;
    RAW();
#endif

    nOfActions = numOfActions();

    while (drawActions(), 1) {
        int c = readCh();
        if (c == 4 || c == 3) {
            RAW();
            return 0;
        }
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
                pos(0, 0);

                UNRAW();
                actions[selected].action(schedule);
                RAW();
#ifndef _WIN32
                readCh();
#else
                getchar();
#endif
            }
				break;
			default:
				break;			
        }
    }
}
