//
// Created by vinic on 12/6/2018.
//

#include <time.h>
#include "container_generator.h"

static inline Time readTime(FILE *file) {
    int hour, minute;
    if(!fscanf(file, "%d:%d", &hour, &minute)) { // NOLINT(cert-err34-c)
        FATAL("Missing more flight data");
    }
    return Time_new((uint8_t) hour, (uint8_t) minute);
}

static inline Voo readFlight(FILE *file) {
    Time  takeOff = readTime(file);
    Time  landing = readTime(file);
    char  takeOffAirport[4];
    char  landingAirport[4];
    short runway;
    if(!fscanf(file, "%s %s %hd", takeOffAirport, landingAirport, &runway)) { // NOLINT(cert-err34-c)
        FATAL("Invalid flight data");
    }
    return Voo_new(
            FlightData_new(takeOff, Aeroporto_get(takeOffAirport), 0),
            FlightData_new(landing, Aeroporto_get(landingAirport), (int8_t) runway)
    );
}

bool parse_file(struct DataInfo info, FILE *file, VSContainer *output) {
    VSContainer container = VSContainer_new(info.vectorSize);

    uint32_t *indexList = malloc(sizeof(uint32_t) * info.toFill);

    for (size_t i = 0; i < info.toFill; ++i) {
        if (!fscanf(file, "%ud", &indexList[i])) { // NOLINT(cert-err34-c)
            FATAL("Missing more indexes");
        }
    }

    for (size_t i = 0; i < info.toFill; ++i) {
        VooSchedule schedule = VooSchedule_newId(indexList[i]);
        for (size_t j        = 0; j < info.eachMatrix; ++j) {
            VooSchedule_insert(schedule, readFlight(file));
        }
        VSContainer_insert(container, schedule);
    }
    VSContainer_fillEmpty(container, info.vectorSize);

    free(indexList);

    *output = container;
    return true;
}

static inline Time randTime() {
    return Time_new((uint8_t) (rand() % 24), (uint8_t) (rand() % 60)); // NOLINT(cert-msc30-c,cert-msc50-cpp)
}

static inline Aeroporto randAirport() {
    const int step = 'Z' - 'A' + 1;
    char      codes[4];
    codes[3] = 0;
    for (uint8_t i = 0; i < 3; ++i) {
        codes[i] = (char) ('A' + (rand() % step)); // NOLINT(cert-msc30-c,cert-msc50-cpp)
    }
    return Aeroporto_get(codes);
}

VSContainer random_data(struct DataInfo info) {
    VSContainer container = VSContainer_new(info.vectorSize);
    srand((unsigned int) time(NULL)); // NOLINT(cert-msc32-c,cert-msc51-cpp)

    for (size_t i = 0; i < info.toFill; ++i) {
        VooSchedule schedule = VooSchedule_newId((uint32_t) (rand() % info.vectorSize)); // NOLINT(cert-msc30-c,cert-msc50-cpp)

        for (size_t j = 0; j < info.eachMatrix; ++j) {
            VooSchedule_insert(
                    schedule,
                    Voo_new(
                            FlightData_new(randTime(), randAirport(), 0),
                            FlightData_new(
                                    randTime(),
                                    randAirport(),
                                    (int8_t) (rand() % 20)) // NOLINT(cert-msc30-c,cert-msc50-cpp)
                    )
            );
        }
        VSContainer_insert(container, schedule);
    }
    VSContainer_fillEmpty(container, info.vectorSize);
    return container;
}
