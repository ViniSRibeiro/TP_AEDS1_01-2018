#include "VooSchedule.h"

struct __VooSchedule {
};

VooSchedule VooSchedule_new() {
  VooSchedule instance = malloc(sizeof(struct __VooSchedule));
  return instance;
}

void VooSchedule_delete(VooSchedule instance) {
    free(instance);
}

