#ifndef _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H
#define _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H

#include "../base.h"

typedef struct __VooSchedule *VooSchedule;

VooSchedule VooSchedule_new();

void VooSchedule_delete(VooSchedule instance);

#endif // _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H
