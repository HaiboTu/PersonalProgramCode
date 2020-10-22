#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

void* thread1Func(void* param) {
    while (1) {

    }

    return NULL;
}

int main() {

	asm volatile (".byte 0x66; clflush (%rax)\n\t");

    return 0;
}

