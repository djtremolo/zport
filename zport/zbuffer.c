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

#include "zbuffer.h"


#if ZBUFFER_DEBUG
#include "stdio.h"
#define DBGPRINT(args...) printf(args)
#else
#define DBGPRINT()
#endif

typedef enum
{
    ZBUFFER_MSG_STATE_FREE = 0,
    ZBUFFER_MSG_STATE_READY_TO_BE_SENT,
    ZBUFFER_MSG_STATE_RESERVED   
} zbufferMessageState_t;


typedef struct
{
    zbufferMessageState_t state;
    uint8_t buf[ZBUFFER_MSG_MAX];
    uint16_t length;
} zbufferMessage_t;

typedef struct
{
    zbuffer_t publicAPI;   /*placeholder for public interface*/

    /*private members*/
    uint16_t myIndex;
    zbufferMessage_t myMessage;
} zbufferPrivate_t;


/*method implementations*/
static int myRun(zbuffer_t* const inst);
static zbufferMessageHandle_t const myGetOutgoingMessage(zbuffer_t* const inst, uint8_t** bufPtr, uint16_t *bytes);
static void myReleaseMessage(zbuffer_t* const inst, zbufferMessageHandle_t const handle);

/*public interface definition*/
static const zbuffer_t publicAPI = {.run=&myRun, .getOutgoingMessage=&myGetOutgoingMessage, .releaseMessage=&myReleaseMessage};

/*instance list (allocated staticly to avoid dynamic allocation)*/
static zbufferPrivate_t instances[ZBUFFER_INSTANCES_COUNT];

zbuffer_t* const zbufferCreate(uint16_t index)
{
    zbuffer_t *inst = NULL;

    if(index < ZBUFFER_INSTANCES_COUNT)
    {
        zbufferPrivate_t *prvInst = &(instances[index]);

        memcpy(&(prvInst->publicAPI), (void*)&publicAPI, sizeof(zbuffer_t));

        prvInst->myIndex = index;   

        inst = &(prvInst->publicAPI);
    }

    return inst;
}

static int myRun(zbuffer_t* const inst)
{
    zbufferPrivate_t* const prvInst = (zbufferPrivate_t* const)inst;

    DBGPRINT("zbuffer[%d]: myRun called\r\n", prvInst->myIndex);

    return 0;
}

static zbufferMessageHandle_t const myGetOutgoingMessage(zbuffer_t* const inst, uint8_t** bufPtr, uint16_t *bytes)
{
    zbufferMessageHandle_t hnd = NULL;
    zbufferPrivate_t* const prvInst = (zbufferPrivate_t* const)inst;

    DBGPRINT("zbuffer[%d]: myGetOutgoingMessage called\r\n", prvInst->myIndex);

    if(prvInst)
    {
        zbufferMessage_t *m = &(prvInst->myMessage);

        if(m->state == ZBUFFER_MSG_STATE_READY_TO_BE_SENT)
        {
            m->state = ZBUFFER_MSG_STATE_RESERVED;
            *bytes = m->length;
            *bufPtr = m->buf;

            hnd = (zbufferMessageHandle_t)m;
        }
    }

    return hnd;
}

static void myReleaseMessage(zbuffer_t* const inst, zbufferMessageHandle_t const handle)
{
    zbufferPrivate_t* const prvInst = (zbufferPrivate_t* const)inst;

    DBGPRINT("zbuffer[%d]: myReleaseMessage called\r\n", prvInst->myIndex);
   
    if(prvInst)
    {
        zbufferMessage_t *m = (zbufferMessage_t*)handle;

        if(m)
        {
            m->state = ZBUFFER_MSG_STATE_FREE;
        }
    }

    return;
}


static int mySetOutgoingMessage(zbuffer_t* const inst, uint8_t const *buf, uint16_t len)
{
    int ret = -1;
    zbufferPrivate_t* const prvInst = (zbufferPrivate_t* const)inst;

    DBGPRINT("zbuffer[%d]: mySetOutgoingMessage called\r\n", prvInst->myIndex);

    if(prvInst)
    {
        zbufferMessage_t *m = &(prvInst->myMessage);

        if(m->state == ZBUFFER_MSG_STATE_FREE)
        {
            /*TODO*/
            m->state = ZBUFFER_MSG_STATE_READY_TO_BE_SENT;
            ret = 0;
        }
    }

    return ret;
}
