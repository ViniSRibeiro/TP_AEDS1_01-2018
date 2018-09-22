#ifndef AIRPORT_CONTROL_INTERACTIVE_ACTIONS_H
#define AIRPORT_CONTROL_INTERACTIVE_ACTIONS_H

#include "../common/VooSchedule.h"

struct Action {
    char *name;

    void (*action)(VooSchedule);
};

extern struct Action actions[];

int numOfActions();

#endif //AIRPORT_CONTROL_INTERACTIVE_ACTIONS_H
