#include <memory.h>
#include "old_airport.h"
#include "../base.h"

struct __Airport {
    char *name;
};

static Airport *storage = NULL;
static unsigned int storageLength = 0;

Airport Airport_get(char *name) {
    for (unsigned int i = 0; i < storageLength; ++i) {
        if (strcmp(storage[i]->name, name) == 0) {
            return storage[i];
        }
    }
    Airport *newArr = realloc(storage, storageLength + 1);
    if(newArr) {
        storage = newArr;
        Airport air = malloc(sizeof(struct __Airport));
        air->name = malloc(strlen(name));
        strcpy(air->name, name);
        storage[storageLength++] = air;
        return air;
    }
    FATAL("Failed to allocate memory");
}