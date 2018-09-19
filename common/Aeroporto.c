#include "Aeroporto.h"
#include <string.h>

struct __Aeroporto {
    char *Name;
};

static Aeroporto *storage = NULL;
static unsigned int storageLength = 0;

Aeroporto Aeroporto_get(char *Name) {
    for (unsigned int i = 0; i < storageLength; ++i) {
        if (strcmp(storage[i]->Name, Name) == 0) {
            return storage[i];
        }
    }
    Aeroporto *newArr = realloc(storage, sizeof(void *) * (storageLength + 1));
    if (newArr) {
        storage = newArr;
        Aeroporto air = malloc(sizeof(struct __Aeroporto));
        air->Name = malloc(strlen(Name));
        strcpy(air->Name, Name);
        storage[storageLength++] = air;
        return air;
    }
    FATAL("Failed to allocate memory");
}

GETTER(Aeroporto, char*, Name);
