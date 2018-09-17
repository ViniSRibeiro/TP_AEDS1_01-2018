#ifndef _AIRPORT_CONTROL_COMMON_VOOLIST_H
#define _AIRPORT_CONTROL_COMMON_VOOLIST_H

#include "../base.h"
#include "Voo.h"

typedef struct __VooList *VooList;

VooList VooList_new();

void VooList_insert(VooList, Voo);

Voo VooList_remove(VooList, VID);

Voo VooList_find(VooList, VID);

uint32_t VooList_size(VooList);

void VooList_print(VooList);

void VooList_delete(VooList instance);

#endif // _AIRPORT_CONTROL_COMMON_VOOLIST_H
