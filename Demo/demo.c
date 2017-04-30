#include "zport.h"

#include "stdio.h"


void main()
{
    int x,y, ans;

    x= 10;
    y = 22;

    ans = zportadd(x,y);

    printf("%d + %d = %d\r\n", x,y, ans);


}