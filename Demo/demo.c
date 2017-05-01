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
#include "zchannel.h"

#include "stdio.h"


int main(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    zchannel_t* const ch0 = zchannelCreate(0);
    zchannel_t* const ch1 = zchannelCreate(1);
    zport_t* const nodeA = zportCreate(0, ch0);
    zport_t* const nodeB = zportCreate(1, ch1);

    if(nodeA && nodeB && ch0 && ch1)
    {
        nodeA->run(nodeA);
        nodeB->run(nodeB);

        ch0->run(ch0);
        ch1->run(ch1);
    }

    printf("DONE\r\n");

    return 0;
}