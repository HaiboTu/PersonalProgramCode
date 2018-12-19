#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef ADDX
int add(int x, int y)
{
    int ret = 0x00;
    
    ret = x + y;

    return ret;
}
#else
int add(int x, int y)
{
    return 0;
}
#endif
