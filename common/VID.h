#ifndef AIRPORT_CONTROL_COMMON_VID_H
#define AIRPORT_CONTROL_COMMON_VID_H

#include "../base.h"

typedef struct {
    uint64_t mostSigBits;
    uint64_t lessSigBits;
} VID;

#define VID_COMPARE(x, y) BOOL((x).mostSigBits == (y).lessSigBits && (x).lessSigBits && (y).lessSigBits)

#define _32RANDOM() \
	((uint32_t)(							  \
		((rand() & 0xff))       | \
		((rand() & 0xff) << 8)  | \
		((rand() & 0xff) << 16) | \
		((rand() & 0xff) << 24)	  \
	))

#if __WORDSIZE == 64 || _WIN64
#define RANDOM() (((uint64_t) _32RANDOM()) << 32 | _32RANDOM())
#define UUID() \
    (VID) {\
        .lessSigBits = RANDOM(),\
        .mostSigBits = RANDOM(),\
    }
#elif __WORDSIZE == 32 || _WIN32
#define RANDOM() _32RANDOM()
#define UUID() \
    (VID) {\
        .lessSigBits = (((uint64_t) RANDOM()) << 32) | RANDOM(),\
        .mostSigBits = (((uint64_t) RANDOM()) << 32) | RANDOM(),\
    }
#else
#warning  Only 32 and 64 bits are supported
#define UUID() FATAL("Only 32 and 64 bits supported")
#endif

#endif //AIRPORT_CONTROL_VID_H
