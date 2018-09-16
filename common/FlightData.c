#include "FlightData.h"

struct __FlightData {
    Time Schedule;
    Aeroporto Airport;
    int8_t Runway;
};

FlightData FlightData_new(Time Schedule, Aeroporto Airport, int8_t Runway) {
    FlightData instance = malloc(sizeof(struct __FlightData));
    instance->Schedule = Schedule;
    instance->Airport = Airport;
    instance->Runway = Runway;
    return instance;
}

GETTER(FlightData, Time, Schedule);

GETTER(FlightData, Aeroporto, Airport);

GETTER(FlightData, int8_t, Runway);

void FlightData_delete(FlightData instance) {
    Time_delete(instance->Schedule);
    Aeroporto_delete(instance->Airport);
    free(instance);
}
