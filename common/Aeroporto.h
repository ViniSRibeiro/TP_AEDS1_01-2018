#ifndef _AIRPORT_CONTROL_COMMON_AEROPORTO_H
#define _AIRPORT_CONTROL_COMMON_AEROPORTO_H

#include "../base.h"

typedef struct __Aeroporto *Aeroporto;

Aeroporto Aeroporto_new();

void Aeroporto_delete(Aeroporto instance);

#endif // _AIRPORT_CONTROL_COMMON_AEROPORT_H