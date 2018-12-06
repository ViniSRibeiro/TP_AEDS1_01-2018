#include "Aeroporto.h"
#include <string.h>

struct __Aeroporto {
    char *Name;
};

static Aeroporto *storage        = NULL;
static size_t    storageLength   = 0;
static size_t    storageCapacity = 0;

Aeroporto Aeroporto_get(char *Name) {
    for (unsigned int i = 0; i < storageLength; ++i) {
        if (strcmp(storage[i]->Name, Name) == 0) {
            return storage[i];
        }
    }
    if (storageLength == storageCapacity) {
        storageCapacity = (size_t) (storageCapacity < 4 ? storageCapacity + 1 : storageCapacity * 1.5);
        storage         = realloc(storage, sizeof(void *) * storageCapacity);
        if (!storage) {
            FATAL("Failed to allocate memory to create new Aeroport");
        }
    }
    Aeroporto air = malloc(sizeof(struct __Aeroporto));
    air->Name = malloc(strlen(Name));
    strcpy(air->Name, Name);
    storage[storageLength++] = air;
    return air;

}

GETTER(Aeroporto, char*, Name);
