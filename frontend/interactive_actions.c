#include "interactive_actions.h"
#include <stdio.h>

void PRINT() {
    printf("PRINTED");
}

struct Action actions[] = {
        {"TEST", PRINT},
        {"TEST2", PRINT},
        {"ANOTHER ACTION", PRINT}
};

int numOfActions() {
    return sizeof(actions) / sizeof(struct Action);
}
