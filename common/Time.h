#ifndef _AIRPORT_CONTROL_COMMON_TIME_H
#define _AIRPORT_CONTROL_COMMON_TIME_H

#include "../base.h"

typedef struct __Time *Time;

/**
 * Instantiate a new Time
 * \param hour Hour between [0,24)
 * \param minute Minute between [0,24)
 * \see Time
 */
Time Time_new(uint8_t hour, uint8_t minute);

Time Time_now();

HSETTER(Time, uint8_t, Hour)
HSETTER(Time, uint8_t, Minute)

void Time_updateToNow(Time);

int Time_compareTo(Time this, Time other);

void Time_delete(Time instance);

#endif // _AIRPORT_CONTROL_COMMON_TIME_H
