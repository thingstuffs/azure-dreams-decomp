#include "common.h"

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

/* Allocates a pool node, installs its record and callback when both values exist, and returns its payload or NULL. */
void *func_8004B364(void *second_value, void *first_value)
{
    S_8004B364_Node *node = (S_8004B364_Node *)func_8003FC64(0);

    if (node != 0) {
        if (second_value != 0 && first_value != 0) {
            S_8004B364_Sub *callback_record = node->field_0x08;
            callback_record->field_0x00 = first_value;
            callback_record->field_0x04 = second_value;
            node->field_0x10 = func_8004B324;
        }
        node = (S_8004B364_Node *)((u8 *)node + 0x20);
    }
    return (void *)node;
}
