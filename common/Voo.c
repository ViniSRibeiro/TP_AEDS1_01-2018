#include "Voo.h"

struct __Voo {
};

Voo Voo_new() {
  Voo instance = malloc(sizeof(struct __Voo));
  return instance;
}

void Voo_delete(Voo instance) {
    free(instance);
}

