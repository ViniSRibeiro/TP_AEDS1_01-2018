//
// Created by vinic on 12/5/2018.
//

#include "VooScheduleComparators.h"

#define FIRST_TIME(a, b) do {\
    if(b == NULL || (a != NULL && Time_compareTo(a, b) < 0)) {\
        b = a;\
    }\
} while(0)

#define LAST_TIME(a, b) do {\
    if(b == NULL || (a != NULL && Time_compareTo(a, b) > 0)) {\
        b = a;\
    }\
} while(0)

Time buffer;

static void firstTimeTakeoff(Voo voo) {
    FIRST_TIME(FlightData_getSchedule(Voo_getTakeoff(voo)), buffer);
}

static void firstTimeLanding(Voo voo) {
    FIRST_TIME(FlightData_getSchedule(Voo_getLanding(voo)), buffer);
}

static void lastTimeTakeoff(Voo voo) {
    LAST_TIME(FlightData_getSchedule(Voo_getTakeoff(voo)), buffer);
}

static void lastTimeLanding(Voo voo) {
    LAST_TIME(FlightData_getSchedule(Voo_getLanding(voo)), buffer);
}

#define ITERATE_SCHEDULE_ITEM(a, o, x, y, func, iter) do {\
    VooScheduleItem item = VooSchedule_getData(a, x, y);\
    buffer = NULL;\
    VooList_forEach(VooScheduleItem_getList(item), iter);\
    func(buffer, o);\
} while(0)


static int8_t firstTakeoff(VooSchedule a, VooSchedule b) {
    Time         timeA = NULL;
    Time         timeB = NULL;
    for (uint8_t x     = 0; x < WIDTH; ++x) {
        for (uint8_t y = 0; y < HEIGHT; ++y) {
            ITERATE_SCHEDULE_ITEM(a, timeA, x, y, FIRST_TIME, firstTimeTakeoff);
            ITERATE_SCHEDULE_ITEM(b, timeB, x, y, FIRST_TIME, firstTimeTakeoff);
        }
    }
    return (int8_t) Time_compareTo(timeA, timeB);
}

static int8_t lastTakeoff(VooSchedule a, VooSchedule b) {
    Time         timeA = NULL;
    Time         timeB = NULL;
    for (uint8_t x     = 0; x < WIDTH; ++x) {
        for (uint8_t y = 0; y < HEIGHT; ++y) {
            ITERATE_SCHEDULE_ITEM(a, timeA, x, y, LAST_TIME, lastTimeTakeoff);
            ITERATE_SCHEDULE_ITEM(b, timeB, x, y, LAST_TIME, lastTimeTakeoff);
        }
    }
    return (int8_t) Time_compareTo(timeB, timeA);
}

static int8_t firstLanding(VooSchedule a, VooSchedule b) {
    Time         timeA = NULL;
    Time         timeB = NULL;
    for (uint8_t x     = 0; x < WIDTH; ++x) {
        for (uint8_t y = 0; y < HEIGHT; ++y) {
            ITERATE_SCHEDULE_ITEM(a, timeA, x, y, FIRST_TIME, firstTimeLanding);
            ITERATE_SCHEDULE_ITEM(b, timeB, x, y, FIRST_TIME, firstTimeLanding);
        }
    }
    return (int8_t) Time_compareTo(timeA, timeB);
}

static int8_t lastLanding(VooSchedule a, VooSchedule b) {
    Time         timeA = NULL;
    Time         timeB = NULL;
    for (uint8_t x     = 0; x < WIDTH; ++x) {
        for (uint8_t y = 0; y < HEIGHT; ++y) {
            ITERATE_SCHEDULE_ITEM(a, timeA, x, y, LAST_TIME, lastTimeLanding);
            ITERATE_SCHEDULE_ITEM(b, timeB, x, y, LAST_TIME, lastTimeLanding);
        }
    }
    return (int8_t) Time_compareTo(timeB, timeA);
}

struct ComparatorEntry comparators[] = {
        {"First takeoff", firstTakeoff},
        {"Last takeoff",  lastTakeoff},
        {"First landing", firstLanding},
        {"Last landing",  lastLanding},
};

int numOfComparators() {
    return sizeof(comparators) / sizeof(struct ComparatorEntry);
}

