#ifndef _AIRPORT_CONTROL_COMMON_VOO_H
#define _AIRPORT_CONTROL_COMMON_VOO_H

#include "../base.h"
#include "FlightData.h"
#include "VID.h"

typedef struct __Voo *Voo;

Voo Voo_new(FlightData takeoff, FlightData landing);

HSETTER(Voo, VID, Vid);

HSETTER(Voo, FlightData, Takeoff);

HSETTER(Voo, FlightData, Landing);

void Voo_print(Voo);

void Voo_delete(Voo instance);

#endif // _AIRPORT_CONTROL_COMMON_VOO_H
