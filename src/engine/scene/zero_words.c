#include "shared/object_node.h"
#include "common.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "slus.h"

/* Freelist/active-list node. next at 0x00, prev at 0x04, a slot pointer at
 * 0x08, another slot pointer at 0x0C, flags at 0x1E. Total size 0x124
 * bytes (zeroed via zero_words(node, 0x49) on allocation). */


extern struct { u16 flags; u8 pad[8]; } system_update_flags;
extern ObjectNodeHeader *free_node_list_head;   /* freelist head */
extern ObjectNodeHeader *active_node_list_head;   /* active list head */

/* Allocates and initializes an active node, reclaiming an eligible active node if needed and allowed. */
ObjectNodeHeader *func_8003FC64(s32 flags)
{
    ObjectNodeHeader *node;
    ObjectNodeHeader *free_head;
    ObjectNodeHeader *active_head;
    u8 *buffer;
    ObjectNodeHeader **freelist_ptr;
    ObjectNodeHeader **active_ptr;
    ObjectNodeHeader **active_ptr_early;

    freelist_ptr = &free_node_list_head;
    active_ptr_early = &active_node_list_head;
    if ((system_update_flags.flags & 0x2) && (flags & 0x200)) {
        return 0;
    }

    free_head = *freelist_ptr;
    if (free_head != 0) {
        node = free_head;
        free_node_list_head = node->next;
        zero_words(node, 0x49);

        active_ptr = active_ptr_early;
        active_head = *active_ptr;
        active_node_list_head = node;
        node->next = active_head;
        if (active_head != 0) {
            active_head->pprev = (ObjectNodeHeader **)node;
        }

        node->flags = flags | 0x4000;

        buffer = (u8 *)node + 0x124;
        if (flags & 0x100) {
            buffer = (u8 *)node + 0xF4;
            node->unk_0C = buffer;
        } else if (flags & 0x6) {
            buffer = (u8 *)node + 0x100;
            node->unk_0C = buffer;
        } else if (flags & 0x41) {
            buffer = (u8 *)node + 0x10C;
            node->unk_0C = buffer;
        }

        if (flags & 0x157) {
            buffer = buffer - 0x18;
            node->unk_08 = buffer;
        }

        return node;
    }

    if (flags & 0x200) {
        return 0;
    }
    return evict_node_and_allocate(flags, 0);
}
