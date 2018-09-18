#include "VooSchedule.h"
#include "VooScheduleItem.h"

#define ITERATE(a, b) \
for (int x = 0; x < WIDTH; ++x) \
    for (int y = 0; y < HEIGHT; ++y) {\
        VooScheduleItem it = a->data[x][y];\
        b;\
    }\
(void)0

#define WIDTH 24
#define HEIGHT 24
struct __VooSchedule {
    VooScheduleItem data[WIDTH][HEIGHT];
};

VooSchedule VooSchedule_new() {
    VooSchedule instance = malloc(sizeof(struct __VooSchedule));
    for (int x = 0; x < WIDTH; ++x)
        for (int y = 0; y < HEIGHT; ++y)
            instance->data[x][y] = VooScheduleItem_new();
    return instance;
}

void VooSchedule_insert(VooSchedule this, Voo voo) {
    // TODO
}

void VooSchedule_remove(VooSchedule this, VID vid) {
    // TODO
    // Use a funcao VID_COMPARE() para comparar os vid's, retorna um bool
}

void VooSchedule_find(VooSchedule this, VID vid) {
    // TODO
}

inline void _VooSchedule_forEachInternal(VooScheduleItem list, void(*target)(Voo));
void _VooSchedule_forEachInternal(VooScheduleItem list, void(*target)(Voo)) {
    VooList_forEach(VooScheduleItem_getList(list), target);
}

void VooSchedule_forEach(VooSchedule this, Time takeOff, Time landing, void(*target)(Voo)) {
    if (takeOff != NULL) {
        if (landing != NULL) {
            _VooSchedule_forEachInternal(
                    this->data[Time_getHour(takeOff)][Time_getHour(landing)],
                    target
            );
        } else {
            uint8_t takeOffHour = Time_getHour(takeOff);
            for (int i = 0; i < HEIGHT; ++i) {
                _VooSchedule_forEachInternal(this->data[takeOffHour][i], target);
            }
        }
    } else { // takeOff == NULL
        if (landing != NULL) {
            uint8_t takeOffLanding = Time_getHour(landing);
            for (int i = 0; i < HEIGHT; ++i) {
                _VooSchedule_forEachInternal(this->data[i][takeOffLanding], target);
            }
        } else {
            ITERATE(this, _VooSchedule_forEachInternal(it, target));
        }
    }
}

struct VooSchedule_SearchResult VooSchedule_findPeakTime(VooSchedule this) {
    // TODO
    struct VooSchedule_SearchResult result;
    return result;
}

struct VooSchedule_SearchResult VooSchedule_findOffPeakTime(VooSchedule this) {
    // TODO
    struct VooSchedule_SearchResult result;
    return result;
}

struct VooSchedule_SearchResult VooSchedule_MostRecentUpdated(VooSchedule this) {
    // TODO
    struct VooSchedule_SearchResult result;
    return result;
}

struct VooSchedule_SearchResult VooSchedule_LessRecentUpdated(VooSchedule this) {
    // TODO
    struct VooSchedule_SearchResult result;
    return result;
}

void VooSchedule_delete(VooSchedule instance) {
    ITERATE(instance, VooScheduleItem_delete(it));
    free(instance);
}
