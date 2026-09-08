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

/* Initializes an effect record with a style-selected ID and data derived from the low input byte. */
void func_8004D98C(s32 data_id, s32 style_flags, S_8004D98C *effect)
{
    s32 style_index = style_flags & 0xF;

    effect->unk1 = 0x2C;
    effect->unk4 = 0x1F;
    effect->unk0 = 0;
    effect->unk6 = style_index + 0x7C80;
    if (style_flags & 0x10) {
        effect->unk6 = style_index + 0x7C88;
    }
    func_8004D8F0(data_id & 0xFF, effect->unk8);
}
