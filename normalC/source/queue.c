#include "queue.h"

int queue_init(queue_t * Q, int size);
int queue_resize(queue_t * Q, int size);
int queue_free(queue_t * Q);
int queue_empty(queue_t * Q);
int queue_enqueue(queue_t * Q, item_t item);
int queue_dequeue(queue_t * Q, item_t * item);
void queue_info(queue_t * Q);

int queue_init(queue_t * Q, int size) {
	Q->head = 0;
	Q->tail = 0;
	Q->count = 0;

	pthread_mutex_init(&Q->mutex, NULL);

	Q->array = (item_t*)calloc(size, sizeof(item_t));

	if (Q->array != NULL) {
		Q->size = size;
		return 1;
	} else {
		Q->size = 0;
		fprintf(stderr, "Queue init fail.\n");
		return 0;
	}
}

int queue_resize(queue_t * Q, int size) {
	queue_free(Q);
	return queue_init(Q, size);
}

int queue_free(queue_t * Q) {
	free(Q->array);
	Q->head = 0;
	Q->tail = 0;
	Q->count = 0;
	Q->size = 0;
	Q->array = NULL;
	return 1;
}

int queue_empty(queue_t * Q) {
	if (Q->array == NULL) {
		fprintf(stderr, "Queue is not initialized.\n");
		return 1;
	}

	if (Q->count == 0)
		return 1;
	else
		return 0;
}

int queue_enqueue(queue_t * Q, item_t item) {
	pthread_mutex_lock(&Q->mutex);

	if (Q->array == NULL) {
		fprintf(stderr, "Queue is not initialized.\n");
		pthread_mutex_unlock(&Q->mutex);
		return 0;
	}
	if (Q->count < Q->size) {
		Q->array[Q->head] = item;
		Q->head = (Q->head + 1) % Q->size;
		Q->count++;
		pthread_mutex_unlock(&Q->mutex);
		return 1;
	} else {
		fprintf(stderr, "Queue overflow.\n");
		pthread_mutex_unlock(&Q->mutex);
		return 0;
	}
}

int queue_dequeue(queue_t * Q, item_t * item) {
	pthread_mutex_lock(&Q->mutex);
	if (Q->array == NULL) {
		fprintf(stderr, "Queue is not initialized.\n");
		pthread_mutex_unlock(&Q->mutex);
		return 0;
	}
	if (!queue_empty(Q)) {
		*item = Q->array[Q->tail];
		Q->tail = (Q->tail + 1) % Q->size;
		Q->count--;
		pthread_mutex_unlock(&Q->mutex);
		return 1;
	} else {
		fprintf(stderr, "Queue underflow.\n");
		pthread_mutex_unlock(&Q->mutex);
		return 0;
	}
}

