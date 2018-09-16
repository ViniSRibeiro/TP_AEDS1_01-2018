#include "Voo.h"
#include <time.h>

struct __Voo {
    VID Vid;
    FlightData Takeoff;
    FlightData Landing;
};

static bool needSeed = true;

Voo Voo_new(FlightData Takeoff, FlightData Landing) {
    if (needSeed) {
        needSeed = false;
        srand((unsigned int) time(NULL));
    }
    Voo instance = malloc(sizeof(struct __Voo));
    instance->Vid = (VID) random();
    instance->Takeoff = Takeoff;
    instance->Landing = Landing;
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

