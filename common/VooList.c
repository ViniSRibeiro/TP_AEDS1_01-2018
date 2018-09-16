#include "VooList.h"

struct __VooList {
};

VooList VooList_new() {
  VooList instance = malloc(sizeof(struct __VooList));
  return instance;
}

void VooList_delete(VooList instance) {
    free(instance);
}

