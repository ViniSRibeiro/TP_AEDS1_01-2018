#ifndef _VOO_CONST_H
#define _VOO_CONST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define __MACRO_FUNCTION_BODY(x) do { x } while(0)

#define _OUT_ // Use this to mark parameter as output

//region Constants

#ifndef NULL
#define NULL ((void*)0)
#endif
#define bool int8_t
#define true ((int8_t )1)
#define false ((int8_t )0)

//endregion

//region Logger

#define FPRINT(x, y, ...) fprintf(x, y, ##__VA_ARGS__)

#define PRINT(x, ...) FPRINT(stdout, x, ##__VA_ARGS__)
#define PRINTLN(x, ...) __MACRO_FUNCTION_BODY( PRINT(x, ___VA_ARGS___); PRINT("\n"); )

#define ERROR(x, ...) FPRINT(stderr, x, ##__VA_ARGS__)
#define ERRORLN(x, ...) __MACRO_FUNCTION_BODY( ERROR(x, ##__VA_ARGS__); ERROR("\n"); )

#define FATAL(x, ...) __MACRO_FUNCTION_BODY( fflush(stdout); ERRORLN(x, ##__VA_ARGS__); ERRORLN("<%s> %s", __FILE__, __func__); exit(1); )

//region Debug

#ifdef _AIRPORT_CONTROL_DEBUG
#define DEBUG(x, ...) FPRINT(stdout, x, ##__VA_ARGS__)
#define DEBUGLN(x, ...) __MACRO_FUNCTION_BODY( DEBUG(x, __VA_ARGS__); PRINT("\n"); )
#else
#define DEBUG(...) (void)0
#define DEBUGLN(...) (void)0
#endif

//endregion

//endregion


//region Utility
#define __CONCAT(x, y, z) x ## _ ## y ## z

#define HGETTER(name, type, field) \
type __CONCAT(name, get, field)(name ins);

#define GETTER(name, type, field) \
type __CONCAT(name, get, field)(name ins) {\
    return ins->field;\
}

#define HSETTER(name, type, field) \
HGETTER(name, type, field)\
void __CONCAT(name, set, field)(name ins, type v);

#define SETTER(name, type, field) \
GETTER(name, type, field)\
void __CONCAT(name, set, field)(name ins, type v) {\
    ins->field = v;\
}

#define ASSERT(x, y, ...) __MACRO_FUNCTION_BODY( if (!(x)) FATAL(y, ##__VA_ARGS__); )
#define CHECK_NOT_NULL(x, y, ...) ASSERT((x) != NULL, y, ##__VA_ARGS__)

#define UPPER(x) ((char)('a' <= (x) && (x) <= 'z' ? (x) + 'A' - 'a' : (x)))

/**
 * Converts any expression in true/false value
 */
#define BOOL(x) (x) ? true : false

//endregion

#endif //_VOO_CONST_H
