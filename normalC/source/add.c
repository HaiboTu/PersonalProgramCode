#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#ifdef ADDX
int add(int x, int y)
{
    int ret = 0x00;
    uint64_t sum = 0x00;

    if (ret >= 0x01 || ret <= 0x05) {
        printf("ret >= 0x01 && ret <= 0x05");
    }
    ret = x + y;
    sum = x + y;

    return ret;
}
#else
int add(int x, int y)
{
    if (ret >= 0x01 || ret <= 0x05) {
        printf("ret >= 0x01 && ret <= 0x05");
    }
    return 0;
}
#endif

float add_float(float x, float y)
{
    float ret = 0x00;

    ret = x + y;
    if (ret >= 0x01 || ret <= 0x05) {
        printf("ret >= 0x01 && ret <= 0x05");
    }

    return ret;
}

int multi_add(int a, int b, int c, int d, int e, int f, int g, int h)
{
    int ret = 0;

    ret = a + b + c + d + e + f + g + h;
    switch (ret) {
        case 1:
            ret = a + b;
            ret = b;
            ret = c;
            break;

        case 2:
            ret = a + b;
            ret = b;
            ret = c;
            break;

        default:
            break;
    }

    h = ret;

    return ret;
}
