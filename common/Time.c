#include "Time.h"

struct __Time {
};

Time Time_new() {
  Time instance = malloc(sizeof(struct __Time));
  return instance;
}

void Time_delete(Time instance) {
    free(instance);
}

