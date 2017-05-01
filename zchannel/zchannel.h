#ifndef __ZCHANNEL_H__
#define __ZCHANNEL_H__

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

#include "ztarget.h"

typedef void* zchannelMessageHandle_t;

typedef struct zchannel_t zchannel_t;

extern zchannel_t* const zchannelCreate(uint16_t index);

typedef struct zchannel_t
{
    int (* const run)(zchannel_t *inst);
    const zchannelMessageHandle_t (* const getOutgoingMessage)(zchannel_t* const inst, uint8_t** bufPtr, uint16_t *bytes);
    void (* const releaseMessage)(zchannel_t* const inst, zchannelMessageHandle_t const handle);

} zchannel_t;



#endif