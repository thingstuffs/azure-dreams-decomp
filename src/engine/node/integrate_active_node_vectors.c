#include "common.h"
#include "engine/node.h"

/* Linked-list node with a next pointer at offset 0x0, a pointer to a
 * position/velocity vector block at offset 0x8, and a 16-bit flags/state
 * field at offset 0x1E (shared shape with func_80040418/remove_marked_active_nodes/
 * evict_node_and_allocate's D_80081498 view). */
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

extern Node *active_node_list_head;

/* Add velocity to position for each node in D_80081498 with flag 0x8 set. */
void integrate_active_node_vectors(void) {
    Node *node = active_node_list_head;

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
