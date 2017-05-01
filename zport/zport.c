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
    zchannel_t *myChannel;
} zportPrivate_t;


static int myRun(zport_t* const inst);

static const zport_t publicAPI = {.run=&myRun};
static zportPrivate_t instances[ZPORT_INSTANCES_COUNT];


zport_t* const zportCreate(uint16_t index, zchannel_t* const zch)
{
    zport_t *inst = NULL;

    if(index < ZPORT_INSTANCES_COUNT)
    {
        if(zch)
        {
            zportPrivate_t *prvInst = &(instances[index]);

            memcpy(&(prvInst->publicAPI), (void*)&publicAPI, sizeof(zport_t));

            prvInst->myIndex = index;  
            prvInst->myChannel = zch; 

            inst = &(prvInst->publicAPI);
        }
    }

    return inst;
}

int myRun(zport_t* const inst)
{
    zportPrivate_t *prvInst = (zportPrivate_t*)inst;
    
    DBGPRINT("zport[%d]: myRun called\r\n", prvInst->myIndex);

    return 0;
}

