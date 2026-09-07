#include "common.h"

/* S_8004761C_Entry: array element (same family as S_800482C8_Entry); stride 0xC,
 * only the flags byte at offset 0 is read here. */
struct S_8004761C_Entry {
    u8 flags;
    u8 pad[0xB];
};

extern void func_80047468(struct S_8004761C_Entry *a0, s32 a1, s32 a2);

/* Walks an array of 0xC-byte entries (terminated by an entry whose flags byte
 * has bit 0x80 set). For each entry whose flags byte has neither of bits
 * 0x20/0x40 set, decrements a running u16* cursor (starting at the array
 * base) and dispatches to func_80047468, passing the entry pointer, *arg1,
 * and the u16 value at the cursor. */
void func_8004761C(struct S_8004761C_Entry *arg0, s32 *arg1)
{
    struct S_8004761C_Entry *s0 = arg0;
    s32 *s2 = arg1;
    u16 *s1 = (u16 *)arg0;

    do {
        if (!(s0->flags & 0x60)) {
            s1--;
            func_80047468(s0, *s2, *s1);
        }
    } while (!((s0++)->flags & 0x80));
}
