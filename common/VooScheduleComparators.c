//
// Created by vinic on 12/5/2018.
//

#include "VooScheduleComparators.h"

#define FIRST_TIME(a, b) do {\
    if(a != NULL && Time_compareTo(a, b) < 0) {\
        b = a;\
    }\
} while(0)

#define LAST_TIME(a, b) do {\
    if(a != NULL && Time_compareTo(a, b) > 0) {\
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
    Time timeA = NULL;
    Time timeB = NULL;
    
    for (uint8_t x = 0; x < WIDTH; ++x) {
        for (uint8_t y = 0; y < HEIGHT; ++y) {
            ITERATE_SCHEDULE_ITEM(a, timeA, x, y, FIRST_TIME, firstTimeTakeoff);
            if (timeA != NULL) {
                goto out1;
            }
        }
    }
    out1:
    for (uint8_t x = 0; x < WIDTH; ++x) {
        for (uint8_t y = 0; y < HEIGHT; ++y) {
            ITERATE_SCHEDULE_ITEM(b, timeB, x, y, FIRST_TIME, firstTimeTakeoff);
            if (timeB != NULL) {
                goto out2;
            }
        }
    }
    out2:
    return (int8_t) Time_compareTo(timeA, timeB);
}

static int8_t lastTakeoff(VooSchedule a, VooSchedule b) {
    Time timeA = NULL;
    Time timeB = NULL;

    for (int x = WIDTH - 1; x >= 0; --x) {
        for (int y = HEIGHT - 1; y >= 0; --y) {
            ITERATE_SCHEDULE_ITEM(a, timeA, x, y, LAST_TIME, lastTimeTakeoff);
            if (timeA != NULL) {
                goto out1;
            }
        }
    }
    out1:

    for (int x = WIDTH - 1; x >= 0; --x) {
        for (int y = HEIGHT - 1; y >= 0; --y) {
            ITERATE_SCHEDULE_ITEM(b, timeB, x, y, LAST_TIME, lastTimeTakeoff);
            if (timeB != NULL) {
                goto out2;
            }
        }
    }
    out2:

    return (int8_t) Time_compareTo(timeB, timeA);
}

static int8_t firstLanding(VooSchedule a, VooSchedule b) {
    Time timeA = NULL;
    Time timeB = NULL;

    for (uint8_t y = 0; y < HEIGHT; ++y) {
        for (uint8_t x = 0; x < WIDTH; ++x) {
            ITERATE_SCHEDULE_ITEM(a, timeA, x, y, FIRST_TIME, firstTimeLanding);
            if (timeA != NULL) {
                goto out1;
            }
        }
    }
    out1:

    for (uint8_t y = 0; y < HEIGHT; ++y) {
        for (uint8_t x = 0; x < WIDTH; ++x) {
            ITERATE_SCHEDULE_ITEM(b, timeB, x, y, FIRST_TIME, firstTimeLanding);
            if (timeB != NULL) {
                goto out2;
            }
        }
    }
    out2:

    return (int8_t) Time_compareTo(timeA, timeB);
}

static int8_t lastLanding(VooSchedule a, VooSchedule b) {
    Time timeA = NULL;
    Time timeB = NULL;

    for (int y = HEIGHT - 1; y >= 0; --y) {
        for (int x = WIDTH - 1; x >= 0; --x) {
            ITERATE_SCHEDULE_ITEM(a, timeA, x, y, LAST_TIME, lastTimeLanding);
            if (timeA != NULL) {
                goto out1;
            }
        }
    }
    out1:

    for (int y = HEIGHT - 1; y >= 0; --y) {
        for (int x = WIDTH - 1; x >= 0; --x) {
            ITERATE_SCHEDULE_ITEM(b, timeB, x, y, LAST_TIME, lastTimeLanding);
            if (timeB != NULL) {
                goto out2;
            }
        }
    }
    out2:

    return (int8_t) Time_compareTo(timeB, timeA);
}

static int8_t index(VooSchedule a, VooSchedule b) {
    uint32_t first = VooSchedule_getId(a);
    uint32_t second = VooSchedule_getId(b);
    if(first < second) {
        return -1;
    }
    if(first > second) {
        return 1;
    }
    return 0;
}

struct ComparatorEntry comparators[] = {
        {"Index compare", index},
        {"First takeoff", firstTakeoff},
        {"Last takeoff",  lastTakeoff},
        {"First landing", firstLanding},
        {"Last landing",  lastLanding},
};

int numOfComparators() {
    return sizeof(comparators) / sizeof(struct ComparatorEntry);
}

