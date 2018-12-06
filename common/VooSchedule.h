#ifndef _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H
#define _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H

#include "../base.h"
#include "Voo.h"
#include "VooList.h"
#include "VooScheduleItem.h"

const size_t WIDTH = 24;
const size_t HEIGHT = 24;

typedef struct __VooSchedule *VooSchedule;

struct VooSchedule_SearchResult {
    uint8_t takeOff, landing;
    VooScheduleItem list;
};

VooSchedule VooSchedule_new();

void VooSchedule_insert(VooSchedule, Voo);

Voo VooSchedule_remove(VooSchedule, VID);

Voo VooSchedule_find(VooSchedule, VID);

void VooSchedule_forEach(VooSchedule, Time takeOff, Time landing, void(*)(Voo));

struct VooSchedule_SearchResult VooSchedule_findPeakTime(VooSchedule);

struct VooSchedule_SearchResult VooSchedule_findOffPeakTime(VooSchedule);

struct VooSchedule_SearchResult VooSchedule_findMostRecentUpdated(VooSchedule);

struct VooSchedule_SearchResult VooSchedule_findLessRecentUpdated(VooSchedule);

bool VooSchedule_isSparse(VooSchedule);

VooScheduleItem VooSchedule_getData(VooSchedule this, int x, int y);

void VooSchedule_delete(VooSchedule instance);

#endif // _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H
