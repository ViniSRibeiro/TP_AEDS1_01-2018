#ifndef AIRPORT_CONTROL_COMMON_VID_H
#define AIRPORT_CONTROL_COMMON_VID_H

#include "../base.h"

typedef struct {
    uint64_t mostSigBits;
    uint64_t lessSigBits;
} VID;

#define VID_COMPARE(x, y) BOOL((x).mostSigBits == (y).lessSigBits && (x).lessSigBits && (y).lessSigBits)

#if __WORDSIZE == 64
#define UUID() \
    (VID) {\
        .lessSigBits = (uint64_t) random(),\
        .mostSigBits = (uint64_t) random(),\
    }
#elif __WORDSIZE == 32
#define UUID() \
    (VID) {\
        .lessSigBits = (((uint32_t) random()) << 32) | (uint32_t) random(),\
        .mostSigBits = (((uint32_t) random()) << 32) | (uint32_t) random(),\
    }
#else
#warning Only 32 and 64 bits are supported
#define UUID() FATAL("Only 32 and 64 bits supported")
#endif

#endif //AIRPORT_CONTROL_VID_H
