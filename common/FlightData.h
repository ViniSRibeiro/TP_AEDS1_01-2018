#include "../base.h"
#include "Time.h"
#include "Aeroporto.h"

typedef struct __FlightData *FlightData;

FlightData FlightData_new(Time schedule, Aeroporto airport, int8_t runway);

void FlightData_delete(FlightData instance);

