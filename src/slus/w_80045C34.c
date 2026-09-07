#include "common.h"

/* S_80045C34: the "flags/value" record pointed to by a2. Only two fields are
 * accessed by this function: a signed 16-bit value at 0x6 and a 16-bit flags
 * word at 0x14 (bit 0x80 tested). */
typedef struct S_80045C34 {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad1[0x14 - 0x8];
    /* 0x14 */ u16 unk14;
} S_80045C34;

extern void func_80045CC4(void *a0, s32 a1, S_80045C34 *a2, s16 a3);
extern s32 func_80045310(u32 a0);

/* D_80083160[0] points at a large shared-state struct; only the pointer field
 * at offset 0x8D0 is read here. */
extern void *D_80083160[3];

/* Walks a singly-linked list of "link" records. Each link record has a next
 * pointer at offset 0x18 relative to the record base (i.e. 8 bytes before the
 * "s0" pointer passed in, which addresses record_base+0x20), an int value at
 * offset 0x8, and a pointer to an S_80045C34 record at offset 0xC. For each
 * live record whose S_80045C34 flags don't have bit 0x80 set, calls
 * func_80045CC4 and then bails out (returning 0) if func_80045310 signals to
 * stop. Always returns 0. */
s32 func_80045C34(u8 *a0, s32 a1, S_80045C34 *a2)
{
    u8 *s0 = a0;
    void *next;

    do {
        if (!(a2->unk14 & 0x80)) {
            func_80045CC4(s0, a1, a2, a2->unk6);
            if (func_80045310(*(u32 *)((u8 *)D_80083160[0] + 0x8D0))) {
                return 0;
            }
        }
        next = *(void **)(s0 - 8);
        if (next == 0) {
            return 0;
        }
        s0 = (u8 *)next + 0x20;
        a1 = *(s32 *)((u8 *)next + 8);
        a2 = *(S_80045C34 **)((u8 *)next + 0xC);
    } while (1);
}
