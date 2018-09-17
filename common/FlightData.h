#ifndef _AIRPORT_CONTROL_COMMON_FLIGHTDATA_H
#define _AIRPORT_CONTROL_COMMON_FLIGHTDATA_H

#include "../base.h"
#include "Time.h"
#include "Aeroporto.h"

typedef struct __FlightData *FlightData;

FlightData FlightData_new(Time schedule, Aeroporto airport, int8_t runway);

HGETTER(FlightData, Time, Schedule);

HGETTER(FlightData, Aeroporto, Airport);

HGETTER(FlightData, int8_t, Runway);

void FlightData_delete(FlightData instance);

#endif // _AIRPORT_CONTROL_COMMON_FLIGHTDATA_H
