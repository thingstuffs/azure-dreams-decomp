#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_80172E80_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    u8 unk_84;
    u8 unk_85;
} S_80172E80_0;   /* arg3 in func_80172E80 */

typedef struct S_80172E80_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80172E80_1;   /* flags_base in func_80172E80 */

typedef struct S_80172E80_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172E80_2;   /* arg2 in func_80172E80 */

typedef struct S_80172E80_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80172E80_3;   /* arg0 in func_80172E80 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047784();
M2C_UNK func_8009C93C();
s32 func_800A0134();
s32 func_800A04F0();
s32 func_800A2B5C();
s32 func_800A2CB8();
M2C_UNK func_800C7930();

extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_800E2378;

s32 func_80172E80(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 result;
    s32 state;
    s32 value;
    s32 flags;
    s32 *flags_base;
    u8 *table;

    ((S_80172E80_0 *)arg3)->unk_71 &= 0x7F;
    flags_base = &D_80083460;
    state = 0;
    if (((S_80172E80_1 *)flags_base)->unk_02 & 0x2000) {
        goto return_minus_one;
    }

    value = func_800A04F0(arg3, ((S_80172E80_2 *)arg2)->unk_24,
                         ((S_80172E80_2 *)arg2)->unk_25,
                         ((S_80172E80_0 *)arg3)->unk_2A);
    result = 0;
    if ((func_800A2CB8(arg3, value) << 16) == 0) {
        goto return_zero;
    }

    result = -1;
    flags = ((S_80172E80_1 *)flags_base)->unk_02;
    if (flags & 0x2000) {
        return result;
    }
    if (!(((S_80172E80_0 *)arg3)->unk_46 & 0x8000)) {
        if (flags & 8) {
            return result;
        }
    }

    if ((u16)((0 - func_800A0134(value, arg3)) + 0x40) >= 0x81U) {
        return state;
    }

    state = 1;
    if (!(((S_80172E80_0 *)arg3)->unk_46 & 0x8000)) {
        if (D_80083462 & 8) {
            return -1;
        }
    }
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((s8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) != 0) {
return_minus_one:
        return -1;
    }

    result = state;
    ((S_80172E80_3 *)arg0)->unk_9B = 0;
    if (result != 0) {
        ((S_80172E80_3 *)arg0)->unk_9A = 0x11;
        ((S_80172E80_3 *)arg0)->unk_8C = 0;
        ((S_80172E80_0 *)arg3)->unk_84 = 0x7C;
        ((S_80172E80_0 *)arg3)->unk_85 = 0;
        ((S_80172E80_3 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172E80_0 *)arg3)->unk_1C &= 0xFFFBFFFF;
        table = &D_800E2378;
        (*(u8 **)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
                      table[((D_80083228 + ((S_80172E80_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                      0);
        ((S_80172E80_0 *)arg3)->unk_6D--;
        func_8009C93C(arg3, arg2, ((S_80172E80_0 *)arg3)->unk_2A, 1, 0);
    }
    return result;

return_zero:
    return 0;
}
