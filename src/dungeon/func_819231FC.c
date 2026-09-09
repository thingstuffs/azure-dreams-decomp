#include "common.h"

typedef struct S_800249FC_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_800249FC_0;   /* arg2 in func_800249FC */

typedef struct S_800249FC_1_pre {
    u16 unk_00;
} S_800249FC_1_pre;   /* the 0x2 bytes before arg0 in func_800249FC, addressed as arg0[-1] */

typedef struct S_800249FC_1 {
    u8 pad_00[0x5A];
    union { s16 s; u16 u; } unk_5A;   /* accessed as both */
} S_800249FC_1;   /* arg0 in func_800249FC */



extern s32 func_8002406C(s32 arg0);
extern s16 D_80025B60[5];
extern s32 D_800814A0[3];

/* Update effect values and flags, then mark the object when its countdown expires. */
void func_800249FC(void *object, s32 unused, S_800249FC_0 *effect) {
    s32 ticks_left;
    s16 next_ticks;
    s32 check_result;
    u16 flags;
    u16 paired_value;

    effect->unk_1A += 0x2BC;
    ticks_left = ((S_800249FC_1 *)object)->unk_5A.s;
    D_80025B60[0] = 1;

    if (ticks_left >= 0x29) {
        paired_value = effect->unk_1E + 0xC8;
        effect->unk_1E = paired_value;
        effect->unk_1C = paired_value;
    } else {
        if (ticks_left < 0x15) {
            paired_value = effect->unk_1E - 0xBE;
            effect->unk_1E = paired_value;
            effect->unk_1C = paired_value;
        }
    }

    check_result = func_8002406C(3);
    flags = effect->unk_14;
    if (flags & 0x80) {
        effect->unk_14 = flags & 0xFF7F;
    } else if ((check_result << 16) != 0) {
        effect->unk_14 = flags & 0xFF7F;
    } else {
        effect->unk_14 = flags | 0x80;
    }

    next_ticks = ((S_800249FC_1 *)object)->unk_5A.u - 1;
    ((S_800249FC_1 *)object)->unk_5A.s = next_ticks;
    if ((next_ticks << 16) <= 0) {
        ((S_800249FC_1_pre *)object)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
