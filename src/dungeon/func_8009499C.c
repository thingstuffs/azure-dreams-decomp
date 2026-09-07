#include "common.h"

/* Linked-list node with a next pointer at offset 0x0 and a 16-bit
 * flags/state field at offset 0x1E (shared shape with func_8004027C's
 * D_80081498 view). */
typedef struct Node {
    struct Node *next;      /* 0x00 */
    u8 pad[0x1E - 0x04];
    u16 field_1E;            /* 0x1E */
} Node;

/* D_80081498 is accessed via %hi/%lo, so its containing symbol must be
 * larger than the -G8 small-data threshold; pad it out. */
extern struct {
    Node *head;
    int pad[2];
} D_80081498;

extern s32 D_80012090[];

extern struct {
    s32 v;
    s32 pad[2];
} D_800E296C;

extern void func_80099FDC(void *arg0);

void func_8009A0FC(void) {
    Node *node = D_80081498.head;

    if (node != 0) {
        do {
            if (node->field_1E & 0x1000) {
                func_80099FDC(node);
            }
            node = node->next;
        } while (node != 0);
    }
    if (*(s32 *)0x80012090 != 1) {
        D_800E296C.v &= 0xEFFFFFFF;
    }
}

/* MECHANISM: The natural list loop holds the node in s0 across the call, producing
   the 0x18 frame and exact s0/ra saves.  A literal 0x80012090 lvalue selects the
   absolute-lw macro whose expansion reuses v1 for both the address and loaded value. */
