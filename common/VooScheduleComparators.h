//
// Created by vinic on 12/5/2018.
//

#ifndef AIRPORT_CONTROL_VOOSCHEDULECOMPARATORS_H
#define AIRPORT_CONTROL_VOOSCHEDULECOMPARATORS_H

#include "VooScheduleContainer.h"

struct ComparatorEntry {
    char *name;
    VSContainer_Comparator action;
};

extern struct ComparatorEntry comparators[];

extern int numOfComparators();

#endif //AIRPORT_CONTROL_VOOSCHEDULECOMPARATORS_H
