#include "../base.h"
#include "FlightData.h"

typedef uint32_t VID;

typedef struct __Voo *Voo;

Voo Voo_new(FlightData Takeoff, FlightData Landing);

void Voo_delete(Voo instance);

