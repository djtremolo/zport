#include "zport.h"
#include "zchannel.h"

#include "stdio.h"


int main(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    zchannel_t *ch = zchannelCreate(0);
    zport_t *nodeA = zportCreate(0);
    zport_t *nodeB = zportCreate(1);

    if(nodeA && nodeB && ch)
    {
        nodeA->run(nodeA);
        nodeB->run(nodeB);

        ch->run(ch);
    }

    printf("DONE\r\n");

    return 0;
}