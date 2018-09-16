#include "FlightData.h"

struct __FlightData {
};

FlightData FlightData_new() {
  FlightData instance = malloc(sizeof(struct __FlightData));
  return instance;
}

void FlightData_delete(FlightData instance) {
    free(instance);
}

