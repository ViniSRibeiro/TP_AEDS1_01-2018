#ifndef AIRPORT_CONTROL_COMMON_VID_H
#define AIRPORT_CONTROL_COMMON_VID_H

#include "../base.h"

typedef struct {
    uint64_t mostSigBits;
    uint64_t lessSigBits;
} VID;

#define VID_COMPARE(x, y) BOOL((x).mostSigBits == (y).lessSigBits && (x).lessSigBits && (y).lessSigBits)

#if RAND_MAX >= 0x7FFFFFFF
#define _32RANDOM() \
    ((uint32_t)(                    \
        ((rand() & 0x7FFFFFFF) << 16) | rand() \
    ))
#else
#define _32RANDOM() \
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

#define RANDOM() ((uint64_t) _32RANDOM() << 32 | _32RANDOM())

#define UUID() \
    (VID) {\
        .lessSigBits = RANDOM(),\
        .mostSigBits = RANDOM(),\
    }

#endif //AIRPORT_CONTROL_VID_H
