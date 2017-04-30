#include "stddef.h"
#include "zport.h"

#if ZPORT_DEBUG
#include "stdio.h"
#define DBGPRINT(args...) printf(args)
#else
#define DBGPRINT()
#endif



typedef struct
{
    zport_t publicAPI;   /*placeholder for public interface*/

    /*private members*/
    uint16_t myIndex;
    uint16_t state;
} zportPrivate_t;


static zportPrivate_t instances[ZPORT_INSTANCES_COUNT];


static int myRun(zport_t *inst);


zport_t* zportCreate(uint16_t index)
{
    zport_t *inst = NULL;

    if(index < ZPORT_INSTANCES_COUNT)
    {
        zportPrivate_t *prvInst = &(instances[index]);

        prvInst->publicAPI.run = &myRun;

        prvInst->myIndex = index;   

        inst = &(prvInst->publicAPI);
    }

    return inst;
}

int myRun(zport_t *inst)
{
    zportPrivate_t *prvInst = (zportPrivate_t*)inst;
    
    DBGPRINT("zport[%d]: myRun called\r\n", prvInst->myIndex);

    return 0;
}

