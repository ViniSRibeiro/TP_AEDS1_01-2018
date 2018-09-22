#include "VooSchedule.h"

#define ITERATE(a, b) \
for (uint8_t x = 0; x < WIDTH; ++x) \
    for (uint8_t y = 0; y < HEIGHT; ++y) {\
        VooScheduleItem it = (a)->data[x][y];\
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
    VooScheduleItem item = this->data
    [Time_getHour(FlightData_getSchedule(Voo_getTakeoff(voo)))]
    [Time_getHour(FlightData_getSchedule(Voo_getLanding(voo)))];

    VooScheduleItem_updateTime(item);
    VooList_insert(VooScheduleItem_getList(item), voo);
}

Voo VooSchedule_remove(VooSchedule this, VID vid) {
    ITERATE(this,
            VooList item = VooScheduleItem_getList(it);
                    Voo v;
                    if ((v = VooList_remove(item, vid)) != NULL) {
                        return v;
                    }
    );
    return NULL;
}

Voo VooSchedule_find(VooSchedule this, VID vid) {
    ITERATE(this,
            VooList item = VooScheduleItem_getList(it);
                    Voo v;
                    if ((v = VooList_remove(item, vid)) != NULL) {
                        return v;
                    }
    );
    return NULL;
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

static struct VooSchedule_SearchResult find(VooSchedule this, bool(*comparator)(VooScheduleItem, VooScheduleItem)) {
    struct VooSchedule_SearchResult result;
    result.list = this->data[0][0];
    ITERATE(this,
            if (comparator(result.list, it)) {
                result.list = it;
                result.takeOff = x;
                result.landing = y;
            }
    );
    return result;
}

static bool peak(VooScheduleItem c1, VooScheduleItem c2) {
    return VooList_size(VooScheduleItem_getList(c1)) < VooList_size(VooScheduleItem_getList(c2));
}

struct VooSchedule_SearchResult VooSchedule_findPeakTime(VooSchedule this) {
    return find(this, peak);
}

static bool offPeak(VooScheduleItem c1, VooScheduleItem c2) {
    return VooList_size(VooScheduleItem_getList(c1)) > VooList_size(VooScheduleItem_getList(c2));
}

struct VooSchedule_SearchResult VooSchedule_findOffPeakTime(VooSchedule this) {
    return find(this, offPeak);
}

static bool recentUpdated(VooScheduleItem c1, VooScheduleItem c2) {
    return Time_compareTo(VooScheduleItem_getLastUpdate(c1), VooScheduleItem_getLastUpdate(c2)) > 0;
}

struct VooSchedule_SearchResult VooSchedule_findMostRecentUpdated(VooSchedule this) {
    return find(this, recentUpdated);
}

static bool notRecentUpdated(VooScheduleItem c1, VooScheduleItem c2) {
    return Time_compareTo(VooScheduleItem_getLastUpdate(c1), VooScheduleItem_getLastUpdate(c2)) < 0;
}

struct VooSchedule_SearchResult VooSchedule_findLessRecentUpdated(VooSchedule this) {
    return find(this, notRecentUpdated);
}

bool VooSchedule_isSparse(VooSchedule this) {
    const unsigned int total = WIDTH * HEIGHT / 2;
    int any = 0;
    ITERATE(this,
            if (VooScheduleItem_num(it) > 0) {
                any++;
            }
    );
    return any > total;
}

void VooSchedule_delete(VooSchedule instance) {
    ITERATE(instance, VooScheduleItem_delete(it));
    free(instance);
}
