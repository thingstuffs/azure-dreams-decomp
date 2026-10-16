#include "common.h"

extern void *D_800FE490[];

/* Inserts a node before the doubly linked list sentinel D_800FE490. */
void townAppendSecondaryListNode(void *node) {
    *(void **)node = D_800FE490;
    *((void **)node + 1) = *((void **)D_800FE490 + 1);
    *((void **)*((void **)D_800FE490 + 1)) = node;
    *((void **)D_800FE490 + 1) = node;
}
