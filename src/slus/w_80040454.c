#include "common.h"

/* Linked-list node with a next pointer at offset 0x0 and a 16-bit flags/state
 * field at offset 0x1E. Iterates the global singly-linked list headed by
 * D_80081498, clearing bits 0xC00 (masking with 0xF3FF) in that field of
 * every node. Mirrors the shape of func_80040418, which OR's 0xC00 in. */

typedef struct S_80040454 {
    struct S_80040454 *next;       /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E;       /* 0x1E */
} S_80040454;

/* D_80081498 is accessed via %hi/%lo, so its containing symbol must be
 * larger than the -G8 small-data threshold; pad it out. */
extern struct {
    S_80040454 *head;
    int pad[2];
} D_80081498;

void func_80040454(void)
{
    S_80040454 *v1 = D_80081498.head;

    if (v1 != 0) {
        do {
            v1->field_1E &= 0xF3FF;
            v1 = v1->next;
        } while (v1 != 0);
    }
}
