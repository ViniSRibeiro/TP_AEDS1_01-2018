#include "VooScheduleItem.h"

struct __VooScheduleItem {
    VooList List;
    Time LastUpdate;
};

VooScheduleItem VooScheduleItem_new() {
    VooScheduleItem instance = malloc(sizeof(struct __VooScheduleItem));
    instance->List = VooList_new();
    instance->LastUpdate = Time_now();
    return instance;
}

GETTER(VooScheduleItem, VooList, List);

GETTER(VooScheduleItem, Time, LastUpdate);

uint32_t VooScheduleItem_num(VooScheduleItem this) {
    return VooList_size(this->List);
}

void VooScheduleItem_updateTime(VooScheduleItem this) {
    Time_updateToNow(this->LastUpdate);
}

void VooScheduleItem_delete(VooScheduleItem instance) {
    VooList_delete(instance->List);
    Time_delete(instance->LastUpdate);
    free(instance);
}

