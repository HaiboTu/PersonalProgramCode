#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define ADDR_BITS	(0x30ul)
#define CNT_BITS	(0x40ul - ADDR_BITS)
#define CNT_MASK	((1ul << CNT_BITS) - 1)

typedef uint64_t lf_stack;
typedef struct {
	uint64_t next;
	uint64_t cmark;
} lf_node;

int cas64(uint64_t *val, uint64_t oldv, uint64_t newv);

int push(lf_stack *head, lf_node *node);
lf_node *pop(lf_stack *head);

