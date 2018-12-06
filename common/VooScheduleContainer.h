//
// Created by vinir on 05/12/2018.
//

#ifndef AIRPORT_CONTROL_SORT_VOOSCHEDULE_H
#define AIRPORT_CONTROL_SORT_VOOSCHEDULE_H

#include "../base.h"
#include "VooSchedule.h"

typedef struct __VSContainer *VSContainer;

typedef int8_t(*VSContainer_Comparator)(VooSchedule, VooSchedule);

struct VSContainer_SortStats {
    uint32_t comps;
    uint32_t moves;
};

enum VSContainer_SortType {
    VSCONTAINER_BUBBLE,
    VSCONTAINER_SELECTION,
    VSCONTAINER_INSERTION,
    VSCONTAINER_SHELL,
    VSCONTAINER_QUICK,
    VSCONTAINER_HEAP
};

VSContainer VSContainer_new(size_t initialSize);

void VSContainer_insert(VSContainer, VooSchedule);

void VSContainer_insertAt(VSContainer, size_t pos, VooSchedule);

void VSContainer_fillEmpty(VSContainer, size_t length);

struct VSContainer_SortStats VSContainer_sort(VSContainer, enum VSContainer_SortType, VSContainer_Comparator);

VSContainer VSContainer_clone(VSContainer);

void VSContainer_deleteClone(VSContainer);

void VSContainer_delete(VSContainer);

#endif //AIRPORT_CONTROL_SORT_VOOSCHEDULE_H
