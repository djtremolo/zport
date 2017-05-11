#ifndef __ZPORT_H__
#define __ZPORT_H__

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
#include "zbuffer.h"


typedef struct zport_t zport_t;
typedef void* zportZeroCopyHandle_t;


extern zport_t* const zportCreate(uint16_t index, zbuffer_t* const zbuf);

typedef struct zport_t
{
    int (* const run)(zport_t* const inst);
    const zportZeroCopyHandle_t (* const zcReserve)(zport_t* const inst, uint8_t** bufPtr, uint16_t* const lenPtr);
    int (* const zcSend)(zport_t* const inst, zportZeroCopyHandle_t const hnd);
    const zportZeroCopyHandle_t (* const zcReceive)(zport_t* const inst, uint8_t** bufPtr, uint16_t* const lenPtr);
    int (* const zcRelease)(zport_t* const inst, zportZeroCopyHandle_t const hnd);
    int (* const send)(zport_t* const inst, uint8_t* const buf, uint16_t len);
    int (* const receive)(zport_t* const inst, uint8_t** const bufPtr, uint16_t *lenPtr);
    
} zport_t;



#endif