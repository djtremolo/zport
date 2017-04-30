#include "stddef.h"
#include "zchannel.h"


#if ZCHANNEL_DEBUG
#include "stdio.h"
#define DBGPRINT(args...) printf(args)
#else
#define DBGPRINT()
#endif



typedef struct
{
    zchannel_t publicAPI;   /*placeholder for public interface*/

    /*private members*/
    uint16_t myIndex;
} zchannelPrivate_t;


static zchannelPrivate_t instances[ZCHANNEL_INSTANCES_COUNT];


static int myRun(zchannel_t *inst);


zchannel_t* zchannelCreate(uint16_t index)
{
    zchannel_t *inst = NULL;

    if(index < ZCHANNEL_INSTANCES_COUNT)
    {
        zchannelPrivate_t *prvInst = &(instances[index]);

        prvInst->publicAPI.run = &myRun;

        prvInst->myIndex = index;   

        inst = &(prvInst->publicAPI);
    }

    return inst;
}

int myRun(zchannel_t *inst)
{
    zchannelPrivate_t *prvInst = (zchannelPrivate_t*)inst;
    
    DBGPRINT("zchannel[%d]: myRun called\r\n", prvInst->myIndex);

    return 0;
}

