/*
MIT License

Copyright (c) 2017 Sami Saastamoinen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
    zbuffer_t *myBuffer;
} zportPrivate_t;

/*method prototypes*/
static int myRun(zport_t* const inst);
static zportZeroCopyHandle_t myZcReserve(zport_t* const inst);
static int myZcSend(zport_t* const inst, zportZeroCopyHandle_t const hnd);
static zportZeroCopyHandle_t myZcReceive(zport_t* const inst);
static int myZcRelease(zport_t* const inst, zportZeroCopyHandle_t const hnd);
static int mySend(zport_t* const inst, uint8_t* const buf, uint16_t len);
static int myReceive(zport_t* const inst, uint8_t** const bufPtr, uint16_t *lenPtr);

/*definition of the user API*/
static const zport_t publicAPI = {.run=&myRun, .zcReserve=&myZcReserve, .zcSend=&myZcSend, .zcReserve=&myZcReceive, .zcRelease=&myZcRelease, .send=&mySend, .receive=&myReceive};

/*storage area for the zport instances*/
static zportPrivate_t instances[ZPORT_INSTANCES_COUNT];


zport_t* const zportCreate(uint16_t index, zbuffer_t* const zch)
{
    zport_t *inst = NULL;

    if(index < ZPORT_INSTANCES_COUNT)
    {
        if(zch)
        {
            zportPrivate_t *prvInst = &(instances[index]);

            memcpy(&(prvInst->publicAPI), (void*)&publicAPI, sizeof(zport_t));

            prvInst->myIndex = index;  
            prvInst->myBuffer = zch; 

            inst = &(prvInst->publicAPI);
        }
    }

    return inst;
}

static int myRun(zport_t* const inst)
{
    zportPrivate_t* const prvInst = (zportPrivate_t*)inst;
    const zbuffer_t* const buf = prvInst->myBuffer;
    
    DBGPRINT("zport[%d]: myRun called\r\n", prvInst->myIndex);

    prvInst->myBuffer = NULL;

    buf->run(buf);

    return 0;
}

static zportZeroCopyHandle_t myZcReserve(zport_t* const inst)
{
    zportZeroCopyHandle_t hnd = NULL;

    return hnd;
}

static int myZcSend(zport_t* const inst, zportZeroCopyHandle_t const hnd)
{
    int ret = -1;

    return ret;
}

static zportZeroCopyHandle_t myZcReceive(zport_t* const inst)
{
    zportZeroCopyHandle_t hnd = NULL;

    return hnd;
}

static int myZcRelease(zport_t* const inst, zportZeroCopyHandle_t const hnd)
{

}

static int mySend(zport_t* const inst, uint8_t* const buf, uint16_t len)
{
    int ret = -1;

    return ret;
}

static int myReceive(zport_t* const inst, uint8_t** const bufPtr, uint16_t *lenPtr)
{
    int ret = -1;

    return ret;
}