#include "Aeroporto.h"

struct __Aeroporto {
};

Aeroporto Aeroporto_new() {
  Aeroporto instance = malloc(sizeof(struct __Aeroporto));
  return instance;
}

void Aeroporto_delete(Aeroporto instance) {
    free(instance);
}

