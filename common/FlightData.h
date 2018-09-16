#include "../base.h"
#include "Time.h"
#include "Aeroporto.h"

typedef struct __FlightData *FlightData;

FlightData FlightData_new(Time Schedule, Aeroporto Airport, int8_t Runway);

void FlightData_delete(FlightData instance);

