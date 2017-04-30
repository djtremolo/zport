#ifndef __ZPORT_H__
#define __ZPORT_H__

#include "stdint.h"
#include "stdbool.h"

#include "ztarget.h"

typedef struct zport_t zport_t;
typedef struct zport_t
{
    int (*run)(zport_t *inst);
} zport_t;

extern zport_t* zportCreate(uint16_t index);


#endif