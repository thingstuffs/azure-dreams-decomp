#include "common.h"

extern void *D_800FE490[];

/* Inserts a node at the front of the doubly linked list. */
void prepend_secondary_list_node(void *node) {
    *(void **)node = D_800FE490[0];
    *((void **)node + 1) = D_800FE490;
    *((void **)D_800FE490[0] + 1) = node;
    D_800FE490[0] = node;
}
