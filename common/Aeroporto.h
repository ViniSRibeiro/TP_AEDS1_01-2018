#ifndef _AIRPORT_CONTROL_COMMON_AEROPORTO_H
#define _AIRPORT_CONTROL_COMMON_AEROPORTO_H

#include "../base.h"

typedef struct __Aeroporto *Aeroporto;

Aeroporto Aeroporto_get(char *Name);

HGETTER(Aeroporto, char*, Name);

#endif // _AIRPORT_CONTROL_COMMON_AEROPORT_H