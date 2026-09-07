#include "common.h"

/* Linked-list node with a next pointer at offset 0x0, a pointer to a
 * position/velocity vector block at offset 0x8, and a 16-bit flags/state
 * field at offset 0x1E (shared shape with func_80040418/func_800401FC/
 * func_8003FB98's D_80081498 view). */
typedef struct Node {
    struct Node *next;      /* 0x00 */
    u8 unk04[0x08 - 0x04];
    struct S_8004027C_vec *pos; /* 0x08 */
    u8 pad[0x1E - 0x0C];
    u16 field_1E;            /* 0x1E */
} Node;

/* Position/velocity vector block pointed to at Node+0x8 */
typedef struct S_8004027C_vec {
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
} S_8004027C_vec;

/* D_80081498 is accessed via %hi/%lo, so its containing symbol must be
 * larger than the -G8 small-data threshold; pad it out. */
extern struct {
    Node *head;
    int pad[2];
} D_80081498;

/* Add velocity to position for each node in D_80081498.head with flag 0x8 set. */
void func_8004027C(void) {
    Node *node = D_80081498.head;

    if (node != 0) {
        do {
            if (node->field_1E & 0x8) {
                S_8004027C_vec *pos = node->pos;
                pos->x += pos->vx;
                pos->y += pos->vy;
                pos->z += pos->vz;
            }
            node = node->next;
        } while (node != 0);
    }
}
