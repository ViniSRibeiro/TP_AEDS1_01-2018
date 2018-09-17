#ifndef _AIRPORT_CONTROL_COMMON_VOOLIST_H
#define _AIRPORT_CONTROL_COMMON_VOOLIST_H

#include "../base.h"

typedef struct __VooList *VooList;

VooList VooList_new();

void VooList_delete(VooList instance);

#endif // _AIRPORT_CONTROL_COMMON_VOOLIST_H
