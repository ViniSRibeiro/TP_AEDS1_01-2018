#include "interactive_actions.h"
#include <stdio.h>

static void PRINT() {
    puts("PRINTED");
}

static void PRINT2() {
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
}

static void PRINT3() {
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
	puts("PRINTED");
}

struct Action actions[] = {
        {"TEST", PRINT},
        {"TEST2", PRINT2},
        {"ANOTHER ACTION", PRINT3}
};

int numOfActions() {
    return sizeof(actions) / sizeof(struct Action);
}
