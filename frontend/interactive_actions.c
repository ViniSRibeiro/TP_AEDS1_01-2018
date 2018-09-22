#include "interactive_actions.h"
#include <stdio.h>

static void PRINT3(VooSchedule nothing) {
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
}

struct Action actions[] = {
        {"Test", PRINT3},
        /*{"Inserir voo", ...},
        {"Remover voo", ...},
        {"Procurar voo", ...},
        {"Listar voos", ...},*/
};

int numOfActions() {
    return sizeof(actions) / sizeof(struct Action);
}
