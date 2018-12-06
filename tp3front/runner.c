//
// Created by vinic on 12/6/2018.
//

#include <stdio.h>
#include "runner.h"
#include "../common/VooScheduleComparators.h"

#ifdef WIN32

#include <windows.h>

double get_time() {
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double) t.QuadPart / (double) f.QuadPart;
}

#else
#include <sys/time.h>
#include <sys/resource.h>
double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}
#endif

struct SortAction {
    char                      *name;
    enum VSContainer_SortType type;
};

struct SortAction sorts[]    = {
        {"Bubble",    VSCONTAINER_BUBBLE},
        {"Selection", VSCONTAINER_SELECTION},
        {"Insertion", VSCONTAINER_INSERTION},
        {"Shell",     VSCONTAINER_SHELL},
        {"Quick",     VSCONTAINER_QUICK},
        {"Heap",      VSCONTAINER_HEAP}
};
const uint32_t    sortsCount = sizeof(sorts) / sizeof(struct SortAction);

void allSortsAndPrint(VSContainer container) {
    for (uint32_t i = 0; i < sortsCount; ++i) {
        VSContainer   instance = VSContainer_clone(container);
        for (uint32_t j        = 0; j < numOfComparators(); ++j) {
            double                       time  = get_time();
            struct VSContainer_SortStats stats = VSContainer_sort(instance, sorts[i].type, comparators[j].action);
            time = get_time() - time;
            PRINTLN("+-----------------------");
            PRINTLN("| %s sorting - Condition: %s", sorts[i].name, comparators[j].name);
            PRINTLN("| Total time  : %f seg", time);
            PRINTLN("| Comparisons : %d", stats.comps);
            PRINTLN("| Moves       : %d seg", stats.moves);
            PRINTLN("+-----------------------\n");
        }
        VSContainer_delete(instance);
    }
}
