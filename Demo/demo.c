#include "zport.h"

#include "stdio.h"


int main(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    zport_t *nodeA = zportCreate(0);
    zport_t *nodeB = zportCreate(1);

    if(nodeA && nodeB)
    {
        nodeA->run(nodeA);
        nodeB->run(nodeB);
    }

    printf("DONE\r\n");

    return 0;
}