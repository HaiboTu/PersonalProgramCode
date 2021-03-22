#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "cas.h"

static inline uint64_t lf_stack_pack(lf_node* node) {
	return (uint64_t)(node) << CNT_BITS;
}

static inline lf_node *lf_stack_unpack(uint64_t val) {
	return (lf_node *)(val >> CNT_BITS);
}

int cas64(uint64_t *val, uint64_t oldv, uint64_t newv) {
	int ret = 0;

	asm volatile (
		"lock \n\t"
		"cmpxchg %%rcx, (%%rbx) \n\t"
		"sete %%dl \n\t"
		:"+d"(ret):"a"(oldv), "b"(val), "c"(newv) : "memory", "cc");

	return ret;
}

int push(lf_stack *head, lf_node *node) {
	lf_stack new;
	uint64_t old;

	new = lf_stack_pack(node);
	for(;;) {
		old = *(uint64_t *)(head);
		node->next = old;
#if 0
		printf("push node %p in stack\n", new);
		*head = new;
		break;
#else
		if (cas64((uint64_t *)(head), old, new)) {
			break;
		}
#endif
	}

	return 0;
}

lf_node *pop(lf_stack *head) {
	lf_stack *old, *next;
	lf_node *node;

	for(;;) {
		old = *(uint64_t *)(head);
		if (old == 0) {
			return NULL;
		}

		node = lf_stack_unpack(old);
		next = node->next;

#if 0
		printf("pop node %p in stack\n", node);
		*head = next;
		break;
#else
		if (cas64((uint64_t *)(head), old, next)) {
			return node;
		}
#endif
	}
}

int empty(lf_stack *head) {
	return head == NULL;
}
