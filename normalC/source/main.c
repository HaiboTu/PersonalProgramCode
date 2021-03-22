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

#define CONSUMER_COUNT	(0x40)
#define PRODUCER_COUNT	(0x40)
#define MAX_PUSH_NODE	(0x100)
#define CONSUM_MARK		(0x01)

lf_stack *lf_head;
pthread_t producer_threads[PRODUCER_COUNT];
pthread_t consumer_threads[CONSUMER_COUNT];

void sighand(int signo) {
	int i = 0;
	lf_node *node = NULL;

	for (i = 0; i < MAX_PUSH_NODE; i++) {
		node = (lf_node *)malloc(sizeof(lf_node));
		node->cmark = 0;

		push(lf_head, node);

		printf("sighand: push node %p in stack\n", node);
	}

	return;
}

void *producer_thread(void *arg) {
	while (1) {
		sleep(1);
	}
}

void notify_producer() {
	int i = 0;

	for (i = 0; i < PRODUCER_COUNT; i++) {
		pthread_kill(producer_threads[i], SIGALRM);
	}
}

void *consumer_thread(void *arg) {
	lf_node *node = NULL;

	while (1) {
		node = pop(lf_head);
		if (node == NULL) {
			notify_producer();
			sleep(1);
		} else {
			if (node->cmark == CONSUM_MARK) {
				printf("find consumed node %p\n", node);
				exit(-1);
			}

	//		printf("consume node %p\n", node);
			node->cmark = CONSUM_MARK;
			free(node);
		}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	int ret = 0, i = 0;
    struct sigaction actions;

	memset(&actions, 0, sizeof(actions));
	sigemptyset(&actions.sa_mask);
	actions.sa_flags = 0;
	actions.sa_handler = sighand;
	sigaction(SIGALRM, &actions, NULL);

	lf_head = (lf_stack *)malloc(sizeof(lf_stack));
	memset(lf_head, 0x00, sizeof(lf_stack));

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

    return 0;
}

