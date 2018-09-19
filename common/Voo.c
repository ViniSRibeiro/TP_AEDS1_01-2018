#include "Voo.h"

struct __Voo {
    VID Vid;
    FlightData Takeoff;
    FlightData Landing;
};

Voo Voo_new(FlightData takeoff, FlightData landing) {
    Voo instance = malloc(sizeof(struct __Voo));
    instance->Vid = UUID(); // NOLINT(cert-msc30-c,cert-msc50-cpp)
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

void Voo_print(Voo this) {
    FlightData takeOff = Voo_getTakeoff(this);
    Time takeOffTime = FlightData_getSchedule(takeOff);
    FlightData landing = Voo_getLanding(this);
    Time landingTime = FlightData_getSchedule(landing);

    PRINTLN("============="
            "\nVoo %08X"
            "\n>>>Decolagem"
            "\n|  %02d:%02d %s - Pista #%d"
            "\n>>>Pouso"
            "\n|  %02d:%02d %s",
            this->Vid.bits,
            Time_getHour(takeOffTime), Time_getMinute(takeOffTime),
            Aeroporto_getName(FlightData_getAirport(takeOff)),
            FlightData_getRunway(takeOff),

            Time_getHour(landingTime), Time_getMinute(landingTime),
            Aeroporto_getName(FlightData_getAirport(landing))
    );
}

