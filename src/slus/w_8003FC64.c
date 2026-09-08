#include "common.h"

/* Freelist/active-list node. next at 0x00, prev at 0x04, a slot pointer at
 * 0x08, another slot pointer at 0x0C, flags at 0x1E. Total size 0x124
 * bytes (zeroed via func_8003DB4C(node, 0x49) on allocation). */
typedef struct S_80081490 {
    struct S_80081490 *next;   /* 0x00 */
    struct S_80081490 *prev;   /* 0x04 */
    void *field_0x8;           /* 0x08 */
    void *field_0xC;           /* 0x0C */
    u8 pad_0x10[0x1E - 0x10];
    u16 field_0x1E;            /* 0x1E */
    u8 pad_0x20[0x124 - 0x20];
} S_80081490;

extern struct { u16 flags; u8 pad[8]; } D_80013714;
extern struct { S_80081490 *head; s32 pad[2]; } D_80081490;   /* freelist head */
extern struct { S_80081490 *head; s32 pad[2]; } D_80081498;   /* active list head */

extern void func_8003DB4C(void *p, s32 n);
extern void *func_8003FB98(s32 a0, void *a1);

/* Allocates and initializes an active node, reclaiming an eligible active node if needed and allowed. */
void *func_8003FC64(s32 flags)
{
    S_80081490 *node;
    S_80081490 *free_head;
    S_80081490 *active_head;
    u8 *buffer;
    __typeof__(&D_80081490) freelist_ptr;
    __typeof__(&D_80081498) active_ptr;
    __typeof__(&D_80081498) active_ptr_early;

    freelist_ptr = &D_80081490;
    active_ptr_early = &D_80081498;
    if ((D_80013714.flags & 0x2) && (flags & 0x200)) {
        return 0;
    }

    free_head = freelist_ptr->head;
    if (free_head != 0) {
        node = free_head;
        D_80081490.head = node->next;
        func_8003DB4C(node, 0x49);

        active_ptr = active_ptr_early;
        active_head = active_ptr->head;
        D_80081498.head = node;
        node->next = active_head;
        if (active_head != 0) {
            active_head->prev = node;
        }

        node->field_0x1E = flags | 0x4000;

        buffer = (u8 *)node + 0x124;
        if (flags & 0x100) {
            buffer = (u8 *)node + 0xF4;
            goto store_buffer;
        }
        if (flags & 0x6) {
            buffer = (u8 *)node + 0x100;
            goto store_buffer;
        }
        if (flags & 0x41) {
            buffer = (u8 *)node + 0x10C;
        store_buffer:
            node->field_0xC = buffer;
        }

        if (flags & 0x157) {
            buffer = buffer - 0x18;
            node->field_0x8 = buffer;
        }

        return node;
    }

    if (flags & 0x200) {
        return 0;
    }
    return func_8003FB98(flags, 0);
}
