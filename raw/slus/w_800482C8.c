#include "common.h"

/* Walks an array of 0xC-byte entries (terminated by an entry whose flags byte has bit 0x80 set). For each entry whose flags byte has neither of bits 0x20/0x40 set, decrements a running s32* cursor (starting at the array base, reinterpreted as s32*) and dispatches to one of two callbacks selected by D_80082E60's byte at offset 0xA, passing the entry pointer, *arg1, and the value at the cursor. */
/* S_800482C8: array element for the entity/monster list iterated here;
 * stride 0xC, only the flags byte at offset 0 is read. */
struct S_800482C8_Entry {
    u8 flags;
    u8 pad[0xB];
};

/* S_80082E60: global state struct; field at offset 0xA (u8) selects which
 * of two callback functions is invoked. This is the same struct as
 * src/w_80040BB4.c's S_80082E60, which currently names this byte pad_A
 * (unused there) -- it should be renamed field_A and reconciled. */
struct S_80082E60 {
    char pad0[0xA];
    u8 field_A;
};

extern struct S_80082E60 D_80082E60;

extern void func_80047338(struct S_800482C8_Entry *a0, s32 a1, s32 a2);
extern void func_80047468(struct S_800482C8_Entry *a0, s32 a1, s32 a2);

void func_800482C8(struct S_800482C8_Entry *arg0, s32 *arg1)
{
    struct S_800482C8_Entry *s0 = arg0;
    s32 *s2 = arg1;
    s32 *s1 = (s32 *)arg0;

    do {
        if (!(s0->flags & 0x60)) {
            s1--;
            if (D_80082E60.field_A == 1) {
                func_80047468(s0, *s2, *s1);
            } else {
                func_80047338(s0, *s2, *s1);
            }
        }
    } while (!((s0++)->flags & 0x80));
}
