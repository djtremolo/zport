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

#include "zchannel.h"


#if ZCHANNEL_DEBUG
#include "stdio.h"
#define DBGPRINT(args...) printf(args)
#else
#define DBGPRINT()
#endif

typedef enum
{
    ZCHANNEL_MSG_STATE_FREE = 0,
    ZCHANNEL_MSG_STATE_READY_TO_BE_SENT,
    ZCHANNEL_MSG_STATE_RESERVED   
} zchannelMessageState_t;


typedef struct
{
    zchannelMessageState_t state;
    uint8_t buf[ZCHANNEL_MSG_MAX];
    uint16_t length;
} zchannelMessage_t;

typedef struct
{
    zchannel_t publicAPI;   /*placeholder for public interface*/

    /*private members*/
    uint16_t myIndex;
    zchannelMessage_t myMessage;
} zchannelPrivate_t;


/*method implementations*/
static int myRun(zchannel_t* const inst);
static zchannelMessageHandle_t const myGetOutgoingMessage(zchannel_t* const inst, uint8_t** bufPtr, uint16_t *bytes);
static void myReleaseMessage(zchannel_t* const inst, zchannelMessageHandle_t const handle);

/*public interface definition*/
static const zchannel_t publicAPI = {.run=&myRun, .getOutgoingMessage=&myGetOutgoingMessage, .releaseMessage=&myReleaseMessage};

/*instance list (allocated staticly to avoid dynamic allocation)*/
static zchannelPrivate_t instances[ZCHANNEL_INSTANCES_COUNT];

zchannel_t* const zchannelCreate(uint16_t index)
{
    zchannel_t *inst = NULL;

    if(index < ZCHANNEL_INSTANCES_COUNT)
    {
        zchannelPrivate_t *prvInst = &(instances[index]);

        memcpy(&(prvInst->publicAPI), (void*)&publicAPI, sizeof(zchannel_t));

        prvInst->myIndex = index;   

        inst = &(prvInst->publicAPI);
    }

    return inst;
}

static int myRun(zchannel_t* const inst)
{
    zchannelPrivate_t* const prvInst = (zchannelPrivate_t* const)inst;

    DBGPRINT("zchannel[%d]: myRun called\r\n", prvInst->myIndex);

    return 0;
}

static zchannelMessageHandle_t const myGetOutgoingMessage(zchannel_t* const inst, uint8_t** bufPtr, uint16_t *bytes)
{
    zchannelMessageHandle_t hnd = NULL;
    zchannelPrivate_t* const prvInst = (zchannelPrivate_t* const)inst;

    DBGPRINT("zchannel[%d]: myGetOutgoingMessage called\r\n", prvInst->myIndex);

    if(prvInst)
    {
        zchannelMessage_t *m = &(prvInst->myMessage);

        if(m->state == ZCHANNEL_MSG_STATE_READY_TO_BE_SENT)
        {
            m->state = ZCHANNEL_MSG_STATE_RESERVED;
            *bytes = m->length;
            *bufPtr = m->buf;

            hnd = (zchannelMessageHandle_t)m;
        }
    }

    return hnd;
}

static void myReleaseMessage(zchannel_t* const inst, zchannelMessageHandle_t const handle)
{
    zchannelPrivate_t* const prvInst = (zchannelPrivate_t* const)inst;

    DBGPRINT("zchannel[%d]: myReleaseMessage called\r\n", prvInst->myIndex);
   
    if(prvInst)
    {
        zchannelMessage_t *m = (zchannelMessage_t*)handle;

        if(m)
        {
            m->state = ZCHANNEL_MSG_STATE_FREE;
        }
    }

    return;
}


static int mySetOutgoingMessage(zchannel_t* const inst, uint8_t const *buf, uint16_t len)
{
    int ret = -1;
    zchannelPrivate_t* const prvInst = (zchannelPrivate_t* const)inst;

    DBGPRINT("zchannel[%d]: mySetOutgoingMessage called\r\n", prvInst->myIndex);

    if(prvInst)
    {
        zchannelMessage_t *m = &(prvInst->myMessage);

        if(m->state == ZCHANNEL_MSG_STATE_FREE)
        {
            /*TODO*/
            m->state = ZCHANNEL_MSG_STATE_READY_TO_BE_SENT;
            ret = 0;
        }
    }

    return ret;
}
