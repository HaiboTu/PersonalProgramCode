#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define ADDR_BITS	(48)
#define CNT_BITS	(64 - ADDR_BITS)

typedef uint64_t lf_stack;
typedef struct {
	uint64_t next;
	uint64_t cmark;
} lf_node;

int cas64(uint64_t *val, uint64_t oldv, uint64_t newv);

int push(lf_stack *head, lf_node *node);
lf_node *pop(lf_stack *head);

