#ifndef __ZCHANNEL_H__
#define __ZCHANNEL_H__

#include "ztarget.h"

typedef struct zchannel_t zchannel_t;
typedef struct zchannel_t
{
    int (*run)(zchannel_t *inst);
} zchannel_t;

extern zchannel_t* zchannelCreate(uint16_t index);


#endif