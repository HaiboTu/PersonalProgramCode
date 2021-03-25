#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "cas.h"

static inline uint64_t checkMark(lf_node* node) {
	if (node->cmark) {
		printf("checkMark failed!\n");
		exit(-1);
	}
}

static inline uint64_t lf_stack_pack(lf_node* node, uint64_t cnt) {
	return (uint64_t)(node) << CNT_BITS | (uint64_t)(cnt & (CNT_MASK));
}

static inline lf_node *lf_stack_unpack(uint64_t val) {
	return (lf_node *)(val >> CNT_BITS);
}

inline int cas64(uint64_t *val, uint64_t oldv, uint64_t newv) {
	int ret = 0;

	asm volatile (
		"lock \n\t"
		"cmpxchg %%rcx, (%%rbx) \n\t"
		"sete (%%rdx) \n\t"
		::"a"(oldv), "b"(val), "c"(newv), "d"(&ret) : "memory", "cc");

	return ret;
}

int push(lf_stack *head, lf_node *node) {
	lf_stack new;
	uint64_t old;

	new = lf_stack_pack(node, node->push_cnt);
	for(;;) {
		old = *(uint64_t *)(head);
		node->next = old;

		if (cas64((uint64_t *)(head), old, new)) {
			break;
		}
	}

	return 0;
}

lf_node *pop(lf_stack *head) {
	uint64_t next, old;
	lf_node *node;

	for(;;) {
		old = *(uint64_t *)(head);
		if (old == 0) {
			return NULL;
		}

		node = lf_stack_unpack(old);
		next = node->next;

		if (cas64((uint64_t *)(head), old, next)) {
			return node;
		}
	}
}

