#include "shared/object_node.h"
#include "common.h"

/* Freelist/active-list node. next at 0x00, prev at 0x04, a slot pointer at
 * 0x08, another slot pointer at 0x0C, flags at 0x1E. Total size 0x124
 * bytes (zeroed via func_8003DB4C(node, 0x49) on allocation). */


extern struct { u16 flags; u8 pad[8]; } D_80013714;
extern ObjectNodeHeader *D_80081490;   /* freelist head */
extern ObjectNodeHeader *D_80081498;   /* active list head */

extern void func_8003DB4C(void *p, s32 n);
extern void *func_8003FB98(s32 a0, void *a1);

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

    freelist_ptr = &D_80081490;
    active_ptr_early = &D_80081498;
    if ((D_80013714.flags & 0x2) && (flags & 0x200)) {
        return 0;
    }

    free_head = *freelist_ptr;
    if (free_head != 0) {
        node = free_head;
        D_80081490 = node->next;
        func_8003DB4C(node, 0x49);

        active_ptr = active_ptr_early;
        active_head = *active_ptr;
        D_80081498 = node;
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
    return func_8003FB98(flags, 0);
}
