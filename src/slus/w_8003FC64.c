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

/* Allocates a node: if global flag bit 0x2 is set and a0 has bit 0x200 set,
 * bail out early (returns NULL). Otherwise pops the head of the freelist
 * D_80081490; if the freelist is empty, falls back to scanning the active
 * list via func_8003FB98(a0, NULL) (unless a0 has bit 0x200 set, in which
 * case it returns NULL). On a successful pop, the node is zeroed, pushed
 * onto the front of the active list D_80081498, its flags field is set to
 * a0|0x4000, and one of 4 sub-buffer pointers (offset 0xF4/0x100/0x10C/0x124
 * depending on a0's low bits) is selected and stored at field_0xC (skipped
 * for the default 0x124 case); if any of bits 0x157 are set, field_0x8 is
 * set to that pointer minus 0x18. Returns the allocated node. */
void *func_8003FC64(s32 a0)
{
    S_80081490 *s0;
    S_80081490 *v0;
    S_80081490 *old_head;
    u8 *v1;
    __typeof__(&D_80081490) freelist_ptr;
    __typeof__(&D_80081498) active_ptr;
    __typeof__(&D_80081498) active_ptr_early;

    freelist_ptr = &D_80081490;
    active_ptr_early = &D_80081498;
    if ((D_80013714.flags & 0x2) && (a0 & 0x200)) {
        return 0;
    }

    v0 = freelist_ptr->head;
    if (v0 != 0) {
        s0 = v0;
        D_80081490.head = s0->next;
        func_8003DB4C(s0, 0x49);

        active_ptr = active_ptr_early;
        old_head = active_ptr->head;
        D_80081498.head = s0;
        s0->next = old_head;
        if (old_head != 0) {
            old_head->prev = s0;
        }

        s0->field_0x1E = a0 | 0x4000;

        v1 = (u8 *)s0 + 0x124;
        if (a0 & 0x100) {
            v1 = (u8 *)s0 + 0xF4;
            goto write_0xc;
        }
        if (a0 & 0x6) {
            v1 = (u8 *)s0 + 0x100;
            goto write_0xc;
        }
        if (a0 & 0x41) {
            v1 = (u8 *)s0 + 0x10C;
        write_0xc:
            s0->field_0xC = v1;
        }

        if (a0 & 0x157) {
            v1 = v1 - 0x18;
            s0->field_0x8 = v1;
        }

        return s0;
    }

    if (a0 & 0x200) {
        return 0;
    }
    return func_8003FB98(a0, 0);
}
