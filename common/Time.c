#include "Time.h"
#include <time.h>

struct __Time {
    uint8_t Hour;
    uint8_t Minute;
};

Time Time_new(uint8_t hour, uint8_t minute) {
    ASSERT(0 <= hour && hour < 24, "Hour must be between [0,24)");
    ASSERT(0 <= minute && minute < 60, "Minute must be between [0,60)");
    Time instance = malloc(sizeof(struct __Time));
    instance->Hour = hour;
    instance->Minute = minute;
    return instance;
}

Time Time_now() {
    time_t n = time(NULL);
    struct tm *now = localtime(&n);
    return Time_new((uint8_t) now->tm_hour, (uint8_t) now->tm_min);
}

SETTER(Time, uint8_t, Hour)
SETTER(Time, uint8_t, Minute)

void Time_updateToNow(Time this) {
    time_t n = time(NULL);
    struct tm *now = localtime(&n);
    this->Hour = (uint8_t) now->tm_hour;
    this->Minute = (uint8_t) now->tm_min;
}

int Time_compareTo(Time this, Time other) {
    if(this == NULL || other == NULL) {
        if(this != NULL) {
            return 1;
        }
        if(other != NULL) {
            return 1;
        }
        return 0;
    }
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

