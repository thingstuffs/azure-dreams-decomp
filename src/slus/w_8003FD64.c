#include "common.h"

#include "common.h"

typedef struct S_80081490 {
    struct S_80081490 *next;    /* 0x00 */
    struct S_80081490 **pprev;  /* 0x04 - address of the slot pointing at this node */
    void *field_0x8;            /* 0x08 */
    void *field_0xC;            /* 0x0C */
    u8 pad_0x10[0x1E - 0x10];
    u16 field_0x1E;             /* 0x1E */
    u8 pad_0x20[0x124 - 0x20];
} S_80081490;

typedef struct S_80013714 {
    u16 flags;      /* 0x0 */
    u8 pad[8];      /* keep size > 8 to force %hi/%lo addressing */
} S_80013714;

extern S_80013714 D_80013714;

extern void func_8003DB4C(int *p, int n);
extern void *func_8003FB98(s32 a0, void *a1);

/* Allocates a freelist node and links it onto the caller-provided list *a1
 * (an hlist-style doubly linked list: pprev points at the slot referencing
 * this node, not at the previous node itself). If global flag bit 0x2 is
 * set and a0 has bit 0x200 set, bails out early returning NULL. If the
 * freelist D_80081490 is empty, falls back to func_8003FB98(a0, a1) (unless
 * a0 has bit 0x200 set, in which case NULL). On success the node is zeroed,
 * pushed onto the front of *a1, its flags field set to a0|0x4000, and one of
 * 4 sub-buffer offsets (0xF4/0x100/0x10C/0x124 depending on a0's low bits)
 * is selected and stored at field_0xC (skipped for the default 0x124 case);
 * if any of bits 0x157 are set, field_0x8 is set to that pointer minus 0x18.
 * Returns the allocated node. */
void *func_8003FD64(s32 a0, S_80081490 **a1)
{
    S_80081490 *s0;
    S_80081490 *v0;
    u8 *v1;

    if ((D_80013714.flags & 0x2) && (a0 & 0x200)) {
        return 0;
    }

    {
        extern S_80081490 *D_80081490;
        v0 = D_80081490;
    }
    if (v0 != 0) {
        s0 = v0;
        {
            extern struct { S_80081490 *head; s32 pad[2]; } D_80081490;
            D_80081490.head = s0->next;
        }
        func_8003DB4C((int *)s0, 0x49);

        s0->next = *a1;
        *a1 = s0;
        s0->pprev = a1;
        if (s0->next != 0) {
            s0->next->pprev = (S_80081490 **)s0;
        }

        s0->field_0x1E = (u16)(a0 | 0x4000);

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
    return func_8003FB98(a0, a1);
}
