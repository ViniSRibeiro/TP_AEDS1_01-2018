#include "Aeroporto.h"
#include <string.h>

struct __Aeroporto {
	char *name;
	int refs;
};

static Aeroporto *storage = NULL;
static unsigned int storageLength = 0;

Aeroporto Aeroporto_get(char* name) {
	for (unsigned int i = 0; i < storageLength; ++i) {
		if (strcmp(storage[i]->name, name) == 0) {
			storage[i]->refs++;
			return storage[i];
		}
	}
	Aeroporto *newArr = realloc(storage, storageLength + 1);
	if (newArr) {
		storage = newArr;
		Aeroporto air = malloc(sizeof(struct __Aeroporto));
		air->name = malloc(strlen(name));
		strcpy(air->name, name);
		air->refs = 1;
		storage[storageLength++] = air;
		return air;
	}
	FATAL("Failed to allocate memory");
}

void Aeroporto_delete(Aeroporto instance) {
	for (unsigned int i = 0; i < storageLength; ++i) {
		if (instance == storage[i]) {
			if(--instance->refs == 0) {
				free(instance->name);
				free(instance);
			}
			break;
		}
	}
}

