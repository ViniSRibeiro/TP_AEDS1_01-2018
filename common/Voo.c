#include "Voo.h"

struct __Voo {
    VID Vid;
    FlightData Takeoff;
    FlightData Landing;
};

Voo Voo_new(FlightData takeoff, FlightData landing) {
    Voo instance = malloc(sizeof(struct __Voo));
    instance->Vid = UUID();
    instance->Takeoff = takeoff;
    instance->Landing = landing;
    return instance;
}

SETTER(Voo, VID, Vid);

SETTER(Voo, FlightData, Takeoff);

SETTER(Voo, FlightData, Landing);

void Voo_delete(Voo instance) {
    FlightData_delete(instance->Takeoff);
    FlightData_delete(instance->Landing);
    free(instance);
}

