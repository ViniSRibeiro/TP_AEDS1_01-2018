#ifndef _AIRPORT_CONTROL_COMMON_VOOSCHEDULEITEM_H
#define _AIRPORT_CONTROL_COMMON_VOOSCHEDULEITEM_H

#include "../base.h"
#include "VooList.h"

typedef struct __VooScheduleItem *VooScheduleItem;

VooScheduleItem VooScheduleItem_new();

HGETTER(VooScheduleItem, VooList, List);

HGETTER(VooScheduleItem, Time, LastUpdate);

uint32_t VooScheduleItem_num(VooScheduleItem);

void VooScheduleItem_delete(VooScheduleItem instance);

#endif // _AIRPORT_CONTROL_COMMON_VOOSCHEDULEITEM_H