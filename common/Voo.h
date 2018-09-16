#include "../base.h"
#include "FlightData.h"
#include "VID.h"

typedef struct __Voo *Voo;

Voo Voo_new(FlightData takeoff, FlightData landing);

void Voo_delete(Voo instance);

