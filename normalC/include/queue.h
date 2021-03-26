#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

#include "cas.h"

typedef uint64_t item_t;

typedef struct queue {
	int head;
	int tail;
	int count;
	int size;
	pthread_mutex_t mutex;
	item_t* array;
} queue_t;

int queue_init(queue_t * Q, int size);
int queue_resize(queue_t * Q, int size);
int queue_free(queue_t * Q);
int queue_empty(queue_t * Q);
int queue_enqueue(queue_t * Q, item_t item);
int queue_dequeue(queue_t * Q, item_t * item);

#endif
