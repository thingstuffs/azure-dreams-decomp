#include "common.h"

/* --- gcc 2.7.2 -O2 -G0 TU --- */

/* Sets a "used"/flag bit (0x8000) both on the node's 16-bit flags field and
 * on the global 32-bit flags word, when the node pointer is non-NULL. */
extern int D_800814A0;

/* Linked-list-style node with a 16-bit flags/state field at offset 0x1E
 * (same layout used by func_80040418's Node type in code.c). */
typedef struct Node {
    struct Node *next;       /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

void func_8004B500(Node *a0)
{
    if (a0 != 0) {
        a0->field_1E |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
