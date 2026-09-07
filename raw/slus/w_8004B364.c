#include "common.h"

/* Allocates a pool node via func_8003FC64(0). If allocation succeeds and both
 * a0 and a1 are non-null, stores a1/a0 into the node's sub-record (field_0x8)
 * and installs func_8004B324 as the node's callback (field_0x10). Returns a
 * pointer 0x20 bytes into the node (or NULL if allocation failed). */
/* Sub-record written into the node's field_0x8 slot: two words at offset
 * 0x00 and 0x04. */
typedef struct S_8004B364_Sub {
    void *field_0x00;
    void *field_0x04;
} S_8004B364_Sub;

/* Pool node layout (same node type allocated by func_8003FC64): pointers at
 * 0x00/0x04/0x08/0x0C, and a callback-function-pointer slot at 0x10. */
typedef struct S_8004B364_Node {
    void *field_0x00;
    void *field_0x04;
    S_8004B364_Sub *field_0x08;
    void *field_0x0C;
    void (*field_0x10)(void *, void *);
} S_8004B364_Node;

extern void *func_8003FC64(s32 a0);
extern void func_8004B324(void *a0, void *a1);

void *func_8004B364(void *a0, void *a1)
{
    S_8004B364_Node *node = (S_8004B364_Node *)func_8003FC64(0);

    if (node != 0) {
        if (a0 != 0 && a1 != 0) {
            S_8004B364_Sub *sub = node->field_0x08;
            sub->field_0x00 = a1;
            sub->field_0x04 = a0;
            node->field_0x10 = func_8004B324;
        }
        node = (S_8004B364_Node *)((u8 *)node + 0x20);
    }
    return (void *)node;
}
