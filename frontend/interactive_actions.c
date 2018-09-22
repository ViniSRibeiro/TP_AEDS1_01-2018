#include "interactive_actions.h"
#include <stdio.h>

static void PRINT3(VooSchedule nothing) {
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
}
#define NOP PRINT3
struct Action actions[] = {
        {"Test", PRINT3},
        {"Inserir voo", NOP},
        {"Remover voo", NOP},
        {"Procurar voo", NOP},
        {"Listar voos", NOP},
        {"Horario de maior movimentacao", NOP},
        {"Horario de menor movimentacao", NOP},
        {"Lista recentemente alterada", NOP},
        {"Lista alterada a mais tempo", NOP},
        {"Matriz esparca?", NOP},
};

int numOfActions() {
    return sizeof(actions) / sizeof(struct Action);
}
