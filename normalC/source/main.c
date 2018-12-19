#include "add.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int ret = 0x00, x = 0x01, y = 0x07;

    ret = add(x, y);

    printf("The sum of %d and %d is %d.\n", x, y, ret);

    return ret;
}
