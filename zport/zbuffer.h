#ifndef __ZBUFFER_H__
#define __ZBUFFER_H__

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

typedef void* zbufferMessageHandle_t;

typedef struct zbuffer_t zbuffer_t;

extern zbuffer_t* const zbufferCreate(uint16_t index);

typedef struct zbuffer_t
{
    int (* const run)(const zbuffer_t* const inst);
    const zbufferMessageHandle_t (* const getOutgoingMessage)(const zbuffer_t* const inst, uint8_t** bufPtr, uint16_t *bytes);
    void (* const releaseMessage)(const zbuffer_t* const inst, zbufferMessageHandle_t const handle);

} zbuffer_t;



#endif