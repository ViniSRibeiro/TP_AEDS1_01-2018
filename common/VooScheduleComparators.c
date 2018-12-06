//
// Created by vinic on 12/5/2018.
//

#include "VooScheduleComparators.h"

struct ComparatorEntry comparators[] = {
        {"ASD", NULL}
};

int numOfComparators() {
    return sizeof(comparators) / sizeof(struct ComparatorEntry);
}

