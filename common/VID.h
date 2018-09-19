#ifndef AIRPORT_CONTROL_COMMON_VID_H
#define AIRPORT_CONTROL_COMMON_VID_H

#include "../base.h"

typedef struct {
    uint32_t bits;
} VID;

#define VID_COMPARE(x, y) BOOL((x).bits == (y).bits)

#if RAND_MAX >= 0x7FFFFFFF
#define RANDOM() \
    ((uint32_t)(                    \
        ((rand() & 0x7FFFFFFF) << 16) | rand() \
    ))
#else
#define RANDOM() \
    ((uint32_t)(							  \
        ((rand() & 0xff))       | \
        ((rand() & 0xff) << 8)  | \
        ((rand() & 0xff) << 16) | \
        ((rand() & 0xff) << 24)	  \
    ))
#if RAND_MAX < 0x7FFF
#warning  Only 32 and 64 bits are supported
#endif
#endif

#define UUID() \
    (VID) {\
        .bits = RANDOM(),\
    }

#endif //AIRPORT_CONTROL_VID_H
