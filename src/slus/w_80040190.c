#include "common.h"

/* Linked-list node with a next pointer at offset 0x0, two callback-argument
 * fields at 0x8/0xC, a raw (possibly-null) function-pointer value at 0x10,
 * and a 16-bit flags field at 0x1E. */
typedef struct S_80081498_Node {
    struct S_80081498_Node *next;   /* 0x00 */
    u8 pad_04[0x08 - 0x04];
    void *field_08;                 /* 0x08 */
    void *field_0C;                 /* 0x0C */
    s32 field_10;                   /* 0x10 - raw function pointer value, checked via signed bgez */
    u8 pad_14[0x1E - 0x14];
    u16 field_1E;                   /* 0x1E */
} S_80081498_Node;

/* D_80081498 is accessed via %hi/%lo, so its containing symbol must be
 * larger than the -G8 small-data threshold; pad it out. */
extern struct S_80081498 {
    S_80081498_Node *head;
    s32 pad[2];
} D_80081498;

/* Invokes negative-address callbacks on nodes in D_80081498 whose flags omit bit 0x400. */
void func_80040190(void)
{
    S_80081498_Node *node;
    S_80081498_Node *nextNode;
    s32 callbackAddress;

    node = D_80081498.head;
    if (node != 0) {
        do {
            callbackAddress = node->field_10;
            nextNode = node->next;
            if (callbackAddress >= 0 || (node->field_1E & 0x400)) {
                ;
            } else {
                ((void (*)(void *, void *, void *))callbackAddress)((u8 *)node + 0x20, node->field_08, node->field_0C);
            }
            node = nextNode;
        } while (node != 0);
    }
}
