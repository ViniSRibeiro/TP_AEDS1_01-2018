#include "Time.h"

struct __Time {
    uint8_t Hour;
    uint8_t Minute;
};

Time Time_new(uint8_t hour, uint8_t minute) {
    ASSERT(0 <= hour && hour < 24, "Hour must be between [0,24)");
    ASSERT(0 <= minute && minute < 24, "Minute must be between [0,60)");
    Time instance = malloc(sizeof(struct __Time));
    instance->Hour = hour;
    instance->Minute = minute;
    return instance;
}

SETTER(Time, uint8_t, Hour)
SETTER(Time, uint8_t, Minute)

int Time_compareTo(Time this, Time other) {
    if (this->Hour < other->Hour)
        return -1;
    if (this->Hour > other->Hour)
        return 1;
    if (this->Minute < other->Minute)
        return -1;
    if (this->Minute > other->Minute)
        return 1;
    return 0;
}

void Time_delete(Time instance) {
    free(instance);

}

