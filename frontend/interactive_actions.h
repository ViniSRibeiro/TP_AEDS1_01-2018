#ifndef AIRPORT_CONTROL_INTERACTIVE_ACTIONS_H
#define AIRPORT_CONTROL_INTERACTIVE_ACTIONS_H

struct Action {
    char *name;

    void (*action)();
};

void PRINT();

extern struct Action actions[];

int numOfActions();

#endif //AIRPORT_CONTROL_INTERACTIVE_ACTIONS_H
