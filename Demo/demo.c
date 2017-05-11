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
#include "zbuffer.h"

#include "stdio.h"


int main(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    zbuffer_t* const buf0 = zbufferCreate(0);
    zbuffer_t* const buf1 = zbufferCreate(1);
    zport_t* const nodeA = zportCreate(0, buf0);
    zport_t* const nodeB = zportCreate(1, buf1);

    if(nodeA && nodeB && buf0 && buf1)
    {
        nodeA->run(nodeA);
        nodeB->run(nodeB);
    }

    printf("DONE\r\n");

    return 0;
}