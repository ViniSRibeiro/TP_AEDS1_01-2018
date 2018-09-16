#include "../base.h"

typedef struct __Time *Time;

/**
 * Instantiate a new Time
 * \param hour Hour between [0,24)
 * \param minute Minute between [0,24)
 * \see Time
 */
Time Time_new(uint8_t hour, uint8_t minute);

HSETTER(Time, uint8_t, Hour)
HSETTER(Time, uint8_t, Minute)

int Time_compareTo(Time this, Time other);

void Time_delete(Time instance);


