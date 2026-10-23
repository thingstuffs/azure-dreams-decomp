#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/node.h"

/* --- gcc 2.7.2 -O2 -G0 TU --- */

/* Sets a "used"/flag bit (0x8000) both on the node's 16-bit flags field and
 * on the global 32-bit flags word, when the node pointer is non-NULL. */
extern int D_800814A0;

/* Linked-list-style node with a 16-bit flags/state field at offset 0x1E
 * (same layout used by func_80040418's Node type in code.c). */

/* Sets bit 0x8000 in the node and global flags when the node exists. */
void table_set_bit_hex_8000_in_node_global_flags_node_exists(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->flags |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
