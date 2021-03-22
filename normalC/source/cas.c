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

static inline uint64_t lf_stack_pack(lf_node* node) {
	return (uint64_t)(node) << CNT_BITS;
}

static inline lf_node *lf_stack_unpack(uint64_t val) {
	return (lf_node *)(val >> CNT_BITS);
}

static inline mfenc() {
	asm volatile ("mfence");
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

	new = lf_stack_pack(node);
	for(;;) {
		old = *(uint64_t *)(head);
		node->next = old;
		node->magic = 0x4a;
#if 0
		*head = new;
		break;
#else
		if (new & 0xfffful) {
			printf("push new 0x%016llx\n", new);
			exit(-1);
		}

		if (old & 0xfffful) {
			printf("push old 0x%016llx, head %p\n", old, head);
			exit(-1);
		}
		checkMark(node);

		if (cas64((uint64_t *)(head), old, new)) {
			old = *(uint64_t *)(head);
			if (old & 0xfffful) {
				printf("cas64 finish push old 0x%016llx, head %p\n", old, head);
				exit(-1);
			}

			break;
		}
#endif
	}

	return 0;
}

lf_node *pop(lf_stack *head) {
	uint64_t next, old;
	lf_node *node;
	int i = 0;

	for(;;i++) {
		old = *(uint64_t *)(head);
		if (old == 0) {
			return NULL;
		}

		if (old & 0xfffful) {
			printf("pop old 0x%016llx, head %p, i %d\n", old, head, i);
			exit(-1);
		}

		node = lf_stack_unpack(old);
		next = node->next;

		if (next & 0xfffful) {
			printf("pop next 0x%016llx, old 0x%016llx, head %p, i %d, node %p, node.magic 0x%x\n", next, old, head, i, node, node->magic);
			exit(-1);
		}

#if 0
		//printf("pop node %p in stack\n", node);
		*head = next;
		break;
#else
		if (cas64((uint64_t *)(head), old, next)) {
			old = *(uint64_t *)(head);
			if (old & 0xfffful) {
				printf("cas64 finish pop old 0x%016llx, head %p\n", old, head);
				exit(-1);
			}
			return node;
		}
#endif
	}
}

