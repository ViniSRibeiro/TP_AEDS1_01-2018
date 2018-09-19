#include "FlightData.h"

struct __FlightData {
    Time Schedule;
    Aeroporto Airport;
    int8_t Runway;
};

FlightData FlightData_new(Time schedule, Aeroporto airport, int8_t runway) {
    FlightData instance = malloc(sizeof(struct __FlightData));
    instance->Schedule = schedule;
    instance->Airport = airport;
    instance->Runway = runway;
    return instance;
}

GETTER(FlightData, Time, Schedule);

GETTER(FlightData, Aeroporto, Airport);

GETTER(FlightData, int8_t, Runway);

void FlightData_delete(FlightData instance) {
    Time_delete(instance->Schedule);
    free(instance);
}
