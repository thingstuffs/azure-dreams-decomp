#include "common.h"

typedef struct S_8004D98C {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    u16 unk4;
    u16 unk6;
    u8 unk8[4];
} S_8004D98C;

extern void func_8004D8F0(u32 a0, u8 *a1);

/* Initializes a target/effect struct: clears byte 0, sets type byte 1 to 0x2C,
 * sets half 4 to 0x1F, computes a palette/anim id into half 6 based on the low
 * nibble of a1 (offset by 0x7C88 if bit 0x10 of a1 is set, else 0x7C80), then
 * calls func_8004D8F0 to fill the 4 bytes at offset 8 from the low byte of a0. */
void func_8004D98C(s32 a0, s32 a1, S_8004D98C *a2)
{
    s32 v1 = a1 & 0xF;

    a2->unk1 = 0x2C;
    a2->unk4 = 0x1F;
    a2->unk0 = 0;
    a2->unk6 = v1 + 0x7C80;
    if (a1 & 0x10) {
        a2->unk6 = v1 + 0x7C88;
    }
    func_8004D8F0(a0 & 0xFF, a2->unk8);
}
