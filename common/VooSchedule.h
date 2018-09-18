#ifndef _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H
#define _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H

#include "../base.h"
#include "Voo.h"
#include "VooList.h"

typedef struct __VooSchedule *VooSchedule;

struct VooSchedule_SearchResult {
    uint8_t hour, minute;
    VooList list;
};

VooSchedule VooSchedule_new();

void VooSchedule_insert(VooSchedule, Voo);

void VooSchedule_remove(VooSchedule, VID);

void VooSchedule_find(VooSchedule, VID);

void VooSchedule_forEach(VooSchedule, Time takeOff, Time landing, void(*)(Voo));

struct VooSchedule_SearchResult VooSchedule_findPeakTime(VooSchedule);

struct VooSchedule_SearchResult VooSchedule_findOffPeakTime(VooSchedule);

struct VooSchedule_SearchResult VooSchedule_MostRecentUpdated(VooSchedule);

struct VooSchedule_SearchResult VooSchedule_LessRecentUpdated(VooSchedule);

bool VooSchedule_IsSparse(VooSchedule);

void VooSchedule_delete(VooSchedule instance);

#endif // _AIRPORT_CONTROL_COMMON_VOOSCHEDULE_H
