#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

#include "cas.h"

#define CONSUMER_COUNT	(0x08)
#define PRODUCER_COUNT	(0x08)
#define MAX_PUSH_NODE	(0x100)
#define CONSUM_MARK		(0x01)

lf_stack lf_head;
pthread_t producer_threads[PRODUCER_COUNT];
pthread_t consumer_threads[CONSUMER_COUNT];
sem_t *g_sem_empty_ptr = NULL; // semaphore for consumer
sem_t *g_sem_full_ptr = NULL; // semaphore for producer

void *producer_thread(void *arg) {
	int i = 0;
	lf_node *node = NULL;
	while (1) {
		sem_wait(g_sem_empty_ptr);
		for (i = 0; i < MAX_PUSH_NODE; i++) {
			node = (lf_node *)malloc(sizeof(lf_node));
			node->cmark = 0;
			node->next = 0;
			node->magic = 0x4a;

			push(&lf_head, node);
		}
		sem_post(g_sem_full_ptr);
	}
}

void *consumer_thread(void *arg) {
	lf_node *node = NULL;
	pthread_t tid;

	while (1) {
		node = pop(&lf_head);
		if (node == NULL) {
			sem_post(g_sem_empty_ptr);
			sem_wait(g_sem_full_ptr);
		} else {
			if (node->cmark == CONSUM_MARK) {
				printf("find consumed node %p\n", node);
				exit(-1);
			}

			tid = pthread_self();
			node->cmark = CONSUM_MARK;
			node->magic = 0x00;
			free(node);
		}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	int ret = 0, i = 0;

	memset(&lf_head, 0x00, sizeof(lf_stack));
	printf("lf_headp %p\n", &lf_head);

	g_sem_full_ptr = (sem_t*)malloc(sizeof(sem_t));
	g_sem_empty_ptr = (sem_t*)malloc(sizeof(sem_t));

	sem_init(g_sem_full_ptr, 0, 0); //set semaphore full initially to the buffer length
	sem_init(g_sem_empty_ptr, 0, 0); //set semaphore full initially to 0

	for (i = 0; i < PRODUCER_COUNT; i++) {
		pthread_create(&producer_threads[i], NULL, producer_thread, NULL);
	}

	for (i = 0; i < CONSUMER_COUNT; i++) {
		pthread_create(&consumer_threads[i], NULL, consumer_thread, NULL);
	}

	for (i = 0; i < PRODUCER_COUNT; i++) {
		pthread_join(producer_threads[i], NULL);
	}

	for (i = 0; i < CONSUMER_COUNT; i++) {
		pthread_join(consumer_threads[i], NULL);
	}


	sem_destroy(g_sem_full_ptr);
	sem_destroy(g_sem_empty_ptr);

	free(g_sem_full_ptr);
	free(g_sem_empty_ptr);

    return 0;
}

