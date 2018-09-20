#ifndef _VOO_CONST_H
#define _VOO_CONST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "FIFTH/src/base.h"

//region Constants

#ifndef __GNUC__
#define __attribute__(x)
#endif

//endregion

//region Utility
#define __AIRPORT_CONCAT(x, y, z) x ## _ ## y ## z

#define HGETTER(name, type, field) \
type __AIRPORT_CONCAT(name, get, field)(name ins);

#define GETTER(name, type, field) \
type __AIRPORT_CONCAT(name, get, field)(name ins) {\
    return ins->field;\
}

#define HSETTER(name, type, field) \
HGETTER(name, type, field)\
void __AIRPORT_CONCAT(name, set, field)(name ins, type v);

#define SETTER(name, type, field) \
GETTER(name, type, field)\
void __AIRPORT_CONCAT(name, set, field)(name ins, type v) {\
    ins->field = v;\
}

//endregion

#endif //_VOO_CONST_H
