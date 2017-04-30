/*
MIT License

Copyright (c) [2017] [Sami Saastamoinen]

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

